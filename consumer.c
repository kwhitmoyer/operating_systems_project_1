//CS 33211
//Katherine Whitmoyer
//Project 1: Producer-Consumer Problem

#include "header.h"

int main() {
    struct shared_memory_buffer* shared_memory;

    //Connect to shared memory buffer 
    int shared_memory_file = shm_open(shared_file_name, O_RDWR, 0600);
    if(shared_memory_file == -1) printf("Shared memory failed to load.\n");
    
    //Map to shared memory buffer
    shared_memory = (struct shared_memory_buffer*) mmap(NULL, sizeof(*shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file, 0);      
    if (shared_memory == MAP_FAILED) printf("The memory map failed to be created.\n"); 

    printf("Consumer is consuming values from the buffer.\n");

    for(int i = 0; i < BUFFER_SIZE; ++i){
        //Process calls wait on mutex before entering critical section 
        sem_wait(&shared_memory->full_semaphore); 
        sem_wait(&shared_memory->mutex_semaphore);

        //Process enters critical section 

        int retrieved_value = shared_memory->buffer[shared_memory->head];
        printf("Consumer consumed %d\n", retrieved_value);

        shared_memory->head = (shared_memory->head + 1) % BUFFER_SIZE;

        //Process exits critical section, signals using mutex semaphore
        sem_post(&shared_memory->mutex_semaphore); 
        sem_post(&shared_memory->empty_semaphore);
    }

    printf("Consumer has finished consuming values from the buffer.\n\n");

}
