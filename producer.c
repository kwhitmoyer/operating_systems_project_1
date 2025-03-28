//CS 33211
//Katherine Whitmoyer
//Project 1: Producer-Consumer Problem

#include "header.h"

int main() {
    struct shared_memory_buffer* shared_memory;

    //Get rid of previous shared memory buffer if existing
    shm_unlink("/project_1_shared_memory");

    //Create shared memory buffer with read write ability 
    int shared_memory_file = shm_open(shared_file_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if(shared_memory_file == -1){ printf("Shared memory failed to load.\n"); }

    //Size shared memory buffer
    int ftruncate_failed = ftruncate(shared_memory_file, sizeof(struct shared_memory_buffer));
    if(ftruncate_failed == -1){ printf("Memory failed to be truncated by ftruncate.\n"); }
        
    //Map to shared memory buffer
    shared_memory = (struct shared_memory_buffer*) mmap(NULL, sizeof(*shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file, 0);      
    if (shared_memory == MAP_FAILED){ printf("The memory map failed to be created.");}

    //Create semaphores 
    int full_semaphore = sem_init(&shared_memory->full_semaphore, 1, 0);  
    if (full_semaphore == -1) printf("The full semaphore failed to be initialized.\n");
    
    int empty_semaphore= sem_init(&shared_memory->empty_semaphore, 1, BUFFER_SIZE);
    if(empty_semaphore == -1) printf("The empty semaphore failed to be initialized.\n"); 
    
    int mutex_semaphore = sem_init(&shared_memory->mutex_semaphore, 1, 1);
    if(mutex_semaphore == -1) printf("The mutex semaphore failed to be initialized.\n");

    srand(time(NULL));

    printf("Producer is writing values to the buffer.\n");
    
    for(int i = 0; i < BUFFER_SIZE; ++i){
        //Process calls wait on mutex before entering critical section 
        sem_wait(&shared_memory->empty_semaphore); 
        sem_wait(&shared_memory-> mutex_semaphore);

        //Process enters critical section 

        int insertedValue = rand() % 10 + 1;
        shared_memory->buffer[shared_memory->tail] = insertedValue;
        printf("Producer inserted value: %d\n", insertedValue);

        shared_memory->tail = (shared_memory->tail + 1) % BUFFER_SIZE;

        //Process exits critical section, signals using mutex semaphore
        sem_post(&shared_memory->mutex_semaphore); 
        sem_post(&shared_memory->full_semaphore);
    }

    printf("Producer has finished writing values to the buffer.\n\n");

}



