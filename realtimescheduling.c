#include <stdio.h>
#include <stdlib.h>

#define NUM_TASKS 3
#define SIMULATION_TIME 10

typedef struct {
    int id, period, exec_time, deadline, remain_time, weight;
} Task;

void init_tasks(Task tasks[], int weights[]);
void schedule(Task tasks[], int sim_time, int (*select_task)(Task[], int, int));
int select_rm(Task tasks[], int num_tasks, int time);
int select_edf(Task tasks[], int num_tasks, int time);
int select_ps(Task tasks[], int num_tasks, int time);

int main() {
    int weights[NUM_TASKS] = {1, 2, 3};
    Task tasks[NUM_TASKS];

    printf("Rate-Monotonic Scheduling:\n");
    init_tasks(tasks, weights);
    schedule(tasks, SIMULATION_TIME, select_rm);

    printf("\nEarliest Deadline First Scheduling:\n");
    init_tasks(tasks, weights);
    schedule(tasks, SIMULATION_TIME, select_edf);

    printf("\nProportional Scheduling:\n");
    init_tasks(tasks, weights);
    schedule(tasks, SIMULATION_TIME, select_ps);

    return 0;
}

void init_tasks(Task tasks[], int weights[]) {
    int periods[NUM_TASKS] = {5, 10, 15};
    int exec_times[NUM_TASKS] = {1, 2, 3};
    for (int i = 0; i < NUM_TASKS; i++) {
        tasks[i] = (Task){i + 1, periods[i], exec_times[i], periods[i], exec_times[i], weights[i]};
    }
}

void schedule(Task tasks[], int sim_time, int (*select_task)(Task[], int, int)) {
    for (int time = 0; time < sim_time; time++) {
        for (int i = 0; i < NUM_TASKS; i++)
            if (time % tasks[i].period == 0)
                tasks[i].remain_time = tasks[i].exec_time;
        int task_id = select_task(tasks, NUM_TASKS, time);
        if (task_id != -1) {
            tasks[task_id].remain_time--;
            printf("Time %d: Task %d\n", time, tasks[task_id].id);
        } else {
            printf("Time %d: Idle\n", time);
        }
    }
}

int select_rm(Task tasks[], int num_tasks, int time) {
    Task *selected = NULL;
    for (int i = 0; i < num_tasks; i++)
        if (tasks[i].remain_time > 0 && (!selected || tasks[i].period < selected->period))
            selected = &tasks[i];
    return selected ? selected - tasks : -1;
}

int select_edf(Task tasks[], int num_tasks, int time) {
    Task *selected = NULL;
    for (int i = 0; i < num_tasks; i++) {
        if (time % tasks[i].period == 0)
            tasks[i].deadline = time + tasks[i].period;
        if (tasks[i].remain_time > 0 && (!selected || tasks[i].deadline < selected->deadline))
            selected = &tasks[i];
    }
    return selected ? selected - tasks : -1;
}

int select_ps(Task tasks[], int num_tasks, int time) {
    Task *selected = NULL;
    for (int i = 0; i < num_tasks; i++)
        if (tasks[i].remain_time > 0 && (!selected || tasks[i].weight > selected->weight))
            selected = &tasks[i];
    return selected ? selected - tasks : -1;
}
