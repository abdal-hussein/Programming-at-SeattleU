/* Justin Thoreson
 * CPSC 2500 Computing Systems
 * HW2: mas.cpp
 * 20 April 2021
 *
 * SUMMARY:
 *   This program is meant to simulate the Multiqueue Adaptive Scheduling (MAS)
 *   algorithm, which utilizes three separate queues to schedule the processes
 *   that arrive in the system. When a process's remaining burst time exceeds a
 *   time quantum, that processes is pushed to the queue with the next lowest
 *   priority. EX: q0 --> q1, q1 --> q2
 *
 *   Queues:
 *     q0 - Highest priority, round robin with time quantum of 6 ms
 *     q1 - Second priority, round robin with time quantum of 12 ms
 *     q2 - Lowest priority, FCFS
 *
 * INPUT:
 *   A file is taken as a command line argument.
 *   Usage: ./mas INPUT_FILE.txt
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
#include <sstream>
#include <string>
#include <queue>
#include <list>

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
  
  Process(int pNum, int burst, int remainingBurst, int arrival):
    processNum(pNum), burstTime(burst),
    remainingBurstTime(remainingBurst), arrivalTime(arrival)
  {}
};

// ProcessComparator struct is used to sort the processes by arrival time
struct ProcessComparator
{
  bool operator()(const Process& P1, const Process& P2)
  {
    if (P1.arrivalTime == P2.arrivalTime)
      return P1.processNum < P2.processNum;
    return P1.arrivalTime < P2.arrivalTime;
  }
};


void processFile(queue<Process> &processes, char* argv[]);
// PURPOSE: Processes in a file are stored in the highest priority queue
// PRECONDITION: File containing processes is unread
// POSTCONDITION: Processes are read and ordered by arrival time

void runQueues(queue<Process> &q0, queue<Process> &q1, queue<Process> &q2,
               vector<Process> &finished, vector<Process> &ordered,
               int q0Quantum, int q1Quantum, int &currentTime);
// PURPOSE: Processes all the jobs in the system
// PRECONDITION: System is ready to schedule processes. File has been read
// POSTCONDITION: Processes have been scheduled and completed

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

  // Get processes from file
  queue<Process> q0, q1, q2;
  vector<Process> finished, ordered;
  processFile(q0, argv);

  // Run queues
  const int Q0_QUANTUM = 6;
  const int Q1_QUANTUM = 12;
  int currentTime = 0;
  runQueues(q0, q1, q1, finished, ordered, Q0_QUANTUM, Q1_QUANTUM, currentTime);

  // Get average turnaround and wait times
  cout << "Average turnaround time: " << getAvgTurnaroundTime(finished) << endl
       << "Average waiting time: " << getAvgWaitingTime(finished) << endl;

  // Print processes in order
  printProcessOrder(finished, ordered);
 
  return 0;
}


void processFile(queue<Process> &q0, char* argv[])
{
  ifstream file(argv[1]);
  if (file.fail())
  {
    cout << "ERROR: File either does not exist or has failed to open\n";
    exit(1);
  }
      
  list<Process> listOfProcesses;
  string line;
  string processNum, burstTime, arrivalTime;
  while (getline(file, line) && !file.fail())
  {
    stringstream process(line);
    getline(process, processNum, ',');
    getline(process, burstTime, ',');
    getline(process, arrivalTime, ',');
    
    listOfProcesses.push_back(Process(stoi(processNum), stoi(burstTime),
                                      stoi(burstTime), stoi(arrivalTime)));
  }
  file.close();

  // Sort processes by arrival time before pushing them to q0
  listOfProcesses.sort(ProcessComparator());
  
  while (!listOfProcesses.empty())
  {
    q0.push(listOfProcesses.front());
    listOfProcesses.pop_front();
  }
}

void runQueues(queue<Process> &q0, queue<Process> &q1, queue<Process> &q2,
               vector<Process> &finished, vector<Process> &ordered,
               int q0Quantum, int q1Quantum, int &currentTime)
{
  while (!(q0.empty() && q1.empty() && q2.empty()))
  {
    // If a process in q0 is available to run
    if (!q0.empty() && q0.front().arrivalTime <= currentTime)
    {
      Process front = q0.front();

      // Run current process until quantum duration is met
      if (front.remainingBurstTime > q0Quantum)
      {
        q1.push(Process(front.processNum, front.burstTime,
                        front.remainingBurstTime - q0Quantum, front.arrivalTime));
        currentTime += q0Quantum;
        q0.pop();
      }

      // Run process until completed
      else
      {
        currentTime += front.remainingBurstTime;
        front.remainingBurstTime = 0;

        front.terminationTime = currentTime;
        front.turnaroundTime = front.terminationTime - front.arrivalTime;
        front.waitingTime = front.turnaroundTime - front.burstTime;

        finished.push_back(front);
        q0.pop();
      }


      ordered.push_back(front);
    }

    // If there are no prcesses in q0, and q1 has an available process
    else if (!q1.empty() && q1.front().arrivalTime <= currentTime)
    {
      Process front = q1.front();

      // Run process until preempted by new arrival in q0
      if (!q0.empty() && (front.remainingBurstTime + currentTime > q0.front().arrivalTime))
      {
        front.remainingBurstTime -= (q0.front().arrivalTime - currentTime);
        currentTime = q0.front().arrivalTime;
        q1.pop();
        q1.push(front);
      }

      // Run process until quantum duration is met
      else if (front.remainingBurstTime > q1Quantum)
      {
        q2.push(Process(front.processNum, front.burstTime,
                        front.remainingBurstTime - q1Quantum, front.arrivalTime));
        currentTime += q1Quantum;
        q1.pop();
      }

      // Run process until completed
      else
      {
        currentTime += front.remainingBurstTime;
        front.remainingBurstTime = 0;

        front.terminationTime = currentTime;
        front.turnaroundTime = front.terminationTime - front.arrivalTime;
        front.waitingTime = front.turnaroundTime - front.burstTime;

        finished.push_back(front);
        q1.pop();
      }

      ordered.push_back(front);
    }

    // If there are no processes in q0 and q1, but there is a process in q2.
    else if (!q2.empty())
    {
      Process front = q2.front();

      // Run process until preempted by new arrival in q0
      if (!q0.empty() && (front.remainingBurstTime + currentTime > q0.front().arrivalTime))
      {
        front.remainingBurstTime -= (q0.front().arrivalTime - currentTime);
        currentTime = q0.front().arrivalTime;
        q2.pop();
        q2.push(front);
      }

      // Run process until preempted by new arrival in q1
      else if (!q1.empty() && (front.remainingBurstTime + currentTime > q1.front().arrivalTime))
      {
        front.remainingBurstTime -= (q1.front().arrivalTime - currentTime);
        currentTime = q1.front().arrivalTime;
        q2.pop();
        q2.push(front);
      }

      // Run process until completed
      else
      {
        currentTime += front.remainingBurstTime;
        front.remainingBurstTime = 0;

        front.terminationTime = currentTime;
        front.turnaroundTime = front.terminationTime - front.arrivalTime;
        front.waitingTime = front.turnaroundTime - front.burstTime;

        finished.push_back(front);
        q2.pop();
      }

      ordered.push_back(front);
    }
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
  // Get termination time in order
  for (int i = 0; i < ordered.size(); i++)
    for (int j = 0; j < finished.size(); j++)
      if (ordered[i].processNum == finished[j].processNum)
        ordered[i].terminationTime = finished[j].terminationTime;

  // Print order
  for (int i = 0; i < ordered.size(); i++)
    cout << ordered[i].processNum << '(' << ordered[i].terminationTime << ')'
         << ((i + 1 == ordered.size()) ? " " : ", ");
  cout << endl;
}
