**stack**

I've written this program as an attempt to demonstrate how SLL elements function within a stack structure, as a sort of reference or proof of concept, mainly to service my own understanding of data structures and pointers. The output is designed to demonstrate a standard FILO process, as well as the sequence in which memory is allocated to the heap and deallocated. Comments are fairly detailed, so hopefully this helps anyone currently trying to understand SSLs, pointers, and pointers to pointers.

Usage is straightforward. The program starts by asking how many 'elements' you would like to push (each element has an integer data field which is randomly generated). You can pick an arbitrary number between 1 and 999999. You are then asked the number of elements you would like to pop. Once the program is happy with those values, the process of pushing elements begins, with the push function outputing the address, data, and index for each element as it pushes them. Then, provided a number of pops was requested (you can pick 0), a similar process goes on for popping elements. After this, all of the elements remaining in the stack structure are displayed. 

Here is an example of a run of output:

		> ./stack
		How many elements to push? 10
		How many elements to pop? 7

		PUSH    address: 0x7f8ddad00000    data: 95278873  	(0)
		PUSH    address: 0x7f8ddad00010    data: 57049433  	(1)
		PUSH    address: 0x7f8ddad00020    data: 68188999  	(2)
		PUSH    address: 0x7f8ddad00030    data: 82369834  	(3)
		PUSH    address: 0x7f8ddad00040    data: 26494926  	(4)
		PUSH    address: 0x7f8ddad00050    data: 59400124  	(5)
		PUSH    address: 0x7f8ddad00060    data:  9880126  	(6)
		PUSH    address: 0x7f8ddad00070    data: 98774621  	(7)
		PUSH    address: 0x7f8ddad00080    data: 73338764  	(8)
		PUSH    address: 0x7f8ddad00090    data: 20990555  	(9)

		POP     address: 0x7f8ddad00090    data: 20990555  	(9)
		POP     address: 0x7f8ddad00080    data: 73338764  	(8)
		POP     address: 0x7f8ddad00070    data: 98774621  	(7)
		POP     address: 0x7f8ddad00060    data:  9880126  	(6)
		POP     address: 0x7f8ddad00050    data: 59400124  	(5)
		POP     address: 0x7f8ddad00040    data: 26494926  	(4)
		POP     address: 0x7f8ddad00030    data: 82369834  	(3)

		Remaining stack elements: 3
		address: 0x7f8ddad00020		   data: 68188999	(2)
		address: 0x7f8ddad00010		   data: 57049433	(1)	      
		address: 0x7f8ddad00000		   data: 95278873	(0)


Considerations for next build:
  - Test for memory leaks!
  - A more interactive application with commands for individual or batch pushes and pops, with option to assign data to individual elements, and refresh display of entire stack.
  - Better convention for index numbers, possibly only for use when displaying entire stack. Currently a little confusing as the first element pushed displays a (0) beside it, which could be mistaken for being the first linked list element, i.e. first element to be popped, which is incorrect. Indexes aren't as relevant for stacks, as we are always popping the top item (last in).
  - Display 'next' field, possibly replace index with it.
  - Seperate into two .c files, one as a general use 'stack' library function, which can be included in any other projects; another which allows an interactive environment to play with structure and provides the output described above.
  - Review comments. 
