#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frames[], int framesCount, bool fault) {
    for (int i = 0; i < framesCount; i++) {
        if (frames[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frames[i]);
    }
    if (fault) printf(" - Fault");
    else printf(" - Hit");
    printf("\n");
}

int isPageInFrames(int page, int frames[], int framesCount) {
    for (int i = 0; i < framesCount; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}

int getOptimalReplacementIndex(int pages[], int currentIndex, int frames[], int framesCount, int pagesCount) {
    int farthest = currentIndex;
    int index = -1;

    for (int i = 0; i < framesCount; i++) {
        int j;
        for (j = currentIndex; j < pagesCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == pagesCount) {
            return i;
        }
    }

    return index == -1 ? 0 : index;
}

void fifo(int pages[], int pagesCount, int framesCount) {
    printf("FIFO Page Replacement Algorithm\n");

    int frames[MAX_FRAMES];
    int currentFrame = 0;
    int pageFaults = 0;

    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < pagesCount; i++) {
        bool fault = false;
        if (!isPageInFrames(pages[i], frames, framesCount)) {
            frames[currentFrame] = pages[i];
            currentFrame = (currentFrame + 1) % framesCount;
            fault = true;
            pageFaults++;
        }
        printFrames(frames, framesCount, fault);
    }

    printf("Total Page Faults: %d\n\n", pageFaults);
}

void optimal(int pages[], int pagesCount, int framesCount) {
    printf("Optimal Page Replacement Algorithm\n");

    int frames[MAX_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < pagesCount; i++) {
        bool fault = false;
        if (!isPageInFrames(pages[i], frames, framesCount)) {
            if (frames[i % framesCount] == -1) {
                frames[i % framesCount] = pages[i];
            } else {
                int index = getOptimalReplacementIndex(pages, i + 1, frames, framesCount, pagesCount);
                frames[index] = pages[i];
            }
            fault = true;
            pageFaults++;
        }
        printFrames(frames, framesCount, fault);
    }

    printf("Total Page Faults: %d\n\n", pageFaults);
}

void lru(int pages[], int pagesCount, int framesCount) {
    printf("LRU Page Replacement Algorithm\n");

    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int recent[MAX_FRAMES];

    for (int i = 0; i < framesCount; i++) {
        frames[i] = -1;
        recent[i] = -1;
    }

    for (int i = 0; i < pagesCount; i++) {
        bool fault = false;
        if (!isPageInFrames(pages[i], frames, framesCount)) {
            int lruIndex = 0;
            for (int j = 1; j < framesCount; j++) {
                if (recent[j] < recent[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            fault = true;
            pageFaults++;
        }
        for (int j = 0; j < framesCount; j++) {
            if (frames[j] == pages[i]) {
                recent[j] = i;
            }
        }
        printFrames(frames, framesCount, fault);
    }

    printf("Total Page Faults: %d\n\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES];
    int pagesCount;
    int framesCount;

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    printf("Enter number of pages: ");
    scanf("%d", &pagesCount);

    printf("Enter the page reference string: ");
    for (int i = 0; i < pagesCount; i++) {
        scanf("%d", &pages[i]);
    }

    fifo(pages, pagesCount, framesCount);
    optimal(pages, pagesCount, framesCount);
    lru(pages, pagesCount, framesCount);

    return 0;
}
