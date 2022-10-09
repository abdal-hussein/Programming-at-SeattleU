# Lab 2: Bully

Implements the Bully algorithm by expanding on Lab1. The lab2 bully group member connects to a Group Coordinator Daemon (GCD) to join a group. This group is fully 
interconnected. All members in the group work together to determine a leader based on the highest identity value of all active members.

### Protocols:
JOIN - Contacts the GCD on startup to join the group and access other members within the group\
ELECTION - Initiates an election to determine who the leader of the group is\
COORDINATE - Sent by the leader to all other members with lower indentity values to declare victory\
PROBE - Sent to the leader periodically by all members with lower indentity values to monitor the active status of the leader

### Files:
lab2.py - The bully algorithm group member\
gcd2.py - The GCD server (provided by professor)
