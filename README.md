# os3-malloc-mmap

Implement malloc and calloc using mmap and munmap system calls

Yes, It tracks whatever has been allocated.
The search uses O(n) linear search, similar to insertion and deletion.

## Running

Include in project. Please add `-lrt`.
Included `main.c` is an example program demonstrating the functions

Compiling the example:

`gcc -g -I include src/mapmanagement.c main.c -o main.out -lrc`

## Functions

### smalloc

`void* smalloc(size_t size)`

### scalloc

`void* scalloc(size_t size, int nmemb)`

Sets the data values to zero, mandatorily

### sfree

`void sfree(void* ptr)`

Only smalloc-ed or scalloc-ed variables are freed.
This way, there is no:

1. Double frees
2. freeing null
3. freeing random locations

### spurge

`void spurge()`

Clean all allocated memory.
Implemented because it was possible.