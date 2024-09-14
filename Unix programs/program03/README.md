### **Program3a**:

To understand the program that emulates the UNIX `ln` command, it's helpful to grasp some fundamental concepts related to files, links, and system calls. Here's a detailed explanation from scratch:

### **1. Files and Links**

reference:- <https://youtu.be/4-vye3QFTFo?si=pAVYPznL-hk-9V_6>

#### **Files**:
- **Files** are containers for storing data on your computer. They have names and contain information like text, images, or executable code.

#### **Links**:
- **Links** are shortcuts or references to files. There are two main types of links in UNIX-like operating systems:
  - **Hard Links**: Point directly to the file's data on the disk. Multiple filenames can refer to the same data.
  - **Symbolic Links (Symlinks)**: Point to another file or directory by name, allowing you to create a shortcut that can span across directories.

### **2. Hard Links**

A **hard link** is another name for an existing file. It does not create a new copy of the file but provides an additional path to access the same data. When you create a hard link:
- Both the original file and the hard link point to the same inode (a data structure that stores file metadata).
- Modifications to the file through either name affect the same data.

### **3. The `link` System Call**

The `link` system call in UNIX-like operating systems is used to create a hard link. It works as follows:
- **Syntax**: `int link(const char *oldpath, const char *newpath);`
  - **`oldpath`**: The path of the existing file.
  - **`newpath`**: The path where the hard link will be created.

- **Returns**:
  - **`0`**: On success.
  - **`-1`**: On failure (an error occurred).
 
---

To pass arguments to a program when running it from the command line in a UNIX-like operating system, you use the following format:

```bash
./myprogram arg1 arg2
```

Here's a detailed breakdown:

### **How It Works**

1. **Compile the Program**:
   - First, you need to compile your program into an executable file. For example:
     ```bash
     g++ -o myprogram myprogram.cpp
     ```
   - This command compiles `myprogram.cpp` into an executable named `myprogram`.

2. **Run the Program**:
   - To run the program and pass arguments to it, use:
     ```bash
     ./myprogram arg1 arg2
     ```
   - `./myprogram` is the command to execute the program.
   - `arg1` and `arg2` are the arguments passed to the program.

3. **Program Receives Arguments**:
   - **`argc`**: Represents the number of command-line arguments, including the program name.
     - In the example `./myprogram arg1 arg2`, `argc` will be `3`.
   - **`argv`**: An array of strings where:
     - `argv[0]` is `"./myprogram"`, the name of the program.
     - `argv[1]` is `"arg1"`, the first argument.
     - `argv[2]` is `"arg2"`, the second argument.


---

### **Explaination**:

1. **Include Headers**:
   - **`#include <iostream>`**: Provides functionality for input and output operations, including `std::cout` (for printing messages) and `std::cerr` (for error messages).
   - **`#include <unistd.h>`**: Provides the declaration for the `link` system call.

2. **`int main(int argc, char *argv[])`**:
   - **`int main`**: The main function where the execution begins.
   - **`int argc`**: The count of command-line arguments passed to the program.
   - **`char *argv[]`**: An array of strings representing the command-line arguments.

3. **Check Argument Count**:
   - **`if (argc != 3)`**: Verifies that exactly three arguments are provided: the program name, the source file, and the target file.
   - **`std::cerr << "Usage: " << argv[0] << " source_file target_file" << std::endl;`**: Prints usage instructions if the number of arguments is incorrect.

4. **Assign Arguments**:
   - **`const char *source_file = argv[1];`**: Gets the name of the existing file.
   - **`const char *target_file = argv[2];`**: Gets the name of the new hard link.

5. **Create the Hard Link**:
   - **`if (link(source_file, target_file) == 0)`**: Attempts to create a hard link. If successful (`link` returns `0`), it prints a success message.
   - **`std::cout << "Hard link created: " << target_file << " -> " << source_file << std::endl;`**: Confirms the creation of the hard link.

