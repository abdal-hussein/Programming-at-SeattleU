/* Justin Thoreson
 * CPSC 3500 Computing Systems
 * HW6: server.cpp
 * 02 June 2021
 *
 * This program servers as the server portion of the number guessing game.
 * The server must be given a port number in the command line upon execution.
 * At this point, clients that have the server's IP address and the port number
 * can connect to the server and start playing the game.
 *
 * Have fun!
 */


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include "pthread.h"
#include <unistd.h>
#include <cstdlib>
#include <semaphore.h>
#include <cstring>
#include <algorithm>

using namespace std;


struct ThreadArgs
{
  int clientSock;
};

struct Player
{
  string name = "";
  long turns = 0;
};

struct LeaderBoard
{
  Player first;
  Player second;
  Player third;
};


// Global vars for leaderboard and semaphores
int player_count = 0;
sem_t mutex;
sem_t player_mutex;
LeaderBoard top3;


void error(char* msg);
// PRECONDITION: System call fails
// POSTCONDITION: Error message is displayed and program is aborted

void* threadMain(void *args);
// PRECONDITION: Client has connected to the server
// POSTCONDITION: Client has finished processing and socket is closed

void processClient(int clientSock);
// PRECONDITION: Thread for the client has been created
// POSTCONDITION: Player guessed the right number and the game has ended

void updateLeaderBoard(string playerName, long turns);
// PRECONDITION: Client guessed the correct number
// POSTCONDITION: Leader board is updated if client made the top three


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "ERROR: No port provided\n");
    exit(1);
  }

  // 1. Initialize semaphores
  sem_init(&mutex, 0, 1);
  sem_init(&player_mutex, 0, 1);
  
  int sockfd, portno;
  struct sockaddr_in serv_addr;

  // 2. Create a new socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error((char *) "ERROR opening socket");

  // 3. Get port number and set server address
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  // 4. Bind socket to address
  if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    error((char *) "ERROR on binding");

  // 5. Listen for connections
  listen(sockfd, 5);
  
  while (true)
  {
    // 5a. Accept connection from client
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    int clientSock = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (clientSock < 0) exit(-1);

    // 5b. Create and initialize argument struct
    ThreadArgs* threadArgs = new ThreadArgs;
    threadArgs->clientSock = clientSock;

    // 5c. Create client thread
    pthread_t threadID;
    int status = pthread_create(&threadID, NULL, threadMain,(void *) threadArgs);
    if (status != 0) exit(-1);
  }
  
  return 0;
}


void error(char* msg)
{
  perror(msg);
  exit(1);
}

void* threadMain(void *args)
{
  // 1. Extract socket file descriptor from argument
  struct ThreadArgs* threadArgs = (struct ThreadArgs *) args;
  int clientSock = threadArgs->clientSock;
  delete threadArgs;

  // 2. Communicate with client
  processClient(clientSock);

  // 3. Reclaim resources before finishing
  pthread_detach(pthread_self());
  close(clientSock);
  pthread_exit(NULL);
}

