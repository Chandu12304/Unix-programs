#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <vector>

#define MAX_BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

std::vector<int> buffer;  // Shared buffer
sem_t mutex, empty, full; // Semaphores

// Producer function
void* producer(void* arg) {
    int item = *((int*)arg);
    while (true) {
        sleep(1); 
        sem_wait(&empty);       // Wait for an empty slot
        sem_wait(&mutex);       // Enter critical section
        buffer.push_back(item); // Produce an item
        std::cout << "Produced: " << item << ", Buffer size: " << buffer.size() << std::endl;
        sem_post(&mutex);       // Exit critical section
        sem_post(&full);        // Signal a full slot
    }
    return nullptr;
}

// Consumer function
void* consumer(void*) {
    while (true) {
        sleep(1);
        sem_wait(&full);        // Wait for a full slot
        sem_wait(&mutex);       // Enter critical section
        int item = buffer.back(); buffer.pop_back(); // Consume item
        std::cout << "Consumed: " << item << ", Buffer size: " << buffer.size() << std::endl;
        sem_post(&mutex);       // Exit critical section
        sem_post(&empty);       // Signal an empty slot
    }
    return nullptr;
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, MAX_BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        int* item = new int(i + 1);
        pthread_create(&producers[i], nullptr, producer, item);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_create(&consumers[i], nullptr, consumer, nullptr);
    }
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        pthread_join(producers[i], nullptr);
    }
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consumers[i], nullptr);
    }
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}