6. **Handle Errors**:
   - **`else { perror("Error creating hard link"); return 2; }`**: If `link` fails (returns `-1`), prints an error message using `perror()` and exits with a status code `2`.

---

### **Program3b**:

This program shows how a **parent process** can create a **child process** using the `fork()` system call. Both processes then run simultaneously, doing similar tasks but acting as separate entities. This is a fundamental concept in operating systems that allows multiple tasks to be performed at the same time. The `sleep()` function adds a delay so that the output of both processes is easier to follow.


### Theory Behind the Program Using `fork()`

This program introduces a fundamental concept in operating systems: **processes** and **process creation** using the `fork()` system call. To understand the theory behind this program, let’s break it down step by step.

---

### **1. What is a Process?**

A **process** is a running instance of a program. When you run any program on your computer (like a browser, a text editor, or this C++ program), it becomes a process. Every process has its own memory and system resources.

- **Parent Process**: The process that starts or spawns another process.
- **Child Process**: A new process created by the parent process using `fork()`.

---

### **2. What is `fork()`?**

In UNIX-like operating systems (like Linux), the **`fork()`** system call is used to create a **new process**. The process that calls `fork()` becomes the **parent process**, and the new process created is the **child process**.

- **Parent and Child**: Both the parent and the child processes run the same program but work as separate, independent processes. They run concurrently (at the same time).
- **Return Values**:
  - `fork()` returns `0` to the **child process**.
  - `fork()` returns the **child’s process ID** to the **parent process**.
  - If `fork()` fails, it returns `-1` (which means the creation of the child process was unsuccessful).

---

### **3. How Processes Work After `fork()`**

Once `fork()` is called, two identical processes (parent and child) are created, but they execute independently. Each has its own copy of the program’s data and memory.

- Both the parent and the child run the same code, but they can behave differently based on conditions (like checking `child_pid == 0`).
- Even though they are running the same code, each process can take its own path in the program.

### **4. The Role of the Parent and Child Process**

After the `fork()`, the code is designed to let each process know if it’s the parent or the child:

- **Child Process**: This process knows it’s the child because `fork()` returns `0` to it. It prints messages like `Child Count: 1`.
- **Parent Process**: This process knows it’s the parent because `fork()` returns the child’s process ID (a positive number) to it. It prints messages like `Parent Count: 1`.

Both the parent and child will run the same loop, but they produce different output to represent their roles.

---

### **5. How Does the Program Run Simultaneously?**

Once the `fork()` system call creates a child process, both the parent and child run **at the same time**. They share the CPU, but since processes run quickly, it seems like they are alternating smoothly.

- In this program, both processes count from 1 to 5, with a 1-second pause between each count. The `sleep(1)` function makes both processes sleep for 1 second, ensuring they don’t run too fast.

---

### **6. Understanding `sleep()`**

The `sleep(1)` function causes a process (either the parent or child) to pause for 1 second before continuing to the next iteration of the loop.

This pause ensures that the output doesn’t happen all at once, making it easier to see how the parent and child processes are working alternately.

---

### **Key Concepts in Simple Terms:**

- **Processes**: A program that is currently running.
- **Parent Process**: The original process that creates another process.
- **Child Process**: A new process created by the parent using `fork()`.
- **`fork()`**: A function that splits a process into two—parent and child.
  - Returns `0` in the child process.
  - Returns the child's process ID in the parent.
  - If `fork()` fails, it returns `-1`.
- **Concurrency**: After `fork()`, the parent and child processes run at the same time but do their own thing.
- **`sleep()`**: Pauses the process for a certain amount of time (in seconds).

---

It might seem like the condition `child_pid == 0` should always be true for every iteration, but that's not the case. Here's why:

### **1. Understanding `fork()`**

When `fork()` is called, it **splits the program into two processes**:
- **Parent process**: The process that existed before the `fork()`.
- **Child process**: A new process created by `fork()`.

