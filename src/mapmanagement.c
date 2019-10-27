#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/types.h>

#ifndef _MAP_MANAGEMENT_H
#include<mapmanagement.h>
#endif

static struct allocmem* memlocs = NULL;


struct allocmem *newAllocMem(){
    struct allocmem* ptr;
    //void* res = mmap(NULL,sizeof(struct allocmem),PROT_READ|PROT_WRITE);
    if((ptr = mmap(NULL,sizeof(struct allocmem),PROT_READ | PROT_WRITE , MAP_POPULATE | MAP_ANONYMOUS | MAP_PRIVATE,-1,0))==MAP_FAILED){
        return NULL;
    }
    else{
        ptr->ptr= NULL;
        ptr->size= 0;
        ptr->next = NULL;
        return ptr;
    }
}

void freeAllocMem(struct allocmem* ptr){
    if(ptr!=NULL){
        munmap(ptr,sizeof(struct allocmem));
    }
}

///Pass a valid pointer (or NULL) to store the resultant into 
struct allocmem* insertEnd(struct allocmem* ptr,struct allocmem** outVar){
    if(ptr==NULL){
        struct allocmem* outAble = newAllocMem();
        if(outVar!=NULL) *outVar=outAble;
        return (outAble);
    }else{
        ptr->next = insertEnd(ptr->next,outVar);
        return ptr;
    }
}

struct allocmem* find(struct allocmem* ptr,void* searchPtr){
    if(ptr==NULL){
        return NULL;
    }
    if(ptr->ptr==searchPtr)
        return ptr;
    return find(ptr->next,searchPtr);
}

struct allocmem* findAndRemove(struct allocmem* ptr,void* searchPtr){
    if(ptr==NULL){return NULL;}
    if(ptr->ptr==searchPtr){
        struct allocmem *nextUp = ptr->next;
        freeAllocMem(ptr);
        return nextUp;
    }
    ptr->next = findAndRemove(ptr->next,searchPtr);
    return ptr;
}




void* smalloc(size_t size){
    struct allocmem* info=NULL;
    memlocs = insertEnd(memlocs,&info);
    if(info==NULL){
        ///Failed to initialize metadata info
        return NULL;
    }
    void* ptr;
    if((ptr = mmap(NULL,sizeof(struct allocmem),PROT_READ | PROT_WRITE , MAP_POPULATE | MAP_ANONYMOUS | MAP_PRIVATE,-1,0))==MAP_FAILED){
        ///Failed to make data, revert changes
        memlocs = findAndRemove(memlocs,NULL);
    }else{
        ///Got it together
        info->ptr = ptr;
        info->size = size;
        ///Return this precious pointer
        return ptr;
    }
    return NULL;
}


void* scalloc(size_t size,int nmemb){
    size_t isOverFlow = size*nmemb;
    if(size!=isOverFlow/nmemb){
        ///Overflow, dont try
        return NULL;
    }
    void* newPtr = smalloc(isOverFlow);
    if(newPtr==NULL){
        ///Failed to init
        return NULL;
    }
    ///A character is a byte of data that can be managed
    for(size_t loc = 0;loc<isOverFlow;loc++){
        *(((char*)newPtr)+loc) = 0;
    }
    return newPtr;
}


void sfree(void* ptr){
    if(ptr==NULL)return;
    struct allocmem* info = find(memlocs,ptr);
    if(info==NULL) return;
    munmap(info->ptr,info->size);
    memlocs = findAndRemove(memlocs,ptr);
}


///Violently Remove Everything
void spurge(){
    while(memlocs){
        sfree(memlocs->ptr);
    }
}
