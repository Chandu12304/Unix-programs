#include <iostream>
#include <pthread.h>

void* countTo100(void* arg) {
    int threadID = *(int*)arg; // Get the thread ID
    for (int i = 1; i <= 100; ++i) {
        std::cout << "Thread " << threadID << ": Count " << i << std::endl;
    }
    return nullptr; // End of thread function
}

int main() {
    const int numThreads = 2;
    pthread_t threads[numThreads];
    int threadIDs[numThreads] = {1, 2}; // Thread IDs
    // Create threads
    for (int i = 0; i < numThreads; ++i) {
        pthread_create(&threads[i], nullptr, countTo100, &threadIDs[i]);
    }
    // Wait for threads to finish
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }
    return 0;
}

