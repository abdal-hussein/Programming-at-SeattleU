"""
CPSC 5520 Distributed Systems
Seattle University
This is free and unencumbered software released into the public domain.

Extra credit attempted:
- PROBE
- Feigning failure

:Authors: Justin Thoreson
:Version: f22
"""

from datetime import datetime as dt
from enum import Enum
from time import sleep
import selectors
import socket
import pickle
import random
import sys

BUF_SZ = 1024
CHECK_INTERVAL = 1
ASSUME_FAILURE_TIMEOUT = 1.5
PEER_DIGITS_MODULUS = 100
PEER_DIGITS_DISPLAY = 10

class State(Enum):
  """Enumeration of states a peer can be in for the Lab2 class."""

  # Erase any memory of this peer
  QUIESCENT = 'QUIESCENT'

  # Outgoing message is pending
  SEND_JOIN = 'JOIN' # Message to send to GCD (unrelated to member states)
  SEND_ELECTION = 'ELECTION'
  SEND_VICTORY = 'COORDINATOR'
  SEND_OK = 'OK'
  SEND_PROBE = 'PROBE'

  # Incoming message is pending
  WAITING_FOR_OK = 'WAIT_OK'  # When I've sent them an ELECTION message
  WAITING_FOR_VICTOR = 'WHO IS THE WINNER?'  # This one only applies to myself
  WAITING_FOR_ANY_MESSAGE = 'WAITING'  # When I've done an accept on their connect to my server

  def is_incoming(self):
    """Categorization helper."""

    return self not in (State.SEND_ELECTION, State.SEND_VICTORY, State.SEND_OK)

