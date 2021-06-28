/* Justin Thoreson
 * CPSC3500 Computing Systems
 * HW3: social_distancing.cpp
 * 05 May 2021
 *
 * SUMMARY:
 *  This program is meant to simulate vaccinated and non vaccinated kids playing
 *  in a playground during the covid19 pandemic. This is done through the use of
 *  threads, where each thread represents a kid, vaccinated or not, and
 *  semaphores which help regulate how many kids can play on the playground at a
 *  single time given their vaccination statuses.
 *
 * SOURCES:
 *  - stackoverflow.com for pthread function usage
 *    - https://stackoverflow.com/questions/27468945/create-pthreads-in-loop
 *      - Calling a join immediately after a create makes the threads sequential
 *      - Keeping the creates separate from the joins ensures threads that have
 *        been created can behave properly
 *  - Dr. Mishra's slides for Unit 3
 *    - Casting for void pointers
 */


#include "pthread.h"
#include <semaphore.h>
#include <unistd.h>
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <string>

using namespace std;


// Global vars for mutual exclusion
int vaccinated_kids_count = 0;
sem_t mutex;
sem_t play_mutex;


struct Kid
{
  string status;
  pthread_t tid;
  int kidNum;
};


void createThreads(Kid* kids, int numKids);
// PRECONDITION: Number of kids/threads has been provided
// POSTCONDITION: Threads are created

void joinThreads(Kid* kids, int numKids);
// PRECONDITION: Threads have undergone their functions
// POSTCONDITION: Threads are joined

void* threadFunc_V(void* kid);
// PRECONDITION: Vaccinated kid/thread has been provided
// POSTCONDITION: Semaphores allow kids to play on the structure safely

void* threadFunc_NV(void* kid);
// PRECONDITION: Nonvaccinated kid/thread has been provided
// POSTCONDITION: Semaphores allow kids to play on the structure safely

void play(Kid* kid);
// PRECONDITION: play_mutex has been aquired by the thread
// POSTCONDITION: Kid plays on the structure


int main(int argc, char* argv[])
{
  if (argc != 3 || !(isdigit(*argv[1]) && isdigit(*argv[2])))
  {
    printf("ERROR: Invalid arguments: Two integers must be provided\n");
    printf("Enter the number of vaccinated (V) and non-vaccinated (NV) kids\n");
    printf("Usage: ./social_distancing 'V' 'NV'\n");
    exit(1);
  }

  // Initialize semaphores
  sem_init(&mutex, 0, 1);
  sem_init(&play_mutex, 0, 1);

  // Get num kids
  int numVaccinated = atoi(argv[1]);
  int numNonVaccinated = atoi(argv[2]);
  int numKids = numVaccinated + numNonVaccinated;
  Kid* kids = new Kid[numKids];

  // Initialize kid stats
  for (int i = 0; i < numKids; i++)             kids[i].kidNum = i + 1;
  for (int i = 0; i < numVaccinated; i++)       kids[i].status = "V";
  for (int i = numVaccinated; i < numKids; i++) kids[i].status = "NV";

  // Run threads
  createThreads(kids, numKids);
  joinThreads(kids, numKids);
  
  delete [] kids;
  return 0;
}

void createThreads(Kid* kids, int numKids)
{
  for (int i = 0; i < numKids; i++)
  {
    int status;

    // Create V threads
    if (kids[i].status == "V")
      status = pthread_create(&kids[i].tid, NULL, threadFunc_V,
                              static_cast<void*>(&kids[i]));

    // Create NV threads
    else if (kids[i].status == "NV")
      status = pthread_create(&kids[i].tid, NULL, threadFunc_NV,
                              static_cast<void*>(&kids[i]));

    if (status != 0)
    {
      printf("Error occurred while creating a thread\n");
      exit(1);
    }
  }
}

void joinThreads(Kid* kids, int numKids)
{
  for (int i = 0; i < numKids; i++)
  {
    int status = pthread_join(kids[i].tid, NULL);
    if (status != 0)
    {
      printf("Error occurred while joining a thread\n");
      exit(1);
    }
  }
}

void* threadFunc_V(void* kid)
{
  Kid &child = *(static_cast<Kid*>(kid));

  do
  {
    sem_wait(&mutex);
    printf("%s Thread %i acquired mutex for incrementing the count.\n",
           child.status.c_str(), child.kidNum);
    
    vaccinated_kids_count++;
    if (vaccinated_kids_count == 1)
    {
      printf("%s Thread %i trying to acquire play_mutex.\n",
             child.status.c_str(), child.kidNum);    
      sem_wait(&play_mutex);
    }

    printf("%s Thread %i about to release mutex after incrementing.\n",
           child.status.c_str(), child.kidNum);
    sem_post(&mutex);

    // Play at structure
    play(&child);
    
    sem_wait(&mutex);
    printf("%s Thread %i acquired mutex for decrementing the count.\n",
           child.status.c_str(), child.kidNum);
    
    vaccinated_kids_count--;
    if (vaccinated_kids_count == 0)
    {
      printf("%s Thread %i about to release play_mutex.\n",
             child.status.c_str(), child.kidNum);  
      sem_post(&play_mutex);
    }

    printf("%s Thread %i about to release mutex after decrementing.\n",
           child.status.c_str(), child.kidNum);
    sem_post(&mutex);
    sleep(1);
  }while(true);
  
  pthread_exit(NULL);
}

void* threadFunc_NV(void* kid)
{
  Kid &child = *(static_cast<Kid*>(kid));

  do
  {
    printf("%s Thread %i trying to acquire play_mutex.\n",
           child.status.c_str(), child.kidNum);  
    sem_wait(&play_mutex);

    // Play at structure
    play(&child);
    
    sem_post(&play_mutex);
    sleep(1);
  }while(true);
}

void play(Kid* kid)
{
  printf("%s Thread %i playing!\n", kid->status.c_str(), kid->kidNum);
  sleep(1);
  printf("%s Thread %i playing done!\n", kid->status.c_str(), kid->kidNum);
}