Once the `fork()` call is made:
- **In the child process**, `fork()` returns `0`.
- **In the parent process**, `fork()` returns the **child process ID** (which is a positive number).

### **2. What Happens After `fork()`**

After the call to `fork()`, both the parent and child processes **run the same code** but with **different values for `child_pid`**.

- In the **child process**, `child_pid == 0` is true, so the child process executes the code inside the `if (child_pid == 0)` block.
- In the **parent process**, `child_pid != 0` (because `fork()` returns the child’s process ID), so the parent process executes the code inside the `else` block.

### **3. How the Program Works**

After the `fork()` call:
- **Child process**: In the child process, `child_pid` is 0. So for every iteration of the loop, it prints `Child Count:`.
- **Parent process**: In the parent process, `child_pid` is the child’s process ID (a positive number). So for every iteration of the loop, it prints `Parent Count:`.

Both processes (the parent and the child) will run the loop independently. **Both loops run concurrently** because the operating system schedules them to run at the same time, but each process evaluates the `child_pid` condition separately.

### **Example Execution Flow:**
1. **Parent Process** starts:
   - `child_pid = fork()` creates a child process.
   - In the parent process, `child_pid != 0`, so it enters the `else` block and prints `Parent Count: i`.

2. **Child Process** starts:
   - In the child process, `child_pid == 0`, so it enters the `if` block and prints `Child Count: i`.

Both processes repeat this for 5 iterations, printing their respective messages.

---

## Explaination

### **1. `#include <iostream>`**

- This includes the `iostream` library, which allows the use of `std::cout` and `std::cerr` for printing output to the console.

---

### **2. `#include <unistd.h>`**

- This header file is necessary for the `fork()` function and other system-level calls like `sleep()`. It's commonly used in UNIX-like systems.

---

### **3. `int main()`**

- This is the entry point of the program where execution starts.

---

### **4. `pid_t child_pid;`**

- `pid_t` is a data type used to store process IDs. 
- `child_pid` will store the ID of the child process created by `fork()`.

---

### **5. `child_pid = fork();`**

- The `fork()` system call is used to create a new child process. 
- It returns:
  - `0` in the **child process**.
  - The **child's process ID** in the **parent process**.
  - `-1` if there is an error in creating the child process.

---

### **6. `if (child_pid == -1)`**

- This checks if `fork()` failed. If it returns `-1`, it means the child process could not be created.

---

### **7. `std::cerr << "Fork failed." << std::endl;`**

- If `fork()` fails, an error message is printed using `std::cerr`, which is the stream for error output.

---

### **8. `return 1;`**

- This exits the program with an error code (`1`), indicating that something went wrong.

---

### **9. `for (int i = 1; i <= 5; i++)`**

- This `for` loop runs 5 times, with the variable `i` counting from 1 to 5.
- Both the parent and the child processes will execute this loop separately.

---

### **10. `if (child_pid == 0)`**

- This condition checks if we are in the **child process** (because `fork()` returns `0` for the child process).
  
---

### **11. `std::cout << "Child Count: " << i << std::endl;`**

- If the process is the **child**, it prints "Child Count" along with the current value of `i`.

---

### **12. `else`**

- If the process is not the child (i.e., it’s the **parent process**), the code inside the `else` block will execute.

---

### **13. `std::cout << "Parent Count: " << i << std::endl;`**

- The **parent process** prints "Parent Count" along with the current value of `i`.

---

### **14. `sleep(1);`**

- Both the child and the parent processes pause for 1 second using the `sleep(1)` function, which causes the program to sleep for 1 second before continuing to the next iteration of the loop.

---

### **15. `return 0;`**

- This signals the successful completion of the program.

---

### **What Happens in the Program?**

1. The `fork()` system call creates a child process.
2. Both the parent and child processes enter the same `for` loop, but they execute independently.
3. Each process prints its own count message (`Parent Count` or `Child Count`) every second.
4. The parent and child processes run concurrently, but due to the loop and `sleep(1)`, they alternate printing their counts with a 1-second delay.
