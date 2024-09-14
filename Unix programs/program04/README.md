### **Program04**:

This program demonstrates **Inter-Process Communication (IPC)** using **shared memory** in a UNIX-like system. Shared memory allows multiple processes to communicate by reading and writing to a common memory space. The program creates a shared memory segment, writes a message to it in the parent process, and reads the message in the child process.

---

### Theory of Shared Memory in UNIX

**1. Inter-Process Communication (IPC):**
- **Inter-Process Communication (IPC)** is a mechanism that allows different processes to communicate with each other.
- In most operating systems, processes run independently and cannot directly access each other's memory. IPC provides ways to exchange data between processes.

**2. Shared Memory:**
- **Shared memory** is one of the fastest IPC mechanisms. It allows multiple processes to **share a specific portion of memory**, so that data written by one process can be read by another.
- Once the shared memory is created, both the **parent** and **child** processes can access it as if it were part of their normal memory.
- Shared memory is efficient because no copying of data is needed — both processes access the same memory space directly.

### Theory of Forking:

**1. Process Creation and `fork()`:**
- When a program runs, it runs inside a process. A **process** is simply an instance of a program that’s running.
- To create a new process, we use the **`fork()`** system call. When a process calls `fork()`, it creates a **child process** that is an exact copy of the parent process. Both processes will then continue running the same code but with different roles.
- The **parent process** and the **child process** are independent but can communicate via shared memory.

**2. `fork()` System Call:**
- `fork()` splits the current process into two: the parent and the child.
  - The **parent process** continues with its normal flow.
  - The **child process** is a copy of the parent but runs in parallel.
  - In the child process, `fork()` returns **0**, and in the parent process, `fork()` returns the **child's process ID**.

### Key Components in the Program:

1. **Shared Memory Creation (`shmget`)**:
   - `shmget()` creates a block of memory that both the parent and child processes can access.
   - This block of memory is shared, so anything written to this memory by one process can be read by the other.

2. **Attaching Shared Memory (`shmat`)**:
   - `shmat()` is used by both the parent and child processes to attach the shared memory to their memory space.
   - Once attached, the process can access this memory just like its regular variables.

3. **Detaching Shared Memory (`shmdt`)**:
   - After the processes are done reading or writing to the shared memory, they detach from it using `shmdt()`.
   - This step is important to ensure the system doesn’t keep unnecessary memory segments hanging around.

4. **Removing Shared Memory (`shmctl`)**:
   - The shared memory segment is removed using `shmctl()` when the parent process is done. This step cleans up the memory so other programs don’t accidentally access it.

---

### Example of How It Works:

1. **Creating Shared Memory**: 
   - The parent process creates a shared memory segment that both the parent and child can access.
   
2. **Forking a Child Process**:
   - The parent process calls `fork()` to create a child process.
   
3. **Writing to Shared Memory**:
   - The parent process writes a message into the shared memory: "Hello, shared memory!".
   
4. **Child Reads the Message**:
   - The child process, running in parallel, reads the message from the shared memory and prints it out.

5. **Cleaning Up**:
   - Both the parent and child detach from the shared memory when done.
   - The parent then deletes the shared memory segment to free up system resources.

---

### Key Points:
- **Efficiency**: Shared memory is faster compared to other IPC methods like pipes or message queues because it doesn’t involve copying data between processes.
- **Synchronization**: Shared memory doesn’t have built-in synchronization. If both processes try to access the shared memory at the same time, it can lead to unpredictable results. More complex programs use additional mechanisms (like semaphores) to prevent conflicts.
- **Parent and Child Processes**: After forking, both processes are independent. They share the same memory segment, but each runs its own flow of logic.
  
---

### Detailed Explanation:

```cpp
#include <iostream> 
#include <cstdlib> 
#include <cstring> 
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <unistd.h> 
#include <sys/wait.h>
```
- **Include Headers**: These are necessary libraries for input/output operations, memory functions, and IPC (shared memory, process creation, etc.).
  - `iostream`: For standard input and output (e.g., `std::cout`).
  - `cstdlib`, `cstring`: Provide general functions like `exit()` and `std::strcpy`.
  - `sys/types.h`, `sys/ipc.h`, `sys/shm.h`: System headers for working with shared memory.
  - `unistd.h`: Provides system calls like `fork()`, `wait()`, and `shmdt()`.
  - `sys/wait.h`: For waiting on child processes.

---

