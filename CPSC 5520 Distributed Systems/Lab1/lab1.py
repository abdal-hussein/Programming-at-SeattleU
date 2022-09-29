"""
CPSC 5520, Seattle University
This is free and unencumbered software released into the public domain.
:Authors: Justin Thoreson
:Version: f22
"""

import socket
import pickle
import sys

BUF_SZ: int = 1024  # Per Prof. Lundeen: TCP receive buffer size
CON_TO: float = 1.5 # Connection timeout in seconds

class GCDClient(object):
  """
  Client designated for connecting to the Group Coordinator Daemon 
  and handling connections to potential members of the GCD's group.
  """

  def __init__(self, host: str, port: int) -> None:
    """
    Initializes client with Group Coordinator Daemon host and port

    :param host: The host origin of the GCD
    :param port: The port number of the GCD
    """ 

    self.host: str = host
    self.port: int = port
    self.group: list = []

  def connect_to_gcd(self) -> None:
    """
    Connects to the Group Coordinator Daemon
    """

    # Establish connection and send join message
    print(f"JOIN ({self.host}, {self.port})")
    response = GCDClient.connect(self.host, self.port, "JOIN")
    if type(response) is list:
      self.group = response
    else:
      print(response)

  def connect_to_members(self) -> None:
    """
    Connects to group members
    """

    for member in self.group:

      # Get host and port of current member
      host: str = member["host"]
      port: int = member["port"]

      # Establish connection and send join message
      print(f"HELLO to {member}")
      response = GCDClient.connect(host, port, "HELLO")
      print(response)

  @staticmethod
  def connect(host: str, port: int, msg: str):
    """
    Establishes a connection between the client and a server to transmit a message

    :param host: The host origin of the particular server
    :param port: The port number of the particular server
    :param msg: The message to transmit to the server
    :return: The message received from the server
    """
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

        # Connect and attempt to transmit message
        s.settimeout(CON_TO)
        try:
          s.connect((host, port))
        except socket.error as err:
          response = f"Failed to connect: {err}"
        else:
          response = GCDClient.transmit_message(s, msg)

        # Close connection when finished
        s.close()
        return response

  @staticmethod
  def transmit_message(s: socket.socket, msg: str):
    """
    Sends a message to a group member and receives a response
    
    :param s: The socket to send the message through
    :param msg: The message to send through the socket connection
    :response: The message received from the server
    """

    pickled_msg: bytes = pickle.dumps(msg)
    s.sendall(pickled_msg)
    raw_response: bytes = s.recv(BUF_SZ)

    # Per Prof. Lundeen: Check for pickled response
    try:
      response = pickle.loads(raw_response)
    except (pickle.PickleError, KeyError, EOFError):
      response = f'Expected a pickled message, got {str(raw_response)[:100]}'
    return response

def main() -> None:
  """
  Runs against the Group Coordinator Daemon
  """

  # Check sufficient number of arguments
  if len(sys.argv) != 3:
    print("USAGE: python3 lab1.py <host> <port>")
    exit(1)

  # Get host and port of GCD
  host: str = sys.argv[1]
  port: int = int(sys.argv[2])

  # Connect to GCD server w/ provided host and port
  client = GCDClient(host, port)
  client.connect_to_gcd()
  client.connect_to_members()

if __name__ == "__main__":
  main()
