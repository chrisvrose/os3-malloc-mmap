#define _MAP_MANAGEMENT_H 1

struct allocmem{
    void* ptr;
    size_t size;
    struct allocmem* next;
};

struct allocmem *newAllocMem();

void* smalloc(size_t size);

void* scalloc(size_t size,int nmemb);

void sfree(void* ptr);

void spurge();