This repo contains the implementation of the producer consumer model, 
implemented via the POSIX library. It is a class assignment writte for CS 33211. 

### Within This Implementation
- A producer creates a shared buffer
- The producer produces integers and writes them to the shared buffer
- The consumer accesses the shared buffer
- The consumer file consumes integers from the shared buffer

## Mutual Exclusion 
Mutual exclusion is enforced via the use of a mutex semaphore. The insertion of each integer is treated as the process entering the critical section. 
When the process is trying to enter the critical section, sem_wait(&shared_memory-> mutex_semaphore) decrements the mutex. If the semaphore's value is
greater then zero, the function will return immediately. If the semaphore has the value 0, the sem_wait call is blocked until the semaphore value is greater than zero. 
For more information on the sem_wait() call as implemented in the POSIX library, click [here](https://man7.org/linux/man-pages/man3/sem_wait.3.html)

After the process exits the critical section, sem_post(&shared_memory-> mutex_semaphore) increments the mutex semaphore value to 1. This indicates 
that the process has exited the critical section. If other processes are waiting to enter the critical section, they will become unblocked after the 
mutex is For more information on the sem_post() call as implemented in the POSIX library, click [here](https://man7.org/linux/man-pages/man3/sem_post.3.html)

## Example Usage
This implementation of the producer consumer model can be run by three commands.

### Execution and Commands 
```
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer 
```
These commands compile the producer.c and consumer.c files into executables. 

```
./producer & ./consumer &
```
This command runs the two executable files one after another.

### Expected Output
This implementation will write the values of the producer and consumer to the terminal.

![Expected Output 1](images/expected_output.png)

Note that integer values vary randomly, and a different set of values will be produced each time. 

![Expected Output 2](images/expected_output2.png) 

## Troubleshooting Information 
This implementation depends on the creation of a new memory buffer. If a user runs commands out of order, the shared memory will fail to be created on the next execution of the program. The producer executable will print error messages and then loop infintely, while the consumer executable will return a segmentation fault. 

### Example of Failed Execution 
![Failed Output](images/failed_output.png)

### How To Fix This Issue?
The correct way to fix this issue is to remove current executable files by the rm command.
```
rm producer consumer
```



   
