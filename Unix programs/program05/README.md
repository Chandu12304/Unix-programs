This program demonstrates the concept of **Producer-Consumer Problem** using threads and semaphores in C++. Multiple producers generate data and add it to a shared buffer, while multiple consumers consume that data from the buffer. Semaphores are used to control access to the shared buffer to avoid race conditions.

---

### Explanation

#### Key Concepts
- **Producer**: Adds items to the shared buffer.
- **Consumer**: Removes items from the shared buffer.
- **Semaphores**: Used to manage synchronization between producer and consumer threads.
  - **mutex**: Ensures only one thread (producer or consumer) accesses the buffer at a time (mutual exclusion).
  - **empty**: Tracks the number of empty slots in the buffer.
  - **full**: Tracks the number of filled slots in the buffer.

---

### Code Breakdown

#### Libraries Used
```cpp
#include <iostream> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <vector>
```
- `pthread.h`: For working with threads.
- `semaphore.h`: For using semaphores.
- `unistd.h`: Contains the `sleep()` function for simulating delays.
- `vector`: For using the shared buffer.

#### Constants
```cpp
#define MAX_BUFFER_SIZE 5 
#define NUM_PRODUCERS 2 
#define NUM_CONSUMERS 2
```
- `MAX_BUFFER_SIZE`: Defines the maximum size of the shared buffer.
- `NUM_PRODUCERS` and `NUM_CONSUMERS`: Define how many producer and consumer threads will be created.

#### Shared Buffer and Semaphores
```cpp
std::vector<int> buffer; 
sem_t mutex; 
sem_t empty; 
sem_t full;
```
- `buffer`: Shared vector where producers add items and consumers remove items.
- `mutex`: Controls access to the buffer so only one thread can modify it at a time.
- `empty`: Tracks available empty slots in the buffer.
- `full`: Tracks available filled slots in the buffer.

#### Producer Function
```cpp
void* producer(void* arg) {
    int item = *((int*)arg);
    while (true) {
        sleep(1); // Simulate time to produce an item
        
        sem_wait(&empty); // Wait for an empty slot
        sem_wait(&mutex); // Lock the buffer for exclusive access
        
        buffer.push_back(item); // Produce an item
        std::cout << "Produced: " << item << ", Buffer size: " << buffer.size() << std::endl;
        
        sem_post(&mutex); // Unlock the buffer
        sem_post(&full); // Signal that buffer has a filled slot
    }
    return NULL;
}
```
- The producer generates an item and waits for an empty slot in the buffer using `sem_wait(&empty)`.
- It locks the buffer using `sem_wait(&mutex)`, adds the item, and unlocks the buffer.
- The producer then signals that the buffer has a filled slot using `sem_post(&full)`.
- This process repeats indefinitely in a loop (`while (true)`).

#### Consumer Function
```cpp
void* consumer(void* arg) {
    while (true) {
        sleep(1); // Simulate time to consume an item
        
        sem_wait(&full); // Wait for a filled slot
        sem_wait(&mutex); // Lock the buffer for exclusive access
        
        int item = buffer.back(); // Get the last produced item
        buffer.pop_back(); // Remove the item from the buffer
        std::cout << "Consumed: " << item << ", Buffer size: " << buffer.size() << std::endl;
        
        sem_post(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that the buffer has an empty slot
    }
    return NULL;
}
```
- The consumer waits for a filled slot in the buffer using `sem_wait(&full)`.
- It locks the buffer using `sem_wait(&mutex)`, removes the last produced item from the buffer, and unlocks the buffer.
- The consumer then signals that the buffer has an empty slot using `sem_post(&empty)`.

#### Main Function
```cpp
int main() {
    // Initialize semaphores
    sem_init(&mutex, 0, 1); 
    sem_init(&empty, 0, MAX_BUFFER_SIZE); 
    sem_init(&full, 0, 0); 
    
    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];
    
    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        int* item = new int(i);
        pthread_create(&producer_threads[i], NULL, producer, (void*)item);
    }
    
    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    
    // Join threads
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producer_threads[i], NULL);
    }
    
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumer_threads[i], NULL);
    }
    
    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}
```
- **Semaphore Initialization**:
  - `sem_init(&mutex, 0, 1)`: Initializes the `mutex` semaphore for controlling access to the buffer. It starts with a value of `1` (unlocked).
  - `sem_init(&empty, 0, MAX_BUFFER_SIZE)`: Initializes the `empty` semaphore with the number of empty slots available in the buffer (i.e., `MAX_BUFFER_SIZE`).
  - `sem_init(&full, 0, 0)`: Initializes the `full` semaphore with `0` because the buffer starts empty.

- **Thread Creation**:
  - Two producer and two consumer threads are created using `pthread_create()`.
  - The producer threads are passed an argument, which represents the item they will produce.

- **Thread Joining**:
  - `pthread_join()` ensures that the main program waits for all threads to complete.

- **Semaphore Destruction**:
  - After threads finish, the semaphores are destroyed using `sem_destroy()`.

---

### Key Points
- **Semaphores**: Used to synchronize access to the shared buffer. `mutex` ensures that only one thread (producer or consumer) can access the buffer at a time. `empty` tracks empty buffer slots, and `full` tracks filled buffer slots.
- **Critical Section**: The portion of code where threads modify the shared buffer is protected using `sem_wait()` and `sem_post()` to prevent race conditions.
- **Producer-Consumer Problem**: This is a classic synchronization problem where producers generate data and consumers consume it, but they must coordinate their access to the shared buffer to avoid conflicts.