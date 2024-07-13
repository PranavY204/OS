#include <stdio.h>


void findWaitingTime(int n, int bt[], int wt[], int at[], int tat[]);
void sortByBurstTime(int n, int process[], int bt[]);
void findWaitingTimeSJF(int n, int bt[], int at[], int process[], int wt[], int tat[]);
void printProcessDetails(int n, int process[], int bt[], int at[], int wt[], int tat[]);


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], at[n], process[n], wt[n], tat[n];

    // Input process details for FCFS

    for (int i = 0; i < n; i++) {
        printf("Enter burst time and arrival times for P%d: ", i);
        scanf("%d%d", &bt[i], &at[i]);
        process[i] = i; // Process IDs for FCFS
    }

    findWaitingTime(n, bt, wt, at, tat); // Calculate waiting time for FCFS
    // findTurnAroundTime(n, bt, wt, tat); // Calculate turnaround time

    printf("\nFCFS Scheduling:\n");
    printProcessDetails(n, process, bt, at, wt, tat);

    // sortByBurstTime(n, process, bt);

    findWaitingTimeSJF(n, bt, at, process, wt, tat);
    // findTurnAroundTimeSJF(n, bt, wt, tat);

    printf("\nSJF Scheduling:\n");
    printProcessDetails(n, process, bt, at, wt, tat);
    return 0;
}

void findWaitingTime(int n, int bt[], int wt[], int at[], int tat[]) {
    int ct[n]; // Completion time
    wt[0] = 0; // Waiting time for the first process is always 0
    ct[0] = bt[0] = at[0];
    tat[0] = ct[0] - bt[0];

    // Calculate waiting time for remaining processes using FCFS
    for (int i = 1; i < n; i++) {
        if (at[i] < ct[i-1]) ct[i] = ct[i-1] + bt[i];
        else ct[i] = at[i] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        if (wt[i] < 0) {
            wt[i] = 0; // Ensure waiting time is non-negative for FCFS
        }
    }
}



// Function to sort processes according to burst time for SJF
void sortByBurstTime(int n, int process[], int bt[]) {
    int min_idx;
    for (int i = 0; i < n - 2; i++) {
        min_idx = i;
        for (int j = i+1; j < n - 1; j++) {
            if (bt[j] < bt[i]) {
               min_idx = j;
            }
        }
        if (min_idx != i){
            int temp = bt[i];
            bt[i] = bt[min_idx];
            bt[min_idx] = temp;
            temp = process[i];
            process[i] = process[min_idx];
            process[min_idx] = temp;
        }
    }
    /* printf("Process\t Burst Time\n");
    for(int i = 0; i < n; i++){
        printf("%d\t\t %d\n", process[i], bt[i]);
    } */
}



// Function to simulate SJF scheduling
void findWaitingTimeSJF(int n, int bt[], int at[], int process[], int wt[], int tat[]) {
    int ct[n]; // Completion time and process IDs
    /* for (int i = 0; i < n; i++) {
        process[i] = i; // Store process IDs
    } */

    sortByBurstTime(n, process, bt); // Sort processes by burst time

    wt[0] = 0; // Waiting time for the first process is always 0
    ct[0] = bt[0];
    tat[0] = ct[0];
    // Calculate waiting time for remaining processes using SJF
    for (int i = 1; i < n; i++) {
        if (at[i] < ct[i-1]) ct[i] = ct[i-1] + bt[i];
        else ct[i] = at[i] + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        if (wt[i] < 0) {
            wt[i] = 0; // Ensure waiting time is non-negative (may not be necessary for SJF)
        }
    }
}

// Function to print process details
void printProcessDetails(int n, int process[], int bt[], int at[], int wt[], int tat[]) {
    printf("Process\t Burst Time\t Arrival Time\t Waiting Time\t Turn Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", process[i], bt[i], at[i], wt[i], tat[i]);
    }
    float avgWT, avgTAT;
    for(int i = 0; i < n; i++){
        avgWT += wt[i]; avgTAT = tat[i];
    }
    avgWT /= n;
    avgTAT /= n;
    printf("Avg. Waiting time: %f\n", avgWT);
    printf("Avg. Turnaround time: %f\n", avgTAT);
}
