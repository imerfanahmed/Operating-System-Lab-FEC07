#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int priority;   // Priority
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
};

// Function to sort processes by priority and then by arrival time
void sortProcesses(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority ||
               (proc[i].priority == proc[j].priority && proc[i].arrival > proc[j].arrival)) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process proc[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < proc[i].arrival) {
            currentTime = proc[i].arrival;
        }
        proc[i].waiting = currentTime - proc[i].arrival;
        currentTime += proc[i].burst;
        proc[i].turnaround = proc[i].waiting + proc[i].burst;
    }
}

// Function to print the processes along with their details
void printProcesses(struct Process proc[], int n) {
    printf("PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", proc[i].pid, proc[i].arrival, proc[i].burst, proc[i].priority, proc[i].waiting, proc[i].turnaround);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d%d%d", &proc[i].arrival, &proc[i].burst, &proc[i].priority);
    }

    sortProcesses(proc, n);
    calculateTimes(proc, n);
    printProcesses(proc, n);

    return 0;
}
// Enter the number of processes: 2
// Enter arrival time, burst time, and priority for process 1: 1 5 3
// Enter arrival time, burst time, and priority for process 2: 2 4 2
// PID     Arrival Burst   Priority        Waiting Turnaround
// 2       2       4       2               0       4
// 1       1       5       3               5       10
