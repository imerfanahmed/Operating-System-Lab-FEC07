#include <stdio.h>
#include <limits.h>

struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

// Function to find the waiting time for all processes
void findWaitingTime(struct Process proc[], int n, int wt[]) {
    int rt[n];
    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    int check = 0; // changed boolean to integer

    // Process until all processes are completed
    while (complete != n) {
        // Find process with minimum remaining time among the processes that arrive till the current time
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = 1; // changed boolean to integer
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely executed
        if (rt[shortest] == 0) {
            // Increment complete
            complete++;
            check = 0; // changed boolean to integer

            // Find finish time of current process
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        // Increment time
        t++;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    // calculating turnaround time by adding bt[i] + wt[i]
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to calculate average time
void findavgTime(struct Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(proc, n, wt);

    // Function to find turn around time for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Display processes along with all details
    printf(" P\t\t"
           "BT\t\t"
           "WT\t\t"
           "TAT\t\t\n");

    // Calculate total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        printf(" %d\t\t"
               "%d\t\t %d"
               "\t\t %d\n",
               proc[i].pid, proc[i].bt, wt[i], tat[i]);
    }

    printf("\nAverage waiting time = "
           "%f",
           (float)total_wt / (float)n);
    printf("\nAverage turn around time = "
           "%f",
           (float)total_tat / (float)n);
}

// Driver code
int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *proc = (struct Process *)malloc(n * sizeof(struct Process));
    if (proc == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &proc[i].art);
        printf("Burst time: ");
        scanf("%d", &proc[i].bt);
        proc[i].pid = i + 1;
    }

    findavgTime(proc, n);

    // Free allocated memory
    free(proc);

    return 0;
}

// Enter the number of processes: 5
// Enter arrival time and burst time for each process:
// Process 1:
// Arrival time: 2
// Burst time: 6
// Process 2:
// Arrival time: 5
// Burst time: 2
// Process 3:
// Arrival time: 1
// Burst time: 8
// Process 4:
// Arrival time: 0
// Burst time: 3
// Process 5:
// Arrival time: 4
// Burst time: 4
//  P              BT              WT              TAT
//  1              6                7               13
//  2              2                0               2
//  3              8                14              22
//  4              3                0               3
//  5              4                2               6

// Average waiting time = 4.600000
// Average turn around time = 9.200000