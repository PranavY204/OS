#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

int numProcesses, numResources;
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];

void inputMatrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], const char *name) {
    printf("Enter the %s matrix:\n", name);
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < numResources; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void inputArray(int array[MAX_RESOURCES], const char *name) {
    printf("Enter the %s array:\n", name);
    for (int i = 0; i < numResources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &array[i]);
    }
}

bool isDeadlocked(int visited[], int process, bool waitForGraph[MAX_PROCESSES][MAX_PROCESSES]) {
    if (visited[process] == 1) {
        return true;
    }
    if (visited[process] == 2) {
        return false;
    }

    visited[process] = 1; // Mark as visited

    for (int i = 0; i < numProcesses; i++) {
        if (waitForGraph[process][i]) {
            if (isDeadlocked(visited, i, waitForGraph)) {
                return true;
            }
        }
    }

    visited[process] = 2; // Mark as processed
    return false;
}

void detectDeadlock() {
    bool waitForGraph[MAX_PROCESSES][MAX_PROCESSES] = {false};

    // Build the wait-for graph
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            if (request[i][j] > 0) {
                for (int k = 0; k < numProcesses; k++) {
                    if (allocation[k][j] > 0) {
                        waitForGraph[i][k] = true;
                    }
                }
            }
        }
    }

    // Detect cycle in the wait-for graph
    int visited[MAX_PROCESSES] = {0}; // 0 = not visited, 1 = visiting, 2 = visited
    for (int i = 0; i < numProcesses; i++) {
        if (isDeadlocked(visited, i, waitForGraph)) {
            printf("Deadlock detected involving process %d\n", i);
        }
    }
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &numResources);

    inputArray(available, "available");
    inputMatrix(allocation, "allocation");
    inputMatrix(request, "request");

    detectDeadlock();

    return 0;
}