class BullyGroupMember(object):
  
  def __init__(self, gcd_host, gcd_port, next_birthday, su_id):
    """Constructs a BullyGroupMember object to talk to the given Group Coordinator Daemon.
    
    :param gcd_host: The host name where the GCD is hosted
    :param gcd_port: The port number in which the GCD is hosted
    :param next_birthday: The date of a student's next birthday
    :param su_id: The student's identification number
    """

    # Variables per Prof. Lundeen
    self.gcd_address = (gcd_host, gcd_port)
    days_to_birthday = (next_birthday - dt.now()).days
    self.pid = (days_to_birthday, su_id)
    self.members = {}
    self.states = {}
    self.bully = None
    self.selector = selectors.DefaultSelector()
    self.listener, self.listener_address = self.start_a_server()
    self.last_probe = self.pr_now()
    self.last_feigned_failure = self.pr_now()

  def run(self):
    """Runs the Lab2 Bully algorithm asynchronously via a selector loop"""

    # Register listener to accept clients
    self.set_state(State.WAITING_FOR_ANY_MESSAGE)

    # Get members from GCD
    self.update_members(self.join_group())

    # Send election or declare vitory
    if max(self.members.keys()) > self.pid:
      self.start_election('joining group')
    else:
      self.declare_victory('I am the biggest bully')

    # Selector loop for asynchronous message passing
    while True:
      events = self.selector.select(CHECK_INTERVAL)
      for key, mask in events:
        if key.fileobj == self.listener:
          self.accept_peer()
        elif mask & selectors.EVENT_READ:
          self.receive_message(key.fileobj)
        else:
          self.send_message(key.fileobj)
      self.check_timeouts()
      self.probe_leader()
      self.feign_failure()

  def accept_peer(self):
    """Accept TCP/IP connections from peer"""

    try:
      connection, _address = self.listener.accept()
      print(f'{self.pr_sock(connection)}: accepted [{self.pr_now()}]')
      connection.setblocking(False)
      connection.settimeout(ASSUME_FAILURE_TIMEOUT)
      self.set_state(State.WAITING_FOR_ANY_MESSAGE, connection)
    except Exception as err:
      print(f'{self.pr_sock(connection)}: failed to accept [{self.pr_now()}]')

  def send_message(self, peer):
    """Send the queued message to the given peer based on its current state
    
    :param peer: A peers designated socket
    """

    state = self.get_state(peer)
    print(f'{self.pr_sock(peer)}: sending {state.value} [{self.pr_now()}]')
    try:
      if state == State.SEND_VICTORY:
        members = {pid:address for pid, address in self.members.items() if pid <= self.pid}
      else:
        members = self.members
      self.send(peer, state.value, members)
    except ConnectionError as err:
      print(f'Error connecting to peer: {err}')
    except Exception as err:
      print(f'Error sending message: {err}')

    # Check to see if we want to wait for response immediately
    if state == State.SEND_ELECTION:
      self.set_state(State.WAITING_FOR_OK, peer, switch_mode=True)
    else:
      self.set_quiescent(peer)

  def receive_message(self, peer):
    """Receive an asynchronous message from a particular peer
    
    :param peer: The peer socket to receive a message from
    """
    try:
      message = self.receive(peer)
      message_name, message_data = message if type(message) is tuple else (message, self.members)
    except Exception:
      print(f'{self.pr_sock(peer)}: failed to receive message [{self.pr_now()}]')
      self.set_state(State.WAITING_FOR_ANY_MESSAGE, switch_mode=True)
      self.set_quiescent(peer)
    else:
      # Election
      if message_name == State.SEND_ELECTION.value:
        print(f'{self.pr_sock(peer)}: received ELECTION [{self.pr_now()}]')
        self.update_members(message_data)
        self.send(peer, State.SEND_OK.value)
        self.set_state(State.SEND_OK, peer, switch_mode=True)
        if not self.is_election_in_progress():
          if max(self.members.keys()) > self.pid:
            self.start_election('election received from peer')
          else:
            self.declare_victory('I am the biggest bully')

      # Ok
      elif message_name == State.SEND_OK.value:
        print(f'{self.pr_sock(peer)}: received OK [{self.pr_now()}]')
        self.set_state(State.WAITING_FOR_VICTOR, switch_mode=True)
        self.set_quiescent(peer)

      # Coordinate
      elif message_name == State.SEND_VICTORY.value:
        print(f'{self.pr_sock(peer)}: received COORDINATE [{self.pr_now()}]')
        self.update_members(message_data)
        self.set_state(State.WAITING_FOR_ANY_MESSAGE, switch_mode=True)
        self.set_quiescent(peer)
        self.set_leader(max(message_data.keys()))
        print(f'Leader is now: {self.pr_leader()}')

      # Probe
      elif message_name == State.SEND_PROBE.value:
        print(f'{self.pr_sock(peer)}: received PROBE [{self.pr_now()}]')
        print(f'{self.pr_sock(peer)}: sending OK [{self.pr_now()}]')
        self.send(peer, State.SEND_OK.value)
        self.set_quiescent(peer)

  def check_timeouts(self):
    """Check all peers for timeout"""

    expired = [peer for peer in self.states if not self.listener == peer and self.is_expired(peer)]
    for peer in expired:
      self.set_quiescent(peer)
    if self.is_expired(self.listener):
      state = self.get_state(self.listener)
      if state == State.WAITING_FOR_OK:
        self.declare_victory('bigger bullies timed out')
      elif state == State.WAITING_FOR_VICTOR:
        self.start_election('COORDINATE not received')

  # Consulted Ana Mendes for help w/ PROBE 
  def is_time_to_probe(self):
    """Determines if it's a proper time to send a probe message to the leader
    
    :return: True if proper time to probe, False otherwise
    """

    probe_time = random.uniform(0.5, 3.0)
    last_probe = dt.strptime(self.last_probe, '%H:%M:%S.%f')
    is_time_to_probe = (dt.now() - last_probe).seconds > probe_time
    is_valid_bully = not self.is_election_in_progress() and not self.bully == self.pid
    return is_time_to_probe and is_valid_bully

  # Consulted Ana Mendes for help w/ PROBE
  def probe_leader(self):
    """Sends a PROBE message to the leader"""

    if self.is_time_to_probe():
      leader = (self.bully, self.members[self.bully])
      peer = self.get_connection(leader)
      is_successful_probe = True
      if peer:
        print(f'{self.pr_sock(peer)}: sending PROBE [{self.pr_now()}]')
        try:
          response = self.send(peer, State.SEND_PROBE.value, wait_for_reply=True)
          if response and response == State.SEND_OK.value:
            print(f'{self.pr_sock(peer)}: received OK [{self.pr_now()}]')
        except Exception:
          print(f'{self.pr_sock(peer)}: PROBE unsuccessful [{self.pr_now()}]')
          is_successful_probe = False
        self.set_quiescent(peer)
      elif not peer or not is_successful_probe:
        self.declare_victory('leader has failed')

  # Consulted Ana mendes and Remi Ta for tips on feigning failure
  def feign_failure(self):
    """Present false appearance of failure to other peers"""
    
    sleep_duration = random.uniform(1, 4)
    sleep_reference_time = random.uniform(0, 10)
    last_feigned_failure = dt.strptime(self.last_feigned_failure, '%H:%M:%S.%f')
    is_feigning_time = (dt.now() - last_feigned_failure).seconds > sleep_reference_time
    if is_feigning_time:
      print("Going to sleep...")
      sleep(sleep_duration)
      print("Waking up...")
      self.start_election("waking up")

  def get_connection(self, member):
    """Establishes a connection for a particular member w/ their address
    
    :param member: The peer to establish a connection with
    :return: The member's designated socket
    """

    peer = socket.socket(socket.AF_INET, socket.SOCK_STREAM | socket.SOCK_NONBLOCK)
    peer.settimeout(ASSUME_FAILURE_TIMEOUT)
    try:
      peer.connect(member[1])
    except BlockingIOError:
      pass
    except (ConnectionError, socket.timeout):
      return None
    self.set_state(State.WAITING_FOR_ANY_MESSAGE, peer)
    return peer
  
  def is_election_in_progress(self):
    """Determines whether an election is in progress
    
    :return: True if election in progress, False otherwise
    """

    state = self.states[self.listener][0]
    states = [State.SEND_ELECTION, State.SEND_OK, State.WAITING_FOR_OK, State.WAITING_FOR_VICTOR]
    return self.bully is None and state in states
  
  def is_expired(self, peer=None, threshold=ASSUME_FAILURE_TIMEOUT):
    """Determines whether a peer has expired through timeout
    
    :param peer: A member's designated socket to check for timeout
    :param threshold: The alloted time before timeout occurs
    :return: True if timeout occured, False otherwise
    """

    if not peer:
      return False
    return (dt.now() - dt.strptime(self.states[peer][1], '%H:%M:%S.%f')).seconds > threshold
  
  def set_leader(self, new_leader):
    """Updates the current bully
    
    :param new_leader: The PID of the new bully
    """
    
    self.bully = new_leader
  
  def get_state(self, peer=None, detail=False):
    """Look up current state in state table.

    :param peer: socket connected to peer process (None means self)
    :param detail: if True, then the state and timestamp are both returned
    :return: either the state or (state, timestamp) depending on detail (not found gives (QUIESCENT, None))
    """

    if peer is None:
      peer = self
    status = self.states[peer] if peer in self.states else (State.QUIESCENT, None)
    return status if detail else status[0]

  def set_state(self, state, peer=None, switch_mode=False):
    """Sets the state of a particular peer
    
    :param state: The state to impose unto a peer
    :param peer: The member socket to establish a state unto (peer is listener socket if None)
    :param switch_mode: Determines if a state is being newly established or updated
    """

    event = selectors.EVENT_READ if state.is_incoming() else selectors.EVENT_WRITE
    member = peer if peer else self.listener
    if switch_mode:
      self.selector.unregister(member)
    self.states[member] = (state, self.pr_now())
    self.selector.register(member, event)

  def set_quiescent(self, peer=None):
    """Forgets the provided peer
    
    :param peer: The peer to forget via quiescence
    """

    if peer and not self.listener == peer:
      self.selector.unregister(peer)
      del self.states[peer]
      peer.close()
  
  def start_election(self, reason):
    """Starts an election amongst members with higher PID values
    
    :param reason: The reason for starting an election
    """

    print(f'Starting an election: {reason}')
    has_connected_to_bully = False
    for member in self.members.items():
      if member[0] > self.pid:
        peer = self.get_connection(member)
        if peer:
          self.set_state(State.SEND_ELECTION, peer, switch_mode=True)
          self.set_state(State.WAITING_FOR_OK, switch_mode=True)
          has_connected_to_bully = True
    if not has_connected_to_bully:
      self.declare_victory('I am the biggest bully')
  
  def declare_victory(self, reason):
    """Declare self as bully by sending coordinate messages to all other peers
    
    :param reason: The reason for declaring victory
    """
    
    print(f'Victory by {self.pid}: {reason}')
    self.set_leader(self.pid)
    self.set_state(State.WAITING_FOR_ANY_MESSAGE, switch_mode=True)
    print(f'Leader is now: {self.pr_leader()}')
    for member in self.members.items():
      if member[0] < self.pid:
        peer = self.get_connection(member)
        if peer:
          self.set_state(State.SEND_VICTORY, peer, switch_mode=True)
  
  def update_members(self, their_data_of_membership):
    """Updates the dictionary of other members tracked by this member
    
    :param their_data_of_membership: The members to update within the dictionary
    """
  
    for pid, address in their_data_of_membership.items():
      self.members[pid] = address
  
  @classmethod # uses the class to know which receive method to call
  def send(cls, peer, message_name, message_data=None, wait_for_reply=False, buffer_size=BUF_SZ):
    """Sends a message to a peer
    
    :param peer: The member socket to send a message through
    :param message_name: The message name
    :param message_data: The data to send with the message
    :param wait_for_reply: Determines whether to receive a reply
    :param buffer_size: The size of the byte stream to receive
    :return: The message response if wait_for_reply is True, None otherwise
    """

    message = (message_name, message_data) if message_data else message_name
    peer.sendall(pickle.dumps(message))
    if wait_for_reply:
      return cls.receive(peer, buffer_size)

  @staticmethod
  def receive(peer, buffer_size=BUF_SZ):
    """Receives a message through a provided peer
    
    :param peer: The member socket to receive a message through
    :param buffer_size: The size of the byte stream to receive
    :return: The unpickled message
    """

    message = peer.recv(buffer_size)
    return pickle.loads(message)

  @staticmethod
  def get_unused_port():
    """Generates a random port number
    
    :return: A random port number
    """

    sock = socket.socket()
    sock.bind(('', 0))
    _, port = sock.getsockname()
    sock.close()
    return port

  @staticmethod
  def start_a_server():
    """Generates an address such that other members can connect to this member
    
    :return: The (socket, address) pair for this member
    """

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM | socket.SOCK_NONBLOCK)
    server_address = ('localhost', (BullyGroupMember.get_unused_port()))
    server_socket.bind(server_address)
    server_socket.listen(5)
    return server_socket, server_address

  def join_group(self):
    """Connects to the Group Coordinator Daemon and joins the group
    
    :return: Response from the GCD containing the members of the group
    """

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM | socket.SOCK_NONBLOCK) as gcd_sock:
      gcd_sock.settimeout(ASSUME_FAILURE_TIMEOUT)
      try:
        gcd_sock.connect(self.gcd_address)
      except socket.error as err:
        print(f'Failed to join group: {err}')
        exit(1)
      else:
        self.send(gcd_sock, State.SEND_JOIN.value, (self.pid, self.listener_address))
        response = self.receive(gcd_sock)
    return response
  
  @staticmethod
  def pr_now():
    """Printing helper for current timestamp."""

    return dt.now().strftime('%H:%M:%S.%f')
  
  def pr_sock(self, sock):
    """Printing helper for given socket."""

    if sock is None or sock == self or sock == self.listener:
      return 'self'
    return self.cpr_sock(sock)
  
  @staticmethod
  def cpr_sock(sock):
    """Static version of helper for printing given socket."""

    l_port = sock.getsockname()[1] % PEER_DIGITS_MODULUS
    l_port = f'0{l_port}' if l_port < PEER_DIGITS_DISPLAY else str(l_port)
    try:
      r_port = sock.getpeername()[1] % PEER_DIGITS_MODULUS
    except OSError:
      r_port = '??'
    else:
      r_port = f'0{r_port}' if r_port < PEER_DIGITS_DISPLAY else str(r_port)

    return f'{l_port}->{r_port} ({id(sock)})'
  
  def pr_leader(self):
    """Printing helper for current leader's name."""

    return 'unknown' if self.bully is None else ('self' if self.bully == self.pid else self.bully)

def main():
  """Executes the Bully algorithm through the BullyGroupMember"""

  # Check sufficient number of args
  if len(sys.argv) != 5:
    print('USAGE: python3 lab2.py <host> <port> <nextbirthday> <suid>')
    exit(1)

  # Get command line arguments
  host, port = sys.argv[1], int(sys.argv[2])
  bday, suid = dt.strptime(sys.argv[3], '%Y-%m-%d'), int(sys.argv[4])

  # Run bully algorithm group member
  member = BullyGroupMember(host, port, bday, suid)
  member.run()

if __name__ == '__main__':
  main()
