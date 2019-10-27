# os3-malloc-mmap

Implement malloc and calloc using mmap and munmap system calls

Care has to be taken to not use sfree on traditionally allocated memory; undefined behaviour.

Yes, It tracks whatever has been allocated.
The search uses O(n) linear search, similar to insertion and deletion.

## smalloc

`void* smalloc(size_t size)`

## scalloc

`void* scalloc(size_t size, int nmemb)`

## sfree

`void sfree(void* ptr)`
