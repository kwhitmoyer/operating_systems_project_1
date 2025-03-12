#include <iostream>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int buffer_size = 5; 

using namespace std;

int main() {

int shared_memory_file = shm_open("/project_1_shared_memory", O_CREAT | O_EXCL | O_RDWR, 0600);
if(shared_memory_file == -1){
    std::cout << "Log: Shared memory failed to load." << std::endl;
}

if(ftruncate(shared_memory_file, sizeof(buffer_size)) == -1)
    std::cout << "Shared memory failed to be sized" << std::endl; 
    
int* shared_memory_map = (int*)mmap(NULL, buffer_size*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_file, 0);

}
