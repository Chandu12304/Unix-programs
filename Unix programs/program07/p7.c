// Priority based Algorithm
#include <iostream>
using namespace std;

struct Process {
    int id;         // Process ID
    int burst;      // Burst time
    int priority;   // Priority of the process
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
};

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;    
    Process processes[numProcesses];
    // Input burst time and priority for each process
    for (int i = 0; i < numProcesses; i++) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burst;
        cout << "Enter priority for process " << processes[i].id << ": ";
        cin >> processes[i].priority;
    }
    // Sort processes by priority (lower number means higher priority)
    for (int i = 0; i < numProcesses - 1; i++) {
        for (int j = 0; j < numProcesses - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(processes[j], processes[j + 1]);
            }
        }
    }   
    // Calculate waiting time and turnaround time
    processes[0].waiting = 0; // First process has no waiting time
    processes[0].turnaround = processes[0].burst;
    for (int i = 1; i < numProcesses; i++) {
        processes[i].waiting = processes[i - 1].waiting + processes[i - 1].burst;
        processes[i].turnaround = processes[i].waiting + processes[i].burst;
    }
    // Calculate and display the average waiting and turnaround times
    int totalWaiting = 0, totalTurnaround = 0;
    cout << "\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < numProcesses; i++) {
        totalWaiting += processes[i].waiting;
        totalTurnaround += processes[i].turnaround;
        cout << processes[i].id << "\t\t" << processes[i].burst << "\t\t" << processes[i].priority << "\t\t" << processes[i].waiting << "\t\t" << processes[i].turnaround << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)totalWaiting / numProcesses << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaround / numProcesses << endl;
    return 0;
}