void processClient(int clientSock)
{
  char buffer[550];
  int n;
  string playerName;
  
  // 1. Read client provided name from socket
  bzero(buffer, 549);
  n = recv(clientSock, (void *) buffer, 549, 0);
  if (n < 0) error((char *) "ERROR reading from socket");
  printf("Player has joined: %s", buffer);
  playerName = buffer;
  playerName.erase(remove(playerName.begin(), playerName.end(), '\n'), playerName.end());  
  
  // 2. Generate random number for the client to guess
  srand(time(NULL));
  int max = 999;
  int magicNumber = rand() % max;
  printf("They must guess: %d\n", magicNumber);
  
  // 3. Get client guesses
  long guess;
  long turns = 0;
  do
  {
    turns++;

    // 3a. Send turn number to client
    long networkInt_turn = htonl(turns);
    int bytesSent_turn = send(clientSock, (void *) &networkInt_turn, sizeof(long), 0);
    if (n < 0) error((char *) "ERROR writing to socket"); 

    // 3b. Receive guess from client
    int bytesLeft_guess = sizeof(long);
    long networkInt_guess;
    char *bp = (char *) &networkInt_guess;
    while (bytesLeft_guess)
    {
      int bytesRecv_guess = recv(clientSock, bp, bytesLeft_guess, 0);
      if (bytesRecv_guess <= 0) exit(-1);
      bytesLeft_guess = bytesLeft_guess - bytesRecv_guess;
      bp = bp + bytesRecv_guess;
    }

    guess = ntohl(networkInt_guess);

    // 3c. Check guess result
    if (guess < magicNumber)
    {
      n = send(clientSock, (void *) "Too low!", 18, 0);
      if (n < 0) error((char *) "ERROR writing to socket");
    }

    else if (guess > magicNumber)
    {
      n = send(clientSock, (void *) "Too high!", 18, 0);
      if (n < 0) error((char *) "ERROR writing to socket");
    }
    
  }while (guess != magicNumber);
  
  // 4. Send message indicating a correct guess
  n = send(clientSock, (void *) "Correct guess!", 18, 0);
  if (n < 0) error((char *) "ERROR writing to socket");

  // 5. Send final number of turns for victory message
  long networkInt_turns = htonl(turns);
  int bytesSent_turns = send(clientSock, (void *) &networkInt_turns, sizeof(long), 0);
  if (n < 0) error((char *) "ERROR writing to socket");

  // 6. Update and send leader board
  sem_wait(&mutex);
  player_count++;
  if (player_count == 1)
    sem_wait(&player_mutex);
  sem_post(&mutex);

  updateLeaderBoard(playerName, turns);   
  
  // 6a. Create leader board message
  string first = "";
  string second = "";
  string third = "";
  
  if (top3.first.turns != 0)
    first = "1. " + top3.first.name + " " + to_string(top3.first.turns) + "\n";
  if (top3.second.turns != 0)
    second = "2. " + top3.second.name + " " + to_string(top3.second.turns) + "\n";
  if (top3.third.turns != 0)
    third = "3. " + top3.third.name + " " + to_string(top3.third.turns) + "\n";

  // 6b. Convert message from string to char array for sending
  string lb_str = first + second + third;
  char lb[lb_str.size() + 1];
  strcpy(lb, lb_str.c_str());

  n = send(clientSock, (void *) lb, 500, 0);
  if (n < 0) error((char *) "ERROR writing to socket");
  
  sem_wait(&mutex);
  player_count--;
  if (player_count == 0 )
    sem_post(&player_mutex);
  sem_post(&mutex);
}

void updateLeaderBoard(string playerName, long turns)
{
  if (top3.first.turns == 0)
  {
    top3.first.name = playerName;
    top3.first.turns = turns;
  }

  else if (top3.second.turns == 0)
  {
    if (turns < top3.first.turns)
    {
      top3.second.name = top3.first.name;
      top3.second.turns = top3.first.turns;
      top3.first.name = playerName;
      top3.first.turns = turns;
    }

    else
    {
      top3.second.name = playerName;
      top3.second.turns = turns;
    }
  }

  else if (top3.third.turns == 0)
  {
    if (turns < top3.first.turns)
    {
      top3.third.name = top3.second.name;
      top3.third.turns = top3.second.turns;
      top3.second.name = top3.first.name;
      top3.second.turns = top3.first.turns;
      top3.first.name = playerName;
      top3.first.turns = turns;
    }

    else if (turns < top3.second.turns)
    {
      top3.third.name = top3.second.name;
      top3.third.turns = top3.second.turns;
      top3.second.name = playerName;
      top3.second.turns = turns;
    }

    else
    {
      top3.third.name = playerName;
      top3.third.turns = turns;
    }
  }

  else
  {
    if (turns < top3.first.turns)
    {
      top3.third.name = top3.second.name;
      top3.third.turns = top3.second.turns;
      top3.second.name = top3.first.name;
      top3.second.turns = top3.first.turns;
      top3.first.name = playerName;
      top3.first.turns = turns;
    }

     else if (turns >= top3.first.turns && turns < top3.second.turns)
    {
      top3.third.name = top3.second.name;
      top3.third.turns = top3.second.turns;
      top3.second.name = playerName;
      top3.second.turns = turns;
    }

    else if (turns >= top3.second.turns && turns < top3.third.turns)
    {
      top3.third.name = playerName;
      top3.third.turns = turns;
    }
  }
}
