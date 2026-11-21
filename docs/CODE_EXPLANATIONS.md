1. Header Files

We included three header files in our code.

stdio.h is used for displaying output using printf().

unistd.h is included because we use sbrk() to get memory from the operating system.

stddef.h provides size_t, which we use to store the size of memory blocks.

2. Block Structure

We created a structure named block to store information about each memory block.

struct block {
size_t size;
int free;
struct block *next;
};

The structure has three members. The size variable stores the size of the block in bytes. The free variable tells us whether the block is free or being used. We use 1 for a free block and 0 for a used block.

The next pointer stores the address of the next block. It helps us connect all the blocks using a linked list.

3. Allocation Strategies

We use three allocation strategies in our code: First Fit, Best Fit and Worst Fit.

First Fit selects the first free block that is large enough for the requested memory.

Best Fit selects the smallest free block that is large enough for the requested memory. It helps reduce unused space inside a block.

Worst Fit selects the largest available free block. It leaves a larger remaining space after allocation.

These strategies help us choose which free memory block will be used for a new allocation.

4. Head and Tail Pointers

We use two pointers named head and tail to keep track of our memory blocks.

The head pointer stores the address of the first block in the linked list. The tail pointer stores the address of the last block.

These pointers help us access and manage the memory blocks easily.

5. Strategy Variable

We created a variable named strategy to store the current allocation strategy.

Initially, we set it to FIRST_FIT. This means our allocator uses First Fit by default.

Later, we can change the strategy to Best Fit or Worst Fit when needed.

6. set_strategy()

The set_strategy() function is used to change the allocation strategy.

It takes an integer value as an argument and stores it in the strategy variable.

This allows us to select different allocation strategies without changing the main allocation code.

7. allocator_reset()

The allocator_reset() function resets the allocator's linked list.

It sets both head and tail to NULL. This means the allocator no longer keeps track of the previous blocks.

We use this function when we want to start a new test with an empty allocator.
