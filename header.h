#ifndef PRODUCER_CONSUMER
#define PRODUCER_CONSUMER 

#include <semaphore.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h> 


const int BUFFER_SIZE = 5; 

struct shared_memory_buffer {
    sem_t full_semaphore;
    sem_t empty_semaphore;
    sem_t mutex_semaphore;
    size_t count; 
    char buffer[BUFFER_SIZE];
    int head = 0;  
    int tail = 0; 
};


#endif