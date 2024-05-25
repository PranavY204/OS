#include <stdio.h>
#include <stdbool.h>

// Process structure
struct Process {
    int pid;        // Process ID
    int bt;         // Burst Time
    int at;         // Arrival Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
    int rt;         // Remaining Time
};

// Function to find waiting time for SJF Preemptive
void findWaitingTimeSJF(struct Process proc[], int n) {
    int complete = 0, t = 0, minm = 1e9;
    int shortest = 0, finish_time;
    bool check = false;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].at <= t) && (proc[j].rt < minm) && proc[j].rt > 0) {
                minm = proc[j].rt;
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        // proc[shortest].rt--;
        minm = --proc[shortest].rt;
        if (minm == 0)
            minm = 1e9;

        if (proc[shortest].rt == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            proc[shortest].tat = finish_time - proc[shortest].at;
            proc[shortest].wt = proc[shortest].tat - proc[shortest].bt;

            if (proc[shortest].wt < 0)
                proc[shortest].wt = 0;
        }
        t++;
    }
}

// Function to implement Round Robin scheduling
void findWaitingTimeRR(struct Process proc[], int n, int quantum) {
    int t = 0;
    int rem_bt[n];
    for (int i = 0; i < n; i++)
        rem_bt[i] = proc[i].bt;

    while (1) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    proc[i].tat = t - proc[i].at;
                    proc[i].wt = (proc[i].tat - proc[i].bt) > 0 ? (proc[i].tat - proc[i].bt) : 0;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
            break;
    }
}

// Function to find turnaround time for Round Robin


// Function to print the results
void printResults(struct Process proc[], int n) {
    printf("Process\t Burst Time\t Arrival Time\t Waiting Time\t Turn Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", proc[i].pid, proc[i].bt, proc[i].at, proc[i].wt, proc[i].tat);
    }
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time and arrival time for P%d: ", i);
        scanf("%d%d", &proc[i].bt, &proc[i].at);
        proc[i].pid = i;
        proc[i].rt = proc[i].bt;
    }

    // SJF Preemptive
    findWaitingTimeSJF(proc, n);
    // findTurnAroundTimeSJF(proc, n);
    printf("\nSJF Preemptive Scheduling:\n");
    printResults(proc, n);

    // Reset waiting time and turnaround time for Round Robin
    for (int i = 0; i < n; i++) {
        proc[i].wt = 0;
        proc[i].tat = 0;
    }

    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    // Round Robin
    findWaitingTimeRR(proc, n, quantum);
    // findTurnAroundTimeRR(proc, n);
    printf("\nRound Robin Scheduling:\n");
    printResults(proc, n);

    return 0;
}
