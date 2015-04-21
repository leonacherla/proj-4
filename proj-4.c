// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 4
// Description: Main file which holds the threads for Publisher-Subscriber.

//---------------//
// Include Files //
//---------------//
#include "sem.h"
#include "items.h"

//--------------------//
// Global Definitions //
//--------------------//
#define SUB_LIMIT 5

//---------------------//
// Global Declarations //
//---------------------//
int subCount = 1;
int readCount = 0;
struct semaphore *no_waiting;
struct semaphore *no_accessing;
struct semaphore *counter_mutex;

//----------------------------//
// Method Forward Declaration //
//----------------------------//
void publisherEntry();
void publisherExit();
void subscriberEntry();
void subscriberExit();

//--------------------//
// Threaded Functions //
//--------------------//
void publisher();
void subscriber();

//-----------------------//
// publisherEntry Method //
//-----------------------//
void publisherEntry() {
	P(no_waiting);
	P(no_accessing);
	V(no_waiting);

	return;
}

//----------------------//
// publisherExit Method //
//----------------------//
void publisherExit() {
	V(no_accessing);
	
	return;
}

//------------------------//
// subscriberEntry Method //
//------------------------//
void subscriberEntry() {
	int prev = 0;

	P(no_waiting);
	P(counter_mutex);
	prev = readCount; // Set the previous number of readers
	readCount++; // Increment the reader's count
	V(counter_mutex);

	if (prev == 0) {
		P(no_accessing);
	}

	V(no_waiting);

	return;
}

//-----------------------//
// subscriberExit Method //
//-----------------------//
void subscriberExit() {
	int current = 0;

	P(counter_mutex);
	readCount--; // Decrement the reader count
	current = readCount; // Set the current number of readers
	V(counter_mutex);

	if (current == 0) {
		V(no_accessing);
	}

	return;
}

//------------------//
// publisher Method //
//------------------//
void publisher() {
	while (1) {
		publisherEntry();
		/*-----Critical Section-----*/
		addItem(rand());
		printList();
		/*-----End Critical Section-----*/
		publisherExit();
	}

	return;
}

//-------------------//
// subscriber Method //
//-------------------//
void subscriber() {
	// Grab the Subscriber ID from the Counter
	int subID = subCount;

	// Declare the Pointer to the Linked List of Items & assign to start of List
	struct item *currItem;

	while (1) {
		subscriberEntry();
		/*-----Critical Section-----*/

		// Checking for Published Items
		if (NULL == currItem) {
			// Grab the First Item Published
			currItem = head;
		} else if (currItem->volume != curr->volume) {
			// Checking if Reader's Item is the First or the Latest Item
			currItem = curr;
		}

		// Iterate over all Published Items
		while (NULL != currItem) {
			printf("SUBSCRIBER(%d): ", subID); // Print Subscriber Tag
			readItem(currItem); // Read one currItem of work
			currItem = currItem->next; // Iterate to next Item
		}

		if (subCount < SUB_LIMIT) {
			// Call your buddy and add a new subscriber
			subCount++;
			startThread(subscriber);
		}

		// Reinitialize the Pointer to the Published Items
		currItem = curr;

		printf("\n");
		/*-----End Critical Section-----*/
		subscriberExit();
	}

	return;
}

//-------------//
// main Method //
//-------------//
int main() {
	// Define the Random Number Generator
	srand(time(NULL));

	// Allocate memory for the Semaphores
	no_waiting = (struct semaphore*) malloc(sizeof(struct semaphore));
	no_accessing = (struct semaphore*) malloc(sizeof(struct semaphore));
	counter_mutex = (struct semaphore*) malloc(sizeof(struct semaphore));

	// Allocate memory for the Run Queue to hold the threaded processes
	runQ = (struct queue*) malloc(sizeof(struct queue));

	// Create the Queue
	initQueue(runQ);

	// Initialize the Semaphore
	initSem(no_waiting, 1);
	initSem(no_accessing, 1);
	initSem(counter_mutex, 1);

	// Add processes to threads
	startThread(publisher);
	startThread(subscriber);

	// Begin execution of threads
	run();

	return 0;
}
