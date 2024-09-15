//Round Robin Algorithm
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int numProcesses = 3; // Number of processes
    int timeQuantum = 4; // Time quantum for each process
    // Arrays for arrival times and burst times
    vector<int> arrivalTime = {0, 1, 2};
    vector<int> burstTime = {5, 8, 3};
    // Vector to keep track of remaining burst times
    vector<int> remainingTime = burstTime;
    int totalTime = 0; // Total time for scheduling
    int completedProcesses = 0;
    cout << "Process ID\tBurst Time\tTurnaround Time\tWaiting Time\n";
    while (completedProcesses < numProcesses) {
        for (int i = 0; i < numProcesses; i++) {
            if (remainingTime[i] > 0) {
                // Calculate the time spent on the current process
                int timeSpent = min(timeQuantum, remainingTime[i]);
                remainingTime[i] -= timeSpent;
                totalTime += timeSpent;
                // Print process details
                if (remainingTime[i] == 0) {
                    int turnaroundTime = totalTime - arrivalTime[i];
                    int waitingTime = turnaroundTime - burstTime[i];
                    cout << "Process[" << i + 1 << "]\t\t"
                         << burstTime[i] << "\t\t"
                         << turnaroundTime << "\t\t\t"
                         << waitingTime << endl;
                    completedProcesses++;
                }
            }
        }
    }
    return 0;
}
