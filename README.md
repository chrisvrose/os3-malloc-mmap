# os3-malloc-mmap

Implement malloc and calloc using mmap and munmap system calls

Care has to be taken to not use sfree on traditionally allocated memory; undefined behaviour.

## smalloc

`void* smalloc(size_t size)`

## scalloc

`void* scalloc(size_t size, int nmemb)`

## sfree

`void sfree(void* ptr)`
