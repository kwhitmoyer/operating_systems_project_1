#ifndef PRODUCER_CONSUMER
#define PRODUCER_CONSUMER 

#include <semaphore.h> 
#include <time.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

const char* shared_file_name = "/project_1_shared_memory";

struct shared_memory_buffer {
    sem_t full_semaphore;
    sem_t empty_semaphore;
    sem_t mutex_semaphore;
    char buffer[BUFFER_SIZE];
    int head;  
    int tail;
};

#endif