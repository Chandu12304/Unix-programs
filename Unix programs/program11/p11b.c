#include <iostream>
#include <pthread.h>

const int numThreads = 5; // Number of threads

// Function to be executed by each thread
void* printHello(void* arg) {
    int threadNumber = *(int*)arg; // Get the thread number from the argument
    std::cout << "Hello World from Thread " << threadNumber << std::endl;
    return nullptr; // End of thread function
}

int main() {
    pthread_t threads[numThreads]; // Array to hold thread identifiers
    int threadIDs[numThreads]; // Array to hold thread IDs

    // Initialize thread IDs
    for (int i = 0; i < numThreads; ++i) {
        threadIDs[i] = i + 1; // Set thread number from 1 to numThreads
    }

    // Create and start threads
    for (int i = 0; i < numThreads; ++i) {
        // Pass the address of the threadID as the argument
        pthread_create(&threads[i], nullptr, printHello, &threadIDs[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    return 0;
}
