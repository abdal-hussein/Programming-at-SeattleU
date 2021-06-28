/* Justin Thoreson
 * CPSC 3500 Computing Systems
 * HW2: srtf.cpp
 * 20 April 2021
 *
 * PURPOSE:
 *   This program is meant to simulate the Shortest Remaining Time First (SRTF)
 *   scheduling algorithm. Processes are scheduled based on which one, out of
 *   all processes that have arrived, has the lowest remaining burst time.
 *
 * INPUT:
 *   A file is taken as a command line argument.
 *   Usage: ./srtf INPUT_FILE.txt
 *
 * OUTPUT:
 *   The average turnaround time and average waiting time for all processes is
 *   displayed, followed by the order in which each job was processed alongside
 *   their respective termination times.
 *
 * SOURCES:
 *   - stackoverflow.com: answers regarding how to use custom comparators
 */

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <sstream>

using namespace std;


struct Process
{
  int processNum;
  int burstTime;
  int remainingBurstTime;
  int arrivalTime;
  int terminationTime;
  int turnaroundTime;
  int waitingTime;

  Process(): processNum(0) {}
  
  Process(int pNum, int burst, int remainingBurst, int arrival):
    processNum(pNum), burstTime(burst),
    remainingBurstTime(remainingBurst), arrivalTime(arrival)
  {}

  bool operator==(const struct Process& P2) const
    { return this->processNum == P2.processNum; }
  
};

// ProcessComparator struct used to sort processes
struct ProcessComparator
{
  bool operator()(const Process& P1, const Process& P2)
  {
    if (P1.arrivalTime == P2.arrivalTime)
    {
      if (P1.remainingBurstTime == P2.remainingBurstTime)
        return P1.processNum < P2.processNum;
      return P1.remainingBurstTime < P2.remainingBurstTime;
    }
    
    return P1.arrivalTime < P2.arrivalTime;
  }
};


void processFile(list<Process> &processes, char* argv[]);
// PURPOSE: Processes in a file are stored in a list
// PRECONDITION: File containing processes is unread
// POSTCONDITION: Processes are read and ordered by arrival time

void processJobs(list<Process> &processes,
                 vector<Process> &finished, vector<Process> &ordered);
// PURPOSE: Processes all jobs in the system via SRTF scheduling
// PRECONDITION: System is ready to process jobs. File had been read.
// POSTCONDITION: Jobs are processed to completion
  
float getAvgTurnaroundTime(vector<Process> processes);
// PURPOSE: Retrieves the average turnaround time for all processes
// PRECONDITION: Turnaround time has been calculated for all completed processes
// POSTCONDITION: Average of all turnaround times is calculated and returned

float getAvgWaitingTime(vector<Process> processes);
// PURPOSE: Retrieves the average waiting time for all processes
// PRECONDITION: Waiting time has been calculated for all completed processes
// POSTCONDITION: Average of all waiting times is calculated and returned

void printProcessOrder(vector<Process> &finished, vector<Process> &ordered);
// PURPOSE: Prints the order the jobs were processed
// PRECONDITION: All jobs have finished processing
// POSTCONDITION: Order and termination times of jobs is printed


int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    cout << "ERROR: Program requires exactly one input file\n"
         << "Usage: ./mas INPUT_FILE.txt\n";
    exit(1);
  }

  // Get processes from input file
  list<Process> processes;
  vector<Process> finished, ordered;
  processFile(processes, argv);

  // Run processes
  processJobs(processes, finished, ordered);
  
  // Get average turnaround and waiting times
  cout << "Average turnaround time: " << getAvgTurnaroundTime(finished) << endl
       << "Average waiting time: " << getAvgWaitingTime(finished) << endl;                                            \

  // Print the order of processes and their respective termination times
  printProcessOrder(finished, ordered);
  
  return 0;
}


void processFile(list<Process> &processes, char* argv[])
{
  ifstream file(argv[1]);
  if (file.fail())
  {
    cout << "ERROR: File either does not exist or has failed to open\n";
    exit(1);
  }

  string line;
  string processNum, burstTime, arrivalTime;
  while (getline(file, line) && !file.fail())
  {
    stringstream process(line);
    getline(process, processNum, ',');
    getline(process, burstTime, ',');
    getline(process, arrivalTime, ',');

    processes.push_back(Process(stoi(processNum), stoi(burstTime),
                                stoi(burstTime), stoi(arrivalTime)));
  }
  file.close();

  // Sort processes by arrival time, then burst time, then process number
  processes.sort(ProcessComparator());
}

void processJobs(list<Process> &processes,
                 vector<Process> &finished, vector<Process> &ordered)
{
  int currentTime = 0;
  Process last;
  while(!processes.empty())
  {
    // Find only arrived processes
    list<Process> arrived;
    list<Process>::iterator i;
    for (i = processes.begin(); i != processes.end(); i++)
      if (i->arrivalTime <= currentTime)
        arrived.push_back(Process(i->processNum, i->burstTime,
                                  i->remainingBurstTime, i->arrivalTime));

    if (!arrived.empty())
    {
      // Find process with shortest remaining burst
      Process current = arrived.front();
      for (i = arrived.begin(); i != arrived.end(); ++i)
      {
        if (i->remainingBurstTime < current.remainingBurstTime)
          current = Process(i->processNum, i->burstTime,
                            i->remainingBurstTime, i->arrivalTime);

        else if (i->remainingBurstTime == current.remainingBurstTime)
          if (i->processNum < current.processNum)
            current = Process(i->processNum, i->burstTime,
                              i->remainingBurstTime, i->arrivalTime);
      }

      // Once process is found, run it, decrementing its remaining burst
      current.remainingBurstTime--;
      for (i = processes.begin(); i != processes.end(); i++)
        if (i->processNum == current.processNum)
          i->remainingBurstTime--;

      // If process is finished, calculate stats
      if (current.remainingBurstTime == 0)
      {
        processes.remove(current);

        current.terminationTime = currentTime + 1;
        current.turnaroundTime = current.terminationTime - current.arrivalTime;
        current.waitingTime = current.turnaroundTime - current.burstTime;

        finished.push_back(current);
      }

      // Track the order in which each job is processed
      if (current.processNum != last.processNum)
      {
        ordered.push_back(current);
        last = current;
      }
    }

    currentTime++;
  }
}

float getAvgTurnaroundTime(vector<Process> processes)
{
  int numProcesses = processes.size();
  float totalTurnaround = 0;
  for (int i = 0; i < processes.size(); i++)
    totalTurnaround += processes[i].turnaroundTime;
  return totalTurnaround / numProcesses;
}

float getAvgWaitingTime(vector<Process> processes)
{
  int numProcesses = processes.size();
  float totalWait = 0;
  for (int i = 0; i < processes.size(); i++)
    totalWait += processes[i].waitingTime;
  return totalWait / numProcesses;
}

void printProcessOrder(vector<Process> &finished, vector<Process> &ordered)
{
  // Get ordered processes with termination times
  for (int i = 0; i < ordered.size(); i++)
    for (int j = 0; j < finished.size(); j++)
      if (ordered[i].processNum == finished[j].processNum)
        ordered[i].terminationTime = finished[j].terminationTime;

  // Print processes by order of completion
  for (int i = 0; i < ordered.size(); i++)  
    cout << ordered[i].processNum << '(' << ordered[i].terminationTime << ')'
         << ((i + 1 == ordered.size()) ? " " : ", "); 
  cout << endl;
}
