#include <stdio.h>
#include <process.h>
#include <stdlib.h>

int flagThreadA = 1;
int flagThreadB = 0;
int flagThreadC = 0;
char vector[30];
int indexVector = 0;

void threadA(void *threadno) {
    while (indexVector < 27) {
        while (!flagThreadA) {}
        vector[indexVector] = 'a';
        indexVector++;
        flagThreadA = 0;
        flagThreadB = 1;
    }
    return;
}

void threadB(void *threadno) {
    while (indexVector < 28) {
        while (!flagThreadB) {}
        vector[indexVector] = 'b';
        indexVector++;
        flagThreadB = 0;
        flagThreadC = 1;
    }
    return;
}

void threadC(void *threadno) {
    while (indexVector < 29) {
        while (!flagThreadC) {}
        vector[indexVector] = 'c';
        indexVector++;
        flagThreadC = 0;
        flagThreadA = 1;
    }

    for (int i = 0; i < indexVector; i++) {
        printf("vector[%d] = %c\n", i, vector[i]);
    }
    return;
}


void start_thread() {
    int thread_id;

#if     defined(__WIN32__)
    if ((thread_id = _beginthread(threadA, 4096, NULL)) == (unsigned long) -1)
#else
        if ((thread_id = _beginthread(threadA, 4096, NULL)) == -1)
#endif
    {
        printf("Unable to create thread a.\n");
        return;
    }
    printf("Created thread a.\n");

#if     defined(__WIN32__)
    if ((thread_id = _beginthread(threadB, 4096, NULL)) == (unsigned long) -1)
#else
        if ((thread_id = _beginthread(threadB, 4096, NULL)) == -1)
#endif
    {
        printf("Unable to create thread b.\n");
        return;
    }
    printf("Created thread b.\n");

#if     defined(__WIN32__)
    if ((thread_id = _beginthread(threadC, 4096, NULL)) == (unsigned long) -1)
#else
        if ((thread_id = _beginthread(threadC, 4096, NULL)) == -1)
#endif
    {
        printf("Unable to create thread c.\n");
        return;
    }
    printf("Created thread c.\n");
}

int main(void) {
    start_thread();
    getchar();
    return 0;
}