```cpp
#define SHM_KEY 1234 
#define SHM_SIZE 1024
```
- **Define Constants**:
  - `SHM_KEY`: A unique identifier for the shared memory segment.
  - `SHM_SIZE`: The size of the shared memory (1024 bytes).

---

```cpp
key_t key = ftok(".", SHM_KEY);
if (key == -1) {
    perror("ftok");
    exit(1);
}
```
- **Create a Key**:
  - `ftok()`: Generates a key based on a file (current directory `"."`) and a project identifier (`SHM_KEY`). This key is used to uniquely identify the shared memory segment.
  - `key == -1`: If `ftok()` fails, it returns `-1`, and the program prints an error message and exits.

---

```cpp
int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
if (shmid == -1) {
    perror("shmget");
    exit(1);
}
```
- **Create/Get Shared Memory Segment**:
  - `shmget()`: Creates or retrieves a shared memory segment of size `SHM_SIZE` (1024 bytes), identified by `key`. `IPC_CREAT | 0666` creates the segment with read/write permissions (0666).
  - `shmid == -1`: If `shmget()` fails, it returns `-1`, and the program prints an error and exits.

---

```cpp
char *shm_ptr = (char *)shmat(shmid, NULL, 0);
if (shm_ptr == (char *)(-1)) {
    perror("shmat");
    exit(1);
}
```
- **Attach Shared Memory to Process**:
  - `shmat()`: Attaches the shared memory segment to the process’s address space. `shm_ptr` now points to the shared memory.
  - `shm_ptr == (char *)(-1)`: If `shmat()` fails, it returns `-1`, and the program prints an error and exits.

---

```cpp
std::string message = "Hello, shared memory!";
std::strcpy(shm_ptr, message.c_str());
```
- **Write to Shared Memory**:
  - A string message `"Hello, shared memory!"` is written into the shared memory by copying it using `std::strcpy()` from `message.c_str()` (a C-string version of the message) to the shared memory pointer `shm_ptr`.

---

```cpp
pid_t child_pid = fork();
if (child_pid == -1) {
    perror("fork");
    exit(1);
}
```
- **Fork a Child Process**:
  - `pid_t`: data type used to represent process identifiers (PIDs) in UNIX-like operating systems. It is defined in <sys/types.h>, and it is used to identify processes uniquely within the system.
  - `fork()`: Creates a new process (child). In the parent process, `fork()` returns the child’s process ID. In the child process, it returns `0`.
  - `child_pid == -1`: If `fork()` fails, it returns `-1`, and the program prints an error and exits.

---

### **Child Process (Reads from Shared Memory):**

```cpp
if (child_pid == 0) {
    std::cout << "Child process reads: " << shm_ptr << std::endl;
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
}
```
- **Check if Child Process**: `child_pid == 0` means this block is executed in the child process.
  - The child process reads the content from the shared memory (`shm_ptr`) and prints it using `std::cout`.
  - **Detach Shared Memory**: After reading, the child process detaches the shared memory from its address space using `shmdt()`. If detaching fails, it prints an error and exits.

---

### **Parent Process (Waits and Cleans Up):**

```cpp
else {
    wait(NULL);
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
}
```
- **Parent Process**: This block runs in the parent process (`child_pid != 0`).
  - **Wait for Child Process**: The parent waits for the child process to finish using `wait(NULL)`.
  - **Detach Shared Memory**: Once the child has finished, the parent also detaches the shared memory using `shmdt()`.
  - **Remove Shared Memory**: The parent then calls `shmctl()` with `IPC_RMID` to remove the shared memory segment, so it no longer exists.
  - `IPC_RMID` is used to mark a shared memory segment for deletion. The actual removal occurs after all processes using the segment have detached from it. This ensures proper cleanup and resource management.

---

### **Program Workflow (Summary)**:
1. The program creates a shared memory segment.
2. The **parent process** writes a message into shared memory.
3. The program forks a **child process**.
4. The **child process** reads the message from shared memory and prints it.
5. Both processes detach from shared memory when done.
6. The **parent process** removes the shared memory segment after the child finishes.

---

### **Key Concepts in Simple Terms**:
- **Shared Memory**: A block of memory that multiple processes can access and share information.
- **Forking**: Creating a new process (child) from an existing one (parent).
- **`shmget()`**: Creates or retrieves a shared memory segment.
- **`shmat()`**: Attaches the shared memory to the process.
- **`shmdt()`**: Detaches the shared memory from the process.
- **`shmctl()`**: Controls operations on the shared memory (like removing it).
