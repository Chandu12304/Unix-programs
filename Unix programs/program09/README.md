### Theory Behind the Program: Inter-Process Communication (IPC) Using Pipes

In an operating system, processes are usually isolated from one another. However, there are many cases where processes need to communicate with each other to share data or coordinate tasks. This is called **Inter-Process Communication (IPC)**.

One of the simplest ways to enable communication between processes in Unix-like operating systems is through **pipes**. Pipes allow data to flow in one direction: from one process (the writer) to another process (the reader). The operating system manages this flow by creating a temporary channel in memory.

#### Key Concepts for Beginners:

1. **Processes**:
   - A process is an instance of a running program.
   - The **parent process** creates a new **child process** using a system call like `fork()`.

2. **Pipes**:
   - A pipe is a method to send data from one process to another.
   - It creates two file descriptors:
     - One for **writing** data into the pipe.
     - One for **reading** data from the pipe.
   - Data flows in one direction: writer → reader.

3. **Forking**:
   - When you use the `fork()` function, the operating system creates a new process (a child process) which is a copy of the parent process.
   - Both processes will continue executing the same program, but each has its own memory space.
   - The parent and child process can communicate through the pipe.

4. **How Pipes Work**:
   - Pipes are like channels that can carry data between two processes.
   - The **parent** can write data into the pipe, and the **child** can read it from the other end (or vice versa).
   - The operating system buffers the data so that it can be transferred efficiently.

#### Steps in the Program:

1. **Creating a Pipe**:
   - The `pipe()` function creates the pipe and gives two file descriptors:
     - One to write (`pipe_fd[1]`).
     - One to read (`pipe_fd[0]`).

2. **Forking the Process**:
   - `fork()` creates a child process. After the fork, both the parent and child processes can communicate via the pipe.
   - The parent and child will execute different parts of the program based on the value returned by `fork()`.

3. **Parent Sends Data**:
   - The parent process writes a message (a string) into the pipe using `write()`.
   - The write operation is done using the write-end of the pipe (`pipe_fd[1]`).

4. **Child Receives Data**:
   - The child process reads the data from the pipe using `read()`.
   - The read operation happens on the read-end of the pipe (`pipe_fd[0]`).

5. **Closing Unused Ends**:
   - It’s important to close the pipe ends that are not in use:
     - The parent closes its read-end because it only writes.
     - The child closes its write-end because it only reads.

#### Why Pipes are Useful:
- **Pipes** are an efficient way to share information between related processes.
- They are commonly used in Unix-like systems because they are simple and allow for fast communication without needing to write data to disk.

#### Important Limitations:
- Pipes are **unidirectional**: Data flows in one direction (from writer to reader).
- Both the parent and child processes must be running at the same time for communication to occur.


---

This program demonstrates **inter-process communication (IPC)** using a **pipe** between a parent and a child process. It explains how to send a message from the parent process to the child process using the pipe.

### Step-by-Step Explanation:

#### 1. Pipe Creation
```cpp
int pipe_fd[2]; // File descriptors for the pipe
if (pipe(pipe_fd) == -1) {
    perror("Pipe creation failed");
    return 1;
}
```
- **`pipe_fd[2]`**: This array holds the file descriptors for the pipe:
  - `pipe_fd[0]`: For reading from the pipe.
  - `pipe_fd[1]`: For writing to the pipe.
- **`pipe(pipe_fd)`**: This function creates a pipe and returns two file descriptors (one for reading and one for writing). If it fails, `-1` is returned, and an error message is printed using `perror()`.

#### 2. Forking a Child Process
```cpp
pid_t child_pid = fork(); // Fork a child process
if (child_pid == -1) {
    perror("Fork failed");
    return 1;
}
```
- **`fork()`**: This system call creates a new process (child process). It returns the process ID of the child to the parent, and returns `0` to the child process. If it fails, `-1` is returned.
  - **`child_pid > 0`**: Parent process.
  - **`child_pid == 0`**: Child process.

#### 3. Parent Process (Sending a Message)
```cpp
if (child_pid > 0) { // Parent process
    close(pipe_fd[0]); // Close the read end in the parent
    std::string message = "Hello from parent!";
    if (write(pipe_fd[1], message.c_str(), message.length()) == -1) {
        perror("Write to pipe failed");
        return 1;
    }
    close(pipe_fd[1]); // Close the write end in the parent
}
```
- **Closing the read end (`pipe_fd[0]`) in the parent**: The parent only writes, so it doesn't need the read end.
- **Writing a message to the pipe**:
  - `message = "Hello from parent!"`: A string message to be sent to the child.
  - **`write(pipe_fd[1], message.c_str(), message.length())`**: Writes the message to the pipe. If this fails, it prints an error message.
- **Closing the write end (`pipe_fd[1]`) in the parent**: After writing the message, the parent closes the write end of the pipe.

#### 4. Child Process (Receiving a Message)
```cpp
else { // Child process
    close(pipe_fd[1]); // Close the write end in the child
    char buffer[50]; 
    ssize_t bytes_read;
    bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Read from pipe failed");
        return 1;
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string
    std::cout << "Child process received message: " << buffer << std::endl;
    close(pipe_fd[0]); // Close the read end in the child
}
```
- **Closing the write end (`pipe_fd[1]`) in the child**: The child only reads from the pipe, so it doesn't need the write end.
- **Reading from the pipe**:
  - **`read(pipe_fd[0], buffer, sizeof(buffer))`**: Reads data from the pipe into a buffer. The size of the buffer is 50 bytes in this case.
  - **`buffer[bytes_read] = '\0'`**: After reading, we append a null character to the buffer to terminate the string properly.
- **Printing the message**:
  - The child process prints the received message: `"Child process received message: Hello from parent!"`.
- **Closing the read end (`pipe_fd[0]`) in the child**: After reading the message, the child closes the read end of the pipe.
