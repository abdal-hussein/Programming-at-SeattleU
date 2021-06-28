/* Justin Thoreson
 * CPSC3500 Computing Systems
 * HW3: vaccines.cpp
 * 05 May 2021
 *
 * SUMMARY:
 *  This program is meant to emulate the use of threads via counting the number
 *  of vaccines from three different brands amongst multiple cities.
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
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


struct Vaccines
{
  int v1 = 0;
  int v2 = 0;
  int v3 = 0;
};


void* countVaccines(void* filename);
// PRECONDITION: Each file contains a set number of vaccines amongst 3 brands
// POSTCONDITION: The vaccine count of each file is calculated via threads


int main(int argc, char* argv[])
{
  const string DIR = "/home/fac/mishraa/cpsc3500/pa3a/";
  const string CITY = "city";
  const string EXT = ".txt";
  const int NUM_CITIES = 21;
 
  pthread_t tid[NUM_CITIES];
  string filenames[NUM_CITIES];
  Vaccines count;
   
  // Create threads. Count vaccines in each city.
  for (int i = 0; i < NUM_CITIES; i++)
  {
    filenames[i] = DIR + CITY + to_string(i+1) + EXT;
    int status = pthread_create(&tid[i], NULL, countVaccines,
                                static_cast<void*>(&filenames[i]));
    if (status != 0)
    {
      cout << "Error occurred while creating a thread\n";
      exit(1);
    }   
  }

  // Join all threads. Get vaccine totals.
  for (int i = 0; i < NUM_CITIES; i++)
  {
    Vaccines* count_p;
    Vaccines** count_dp = &count_p;
    int status = pthread_join(tid[i], (void **) count_dp);
    if (status != 0)
    {
      cout << "Error occurred while joining a thread\n";
      exit(1);
    }

    // Get total vaccines
    count.v1 += count_p->v1;
    count.v2 += count_p->v2;
    count.v3 += count_p->v3;
    delete count_p;
  }

  // Print vaccine brand totals
  cout << "v1: " << count.v1 << endl
       << "v2: " << count.v2 << endl
       << "v3: " << count.v3 << endl;

  return 0;
}


void* countVaccines(void* filename)
{
  string &fn = *(static_cast<string*>(filename));
  ifstream file(fn);
  Vaccines count;
  string line;

  if (file.is_open())
  {
    while (getline(file, line))
    {
      if (line == "v1") count.v1++;
      else if (line == "v2") count.v2++;
      else if (line == "v3") count.v3++;
    }
    file.close();
  }

  else printf("ERROR: File failed to open\n");
  
  Vaccines* count_p = new Vaccines;
  *count_p = count;
  pthread_exit(count_p);
}
    
