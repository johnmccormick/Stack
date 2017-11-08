#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int MAX_ELEMENTS = 999999;

// Very basic structure for a singly linked list element
struct element {
	int data;
	struct element* next;
};

// Push an element on to the top of the stack
void push(struct element** top_element, int new_data)
{
    // Allocate memory for a new element, and set pointer to it. 
    // This memory will soon hold our new top element.
    struct element* new_element = malloc(sizeof(struct element));

    // Dereference new_element and assign new_data to 'data' member.
    new_element->data = new_data;

    // Dereference new_element and set it's 'next' member to point to the dereferenced value of
    // 'top_element' (i.e. the memory adress pointed to by the pointer that **top_element points to).
    new_element->next = (*top_element); 

    // We dereference the pointer to original top_element pointer memory location, and store a
    // pointer to the allocated memory of new_element there.
    // Memory address of new_element will now be stored by original top_element pointer.
    // new_element is is our new top element.
    *top_element = new_element;

    // Some output so we can see what's going on and check everything is working as it should.
    printf("PUSH    address: %p    data: %8i  ", new_element, new_element->data);
}

// Pop an element from the top of the stack
void pop(struct element** top_element) 
{	
	// We create a pointer which will hold the next element in the stack.
	// This is necessary because once we free the current element from memory,
	// we will need to retain access the next element pointer, as this will be
	// our new element held at the top of the stack.
	struct element* next_element;

	// So we get the memory address passed into top_element, dereference it and obtain its
	// 'next' pointer, and assign that to the next_element pointer. 
	next_element = (*top_element)->next;

	// Some output to show the address and data value of the top element before we free it.
	printf("POP     address: %p    data: %8i  ", *top_element, (*top_element)->data);

	// next_element holds the keys to the rest of stack, so we can free the memory the top element
	// has been allocated. We do this by dereferencing top_element again, which returns the memory
	// location of the original top_element pointer. This is freed by free(), meaning top_element will
	// now point to an unallocated section of memory.
	free(*top_element);

	// As we will want to refer to top_element again and again, we will change the address the original
	// pointer points to, by dereferencing the pointer of the pointer and making it the same as the
	// next_element pointer. 
	*top_element = next_element;
}

int main () {

	int push_elements;
	int pop_elements;

	// UI to request user for number of elements to push and pop
	do {
		printf("How many elements to push? ");
		scanf("%i", &push_elements);
		if (push_elements < 1 || push_elements > MAX_ELEMENTS)
			printf("Please enter a number between 1 and %i.\n", MAX_ELEMENTS);
	} while (push_elements < 1 || push_elements > MAX_ELEMENTS); // Simple validation to 

	do {
		printf("How many elements to pop? ");
		scanf("%i", &pop_elements);
		if (pop_elements < 0 || pop_elements > push_elements)
			printf("Please enter a number between 0 and %i.\n", push_elements);
	} while (pop_elements > MAX_ELEMENTS || pop_elements > push_elements);
	pop_elements = abs(pop_elements);

	printf("\n");

	struct element* top_element = NULL;

	// push a number of elements with random data
	for (int i = 0; i < push_elements; ++i) {
		// Seeding rand by seconds wasn't effective because this often happens in less than a second.
		// The program won't be run twice on the same second though, so this works.
		srand(time(NULL)*rand());
		push(&top_element, (rand() % 100000000)); // mod 9dp means data is always 8dp.
		printf("\t(%i)\n", i);
	}

	if (pop_elements)
		printf("\n");

	// pop the top element a number of times
	for (int i = 0; i < pop_elements; ++i) {
		pop(&top_element);
		printf("\t(%i)\n", push_elements - 1 - i);
	}

	// How many elements are left unpopped? Did we clear the stack?
	bool stack_cleared;
	int stack_elements = push_elements - pop_elements;

	// If we're at the end of the stack, stack_elements should always == 0, and top_element should point to NULL
	// (the 'next' field of the bottom element). 
	// Although I'm not sure how necessary it is, I'm doing a second check below to check if one
	// condition returns true while the other doesn't (which would be bad).
	// Pretty sure we'd see an error prior to this if something went wrong with pushing or popping, 
	// but I'm going to keep it because it might catch something unexpected.
	if (stack_elements == 0 && top_element == NULL) {
		stack_cleared = true;
	} else {
		if (stack_elements == 0 || top_element == NULL)
			fprintf(stderr, "Something went wrong at line %i\n", __LINE__);
		stack_cleared = false;
		printf("\nRemaining elements: %i.\n", stack_elements);
	}

	// We're not going to pop the remaining elements, but print their data in order to
	// illustrate that any elements that weren't popped will still be accessible, in order,
	// with a determinable last element in the stack.
	// top_element will remain untouched as it will still point to the top element after the loop
	// is complete. After the loop is complete, temp_element will point to the last element, so it's
	// ->next field will point to NULL. The same logic applies to stack_elements and stack_cleared which
	// will be copied into by loop_elements and loop_cleared, which are to be used for the display loop.	
	struct element* temp_element = top_element;
	char* label = "";
	
	int loop_elements = stack_elements;
	bool loop_cleared = stack_cleared;

	while (loop_cleared == false) {
		if (temp_element->next == NULL) {
			loop_cleared = true;
		}

		printf("\taddress: %p    data: %i\t(%i)\t\n", temp_element, temp_element->data, loop_elements - 1);
		loop_elements--;

		// similar to how we pop, the temp_element pointer (like top_element pointer) will now point to the next element in the stack
		// If we didn't have to free allocated memory in pop(), the function could have been two lines, one of output and
		// another which read:	
		//		*head_element = (*head_element)->next 
		temp_element = temp_element->next;
	}
}
