// Priority based Algorithm

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;         // Process ID
    int burst;      // Burst time
    int priority;   // Priority of the process
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
};

// Comparison function to sort processes by burst, then priority, then id
bool compare(const Process &a, const Process &b) {
    if (a.burst != b.burst) return a.burst < b.burst;
    if (a.priority != b.priority) return a.priority < b.priority;
    return a.id < b.id;
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        processes[i].id = i + 1;
        cout << "Enter burst time for process " << processes[i].id << ": ";
        cin >> processes[i].burst;
        cout << "Enter priority for process " << processes[i].id << ": ";
        cin >> processes[i].priority;

        processes[i].waiting = 0;
        processes[i].turnaround = 0;
    }

    // Sort processes using the custom comparison function
    sort(processes.begin(), processes.end(), compare);


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
