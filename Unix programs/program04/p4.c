#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Define the shared memory key and size
#define SHM_KEY 1234
#define SHM_SIZE 1024

int main() {
    // Create a key for the shared memory segment
    key_t key = ftok(".", SHM_KEY);
    if (key == -1) {
        perror("ftok"); // Print error if ftok fails
        exit(1);
    }
    // Create (or get) the shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget"); // Print error if shmget fails
        exit(1);
    }
    // Attach the shared memory segment to the process's address space
    char* shm_ptr = (char*)shmat(shmid, NULL, 0);
    if (shm_ptr == (char*)(-1)) {
        perror("shmat"); // Print error if shmat fails
        exit(1);
    }
    // Write a message to the shared memory
    std::string message = "Hello, shared memory!";
    std::strcpy(shm_ptr, message.c_str()); // strcpy() works with C-string( array of char ) format, whwereas message is std::string format, c_str converts it into the required format
    // Print the message from the shared memory
    std::cout << "Message from shared memory: " << shm_ptr << std::endl;
    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt"); // Print error if shmdt fails
        exit(1);
    }
    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl"); // Print error if shmctl fails
        exit(1);
    }
    return 0;
}

