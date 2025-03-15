#include <iostream>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include "header.hpp"

int buffer_size = 5; 

using namespace std;

int main() {

    shm_unlink("/project_1_shared_memory");

    int shared_memory_file = shm_open("/project_1_shared_memory", O_CREAT | O_EXCL | O_RDWR, 0600);
    if(shared_memory_file == -1){
        std::cout << "Shared memory failed to load." << std::endl;
    }

    int ftruncate_failed = ftruncate(shared_memory_file, sizeof(struct shared_memory_buffer));
    if(ftruncate_failed == -1){
        std::cout << "Memory failed to be truncated by ftruncate." << std::endl; 
    }
        
    struct shared_memory_buffer* shared_memory_map = (struct shared_memory_buffer*) mmap(NULL, sizeof(struct shared_memory_buffer), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file, 0);
    if (shared_memory_map == MAP_FAILED){
        std::cout << "The memory map failed to be created.";
    }
    std::cout << "The shared memory has been created successfully." << std::endl; 

    sem_t* head_semaphore = sem_open("/head_semaphore", O_CREAT, 0666, buffer_size);
    if(head_semaphore == SEM_FAILED) { std::cout << "Head semaphore failed." << std::endl; }
    sem_t* tail_semaphore = sem_open("/tail_semaphore", O_CREAT, 0666, 0); 
    if(tail_semaphore == SEM_FAILED) {std::cout << "Tail semaphore failed." << std::endl; }
    sem_t* mutex_semaphore = sem_open("/mutex_semaphore", O_CREAT, 0666, 1);
    if(mutex_semaphore == SEM_FAILED) {std::cout << "Mutex semaphore failed." << std::endl; }

    std::cout << "The semaphores have initalized successfully." << std::endl; 

    int numOfItems = BUFFER_SIZE;

    
    for(int i = 0; i < BUFFER_SIZE; ++i){

    }

}

