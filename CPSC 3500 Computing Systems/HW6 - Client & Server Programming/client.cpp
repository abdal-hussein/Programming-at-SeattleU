/* Justin Thoreson
 * CPSC 3500 Computing Systems
 * HW6: client.cpp
 * 02 June 2021
 *
 * This program serves as the client portion of the number guessing game.
 * The client must connect by entering in the command line the IP address of the
 * network that the server is running on and the port number that the server has
 * been given.
 *
 * Have fun!
 */


#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <limits>

using namespace std;


void error(char *msg);
// PRECONDITION: System call fails
// POSTCONDITION: Error message is displayed and program is aborted


int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    fprintf(stderr,"usage %s hostname port", argv[0]);
    exit(0);
  }

  int sockfd, portno, n;
  char buffer[550];
  struct sockaddr_in serv_addr;
  struct hostent* server;

  // 1. Get port number and create socket
  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error((char *) "ERROR opening socket");

  // 2. Retrieve host name
  server = gethostbyname(argv[1]);
  if (server == NULL)
  {
    fprintf(stderr,"ERROR, no such host");
    exit(0);
  }
 
  // 3. Set server address
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);

  // 4. Connect to server
  if (connect(sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error((char *) "ERROR connecting");

  // 5. Send name of the user to the server
  printf("Welcome to the Number Guessing Game!\n");
  printf("Please enter your name: ");
  bzero(buffer, 550);
  fgets(buffer, 549, stdin);
  n = send(sockfd, (void *) buffer, strlen(buffer), 0);
  if (n < 0) error((char *) "ERROR writing to socket");
  printf("\n\n");
  
  // 6. Begin the game
  do
  {
    // 6a. Get turn number from server
    int bytesLeft_turn = sizeof(long);
    long networkInt_turn;
    char *bp = (char *) &networkInt_turn;
    while (bytesLeft_turn)
    {
      int bytesRecv_turn = recv(sockfd, bp, bytesLeft_turn, 0);
      if (bytesRecv_turn <= 0) exit(-1);
      bytesLeft_turn = bytesLeft_turn - bytesRecv_turn;
      bp = bp + bytesRecv_turn;
    }

    long turn = ntohl(networkInt_turn);
    printf("Turn: %d\n", turn);
    
    // 6b. Get guess from user
    printf("Enter a guess (0-999): ");
    double guessInput;
    cin >> guessInput;

    while (cin.fail() || guessInput < 0 || guessInput > 999)
    {
      printf("Invalid guess. Guess again (0-999): ");
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      cin >> guessInput;
    }
    
    long guess = static_cast<long>(guessInput);
    
    // 6c. Send guess to server
    long networkInt_guess = htonl(guess);
    int bytesSent_guess = send(sockfd, (void *) &networkInt_guess, sizeof(long), 0);
    if (n < 0) error((char *) "ERROR writing to socket");

    // 6d. Get guess result from server
    bzero(buffer, 550);
    n = recv(sockfd, (void *) buffer, 549, 0);
    if (n < 0) error((char *) "ERROR reading from socket");
    printf("Result of guess: %s\n\n", buffer);

  }while (buffer[0] != 'C');

  // 7. Get total number of turns taken from the server
  int bytesLeft_turns = sizeof(long);
  long networkInt_turns;
  char *bp = (char *) &networkInt_turns;
  while (bytesLeft_turns)
  {
    int bytesRecv_turns = recv(sockfd, bp, bytesLeft_turns, 0);
    if (bytesRecv_turns <= 0) exit(-1);
    bytesLeft_turns = bytesLeft_turns - bytesRecv_turns;
    bp = bp + bytesRecv_turns;
  }

  // 8. Display victory message w/ total turns taken
  long hostInt_turns = ntohl(networkInt_turns);
  printf("\nCongratulations! It took %d turns to guess the number!\n\n", hostInt_turns);

  // 9. Get leaderboard from server
  bzero(buffer, 550);
  n = recv(sockfd, (void *) buffer, 549, 0);
  if (n < 0) error((char *) "ERROR reading from socket");
  printf("\nLeader board:\n%s", buffer);
  
  return 0;
}


void error(char *msg)
{
  perror(msg);
  exit(0);
}
