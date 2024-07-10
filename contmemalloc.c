#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

// Function declarations
void worstFit(int blocks[], int blockCount, int processes[], int processCount);
void bestFit(int blocks[], int blockCount, int processes[], int processCount);
void firstFit(int blocks[], int blockCount, int processes[], int processCount);
void printAllocation(int allocation[], int processCount);

int main() {
    int blocks[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int processes[MAX_PROCESSES] = {212, 417, 112, 426};

    int blockCount = 5;  // Number of memory blocks
    int processCount = 4;  // Number of processes

    printf("Worst Fit Allocation:\n");
    worstFit(blocks, blockCount, processes, processCount);

    printf("\nBest Fit Allocation:\n");
    bestFit(blocks, blockCount, processes, processCount);

    printf("\nFirst Fit Allocation:\n");
    firstFit(blocks, blockCount, processes, processCount);

    return 0;
}

void worstFit(int blocks[], int blockCount, int processes[], int processCount) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processCount; i++) {
        allocation[i] = -1;  // Initialize allocation as -1 (not allocated)
    }

    for (int i = 0; i < processCount; i++) {
        int worstIndex = -1;
        for (int j = 0; j < blockCount; j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIndex == -1 || blocks[j] > blocks[worstIndex]) {
                    worstIndex = j;
                }
            }
        }

        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blocks[worstIndex] -= processes[i];
        }
    }

    printAllocation(allocation, processCount);
}

void bestFit(int blocks[], int blockCount, int processes[], int processCount) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processCount; i++) {
        allocation[i] = -1;  // Initialize allocation as -1 (not allocated)
    }

    for (int i = 0; i < processCount; i++) {
        int bestIndex = -1;
        for (int j = 0; j < blockCount; j++) {
            if (blocks[j] >= processes[i]) {
                if (bestIndex == -1 || blocks[j] < blocks[bestIndex]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blocks[bestIndex] -= processes[i];
        }
    }

    printAllocation(allocation, processCount);
}

void firstFit(int blocks[], int blockCount, int processes[], int processCount) {
    int allocation[MAX_PROCESSES];
    for (int i = 0; i < processCount; i++) {
        allocation[i] = -1;  // Initialize allocation as -1 (not allocated)
    }

    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < blockCount; j++) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;
                blocks[j] -= processes[i];
                break;
            }
        }
    }

    printAllocation(allocation, processCount);
}

void printAllocation(int allocation[], int processCount) {
    printf("Process No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processCount; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}
