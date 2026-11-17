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
