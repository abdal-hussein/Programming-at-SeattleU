Justin Thoreson
CPSC 3500 Computing Systems
HW6: README.txt
02 June 2021

---------------------------

Files included in the submission:
server.cpp - solution for the server code
client.cpp - solution for the client code

---------------------------

For server.cpp:
1) To compile, run: g++ server.cpp -std=c++11 -lpthread -o server
2) To execute, run: ./server <portno>
   - Replace <portno> with the port number
3) To terminate in cs1: Ctrl+C

For client.cpp:
1) To compile, run: g++ client.cpp -std=c++11 -o client
2) To execute, run: ./client <ipaddr> <portno>
   - Replace <ipaddr> with the IP address (of cs1: 10.124.72.20)
   - Replace <portno> with the same port number used during server execution

---------------------------

