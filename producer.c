#include "header.h"

int buffer_size = 5; 

int main() {
    struct shared_memory_buffer* shared_memory;
    shm_unlink("/project_1_shared_memory");

    int shared_memory_file = shm_open(shared_file_name, O_CREAT | O_EXCL | O_RDWR, 0600);
    if(shared_memory_file == -1){ printf("Shared memory failed to load.\n"); }

    int ftruncate_failed = ftruncate(shared_memory_file, sizeof(struct shared_memory_buffer));
    if(ftruncate_failed == -1){ printf("Memory failed to be truncated by ftruncate.\n"); }
        
    shared_memory = (struct shared_memory_buffer*) mmap(NULL, sizeof(*shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file, 0);      
    if (shared_memory == MAP_FAILED){ printf("The memory map failed to be created.");}


    int full_semaphore = sem_init(&shared_memory->full_semaphore, 1, 0);  
    if (full_semaphore == -1) printf("The head semaphore failed to be initialized.\n");
    
    int empty_semaphore= sem_init(&shared_memory->empty_semaphore, 1, BUFFER_SIZE);
    if(empty_semaphore == -1) printf("The tail semaphore failed to be initialized.\n"); 
    
    int mutex_semaphore = sem_init(&shared_memory->mutex_semaphore, 1, 1);
    if(mutex_semaphore == -1) printf("The mutex semaphore failed to be initialized.\n");

    srand(time(NULL));

    printf("Producer is writing values to the buffer.\n");
    
    for(int i = 0; i < BUFFER_SIZE; ++i){
        sem_wait(&shared_memory->empty_semaphore); 
        sem_wait(&shared_memory-> mutex_semaphore);

        int insertedValue = rand() % 10 + 1;
        shared_memory->buffer[shared_memory->tail] = insertedValue;
        printf("Producer inserted value: %d\n", insertedValue);

        shared_memory->tail = (shared_memory->tail + 1) % BUFFER_SIZE;

        sem_post(&shared_memory->mutex_semaphore); 
        sem_post(&shared_memory->full_semaphore);
    }

    printf("Producer has finished writing values to the buffer.\n\n");

}



