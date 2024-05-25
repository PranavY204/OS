#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid; // Process ID
    int bt; // Burst Time
    int priority; // Priority
    int at; // Arrival Time
    int wt; // Waiting Time
    int tat; // Turnaround Time
    int rt; // Remaining Time for Preemptive
} Process;

// Function to sort processes by arrival time, and if equal by priority
void sort_by_at(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].at > processes[j + 1].at || 
               (processes[j].at == processes[j + 1].at && 
                processes[j].priority > processes[j + 1].priority)) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to calculate average waiting time and turnaround time
void calculate_average_times(Process processes[], int n) {
    int total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].wt;
        total_tat += processes[i].tat;
    }
    
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

// Function to print process details
void print_process_details(Process processes[], int n) {
    printf("PID\tBurst Time\tPriority\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                processes[i].pid, 
                processes[i].bt, 
                processes[i].priority, 
                processes[i].at, 
                processes[i].wt, 
                processes[i].tat);
    }
}

void preemptive_priority_scheduling(Process processes[], int n) {
    int time = 0, completed = 0, min_priority, shortest;
    int finish_time;
    int is_done[MAX_PROCESSES] = {0};

    sort_by_at(processes, n);
    
    while (completed != n) {
        min_priority = 999;
        shortest = -1;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && !is_done[i] &&
                processes[i].priority < min_priority && processes[i].rt > 0) {
                min_priority = processes[i].priority;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            time++;
            continue;
        }
        
        processes[shortest].rt--;
        if (processes[shortest].rt == 0) {
            completed++;
            finish_time = time + 1;
            processes[shortest].wt = finish_time - processes[shortest].bt - processes[shortest].at;
            processes[shortest].tat = finish_time - processes[shortest].at;
            if (processes[shortest].wt < 0) processes[shortest].wt = 0;
            is_done[shortest] = 1;
        }
        time++;
    }
    
    print_process_details(processes, n);
    calculate_average_times(processes, n);
}

void non_preemptive_priority_scheduling(Process processes[], int n) {
    int time = 0, completed = 0, min_priority, shortest;

    sort_by_at(processes, n);
    
    while (completed != n) {
        min_priority = 999;
        shortest = -1;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= time && processes[i].priority < min_priority && processes[i].rt > 0) {
                min_priority = processes[i].priority;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            time++;
            continue;
        }
        
        time += processes[shortest].bt;
        processes[shortest].rt = 0;
        processes[shortest].wt = time - processes[shortest].bt - processes[shortest].at;
        processes[shortest].tat = time - processes[shortest].at;
        if (processes[shortest].wt < 0) processes[shortest].wt = 0;
        completed++;
    }
    
    print_process_details(processes, n);
    calculate_average_times(processes, n);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time, priority, and arrival time for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].bt, &processes[i].priority, &processes[i].at);
        processes[i].rt = processes[i].bt;
    }

    printf("Choose the scheduling algorithm:\n");
    printf("1. Preemptive Priority Scheduling\n");
    printf("2. Non-Preemptive Priority Scheduling\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            preemptive_priority_scheduling(processes, n);
            break;
        case 2:
            non_preemptive_priority_scheduling(processes, n);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
