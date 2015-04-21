// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 4
// Description: Stores the Published Items in a Linked List.
//		Allows Publishers to add items and Subscribers to read them.

#ifndef ITEMS_H
#define ITEMS_H

//---------------//
// Include Files //
//---------------//
#include <stdlib.h>
#include <time.h>

//----------------------------//
// Data Structure Declaration //
//----------------------------//
typedef struct item {
	int volume;
	int value;
	struct item *next;
} item;

//---------------------//
// Global Declarations //
//---------------------//
int volume = 0;
struct item *head;
struct item *curr;

//----------------------------//
// Method Forward Declaration //
//----------------------------//
void createList(int);
void addItem(int);
void readItem(struct item*);
void printList();

//-------------------//
// createList Method //
//-------------------//
void createList(int value) {
	// Declare & Initialize the Pointer to the Linked List
	struct item *ptr = (struct item*) malloc(sizeof(struct item));

	// Check to see if memory was allocated
	if (NULL == ptr) {
		printf("ERROR: Could not allocate memory\n");
		return;
	}

	// Display Creation of Linked List
	if (DEBUG) printf("----------CREATING LIST----------\n");

	volume++; // Increment the Volume
	ptr->volume = volume; // Assign the Published Item Volume
	ptr->value = value; // Assign the Published Item a random integer value
	ptr->next = NULL; // Assign the next pointer as NULL to terminate list

	head = ptr; // Assign the head pointer to the newly created Item
	curr = ptr; // Assign the curr pointer to the newly created Item

	// Display the Published Item Information
	printf("PUBLISHING: VOLUME(%d)\t%d\n\n", ptr->volume, ptr->value);

	return;
}

//----------------//
// addItem Method //
//----------------//
void addItem(int value) {
	// Check to see if Linked List has been created
	if (NULL == head) {
		// Create the Linked List if head is NULL
		createList(value);
		return;
	}

	// Declare & Initialize the Pointer to the Linked List
	struct item *ptr = (struct item*) malloc(sizeof(struct item));

	// Check to see if memory has been allocated
	if (NULL == ptr) {
		printf("ERROR: Could not allocate memory\n");
		return;
	}

	volume++; // Increment the Volume
	ptr->volume = volume; // Assign the Published Item Volume
	ptr->value = value; // Assign the Published Item a random integer value
	ptr->next = NULL; // Assign the next pointer as NULL to terminate list

	// Add Item to end of List
	curr->next = ptr; // Attach new item to the end of the Linked List
	curr = ptr; // Move the pointer to the new item

	// Display the Published Item Information
	printf("PUBLISHING: VOLUME(%d)\t%d\n\n", ptr->volume, ptr->value);

	return;
}

//-----------------//
// readItem Method //
//-----------------//
void readItem(struct item *ptr) {
	// Check to see if Pointer is a valid Published Item
	if (NULL == ptr) {
		printf("ERROR: INVALID POINTER (READING)\n");
		return;
	}

	// Display the Published Item Information
	printf("READING VOLUME(%d)\t%d\n", ptr->volume, ptr->value);	

	return;
}

//------------------//
// printList Method //
//------------------//
void printList() {
	// Declare & Initialize a Pointer to the beginning of the Linked List
	struct item *ptr = head;

	printf("----------PRINTING VOLUMES----------\n");

	// Iterate over the Linked List of Items
	while (NULL != ptr) {
		printf("VOLUME(%d):\t%d\n", ptr->volume, ptr->value); // Display the Volume Item Information	
		ptr = ptr->next; // Iterate to next node
	}

	printf("----------DONE PRINTING----------\n");
	printf("\n");
	printf("\n");

	// Pause for Readability
	sleep(1);
	
	return;
}

#endif
