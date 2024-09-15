#include <iostream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_KEY 1234   // Shared memory key
#define SHM_SIZE 1024  // Shared memory size

int main() {
    // Create shared memory segment
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    // Attach shared memory to parent process
    char *shm_ptr = (char *)shmat(shmid, nullptr, 0);
    if (shm_ptr == (char *)(-1)) {
        perror("shmat");
        return 1;
    }

    // Write message to shared memory
    strcpy(shm_ptr, "Hello from parent!");

    // Fork a child process
    if (fork() == 0) {
        // Child reads from shared memory
        std::cout << "Child reads: " << shm_ptr << std::endl;
        shmdt(shm_ptr);  // Detach shared memory in child
    } else {
        wait(nullptr);    // Wait for child to finish
        shmdt(shm_ptr);   // Detach shared memory in parent
        shmctl(shmid, IPC_RMID, nullptr);  // Remove shared memory
    }

    return 0;
}
