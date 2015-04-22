#include "sem.h"
#define SUB_LIMIT 5

int subCount = 1;
int readCount = 0;

int countValue = 0;

struct semaphore *no_waiting;
struct semaphore *no_accessing;
struct semaphore *counter_mutex;

void Reader();
void Writer();


void Reader() {
    int prev = 0;
P(no_waiting);
P(counter_mutex);
printf("Reader Count Value: %d",countValue);
    V(counter_mutex);
V(no_waiting);
return;
}


void Writer() {
    P(no_waiting);
    P(counter_mutex);
    countValue++;
    printf("Writer Count Value: %d",countValue);
    V(counter_mutex);
    V(no_waiting);
return;
}

int main() {

no_waiting = (struct semaphore*) malloc(sizeof(struct semaphore));
no_accessing = (struct semaphore*) malloc(sizeof(struct semaphore));
counter_mutex = (struct semaphore*) malloc(sizeof(struct semaphore));

runQ = (struct queue*) malloc(sizeof(struct queue));

// Create the Queue
initQueue(runQ);

// Initialize the Semaphore
initSem(no_waiting, 1);
initSem(no_accessing, 1);
initSem(counter_mutex, 1);

// Add processes to threads
startThread(Writer);
startThread(Reader);

// Begin execution of threads
run();

return 0;
}