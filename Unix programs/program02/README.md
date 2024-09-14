#### 1. `#include <fcntl.h>  // For open()`
- This header file includes the definitions of the `open()` function and the constants used to specify file access modes like `O_RDONLY` and `O_WRONLY`. 
- It helps us interact with file descriptors.

#### 2. `#include <unistd.h> // For read(), write(), close()`
- This header provides access to low-level I/O system calls: `read()`, `write()`, and `close()`. 
- These are essential for reading from and writing to files at the system level.

#### 3. `#include <stdio.h>  // For perror()`
- The `stdio.h` library is included to use `perror()`, a function that prints an error message to standard output.

---

### Main Program Breakdown:

#### 4. `int main() {`
- The `main()` function is where the program starts execution.

#### 5. `int source_fd = open("source.txt", O_RDONLY);`
- `open()` is used to open the file `"source.txt"` in read-only mode (`O_RDONLY`).
- The `open()` function returns a file descriptor (`source_fd`), a unique number that represents the opened file in the system.
- If `source_fd < 0`, it means the file couldn't be opened.

#### 6. `if (source_fd < 0) { perror("Error opening source file"); return 1; }`
- This checks if the file failed to open (`source_fd < 0`).
- If so, `perror()` prints a descriptive error message to the console (like "Error opening source file").
- `return 1;` exits the program with an error status.

#### 7. `int dest_fd = open("destination.txt", O_WRONLY | O_CREAT, 0644);`
- Opens the file `"destination.txt"` in write-only mode (`O_WRONLY`).
- If the file doesn’t exist, it is created using the flag `O_CREAT` with permissions `0644` (read/write for the owner and read-only for others).
- The `open()` function returns the file descriptor `dest_fd` for the destination file.

#### 8. `if (dest_fd < 0) { perror("Error opening destination file"); close(source_fd); return 1; }`
- Checks if the destination file failed to open. 
- If so, it prints an error message, closes the source file (since it's already open), and exits the program with an error status.

#### 9. `char buffer[1024];`
- Defines a `buffer` that will temporarily hold data read from the source file.
- The size is `1024` bytes, which is how much data will be read in one go.

#### 10. `ssize_t bytes_read;`
- Declares a variable `bytes_read` to store the number of bytes read from the source file by the `read()` function.
- `ssize_t` is a signed data type used for sizes and can hold the number of bytes read.

#### 11. `while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {`
- The `read()` system call reads from the file descriptor `source_fd` and stores the data in `buffer`.
- `sizeof(buffer)` (1024 bytes) determines how much data to read at once.
- The `while` loop continues reading until all data is read (when `read()` returns 0, meaning the end of the file).

#### 12. `write(dest_fd, buffer, bytes_read);`
- `write()` writes the data from `buffer` to the file represented by `dest_fd` (the destination file).
- It writes exactly `bytes_read` bytes to the file.

#### 13. `close(source_fd);`
- After copying is done, `close()` closes the source file descriptor `source_fd`, releasing system resources.

#### 14. `close(dest_fd);`
- Closes the destination file descriptor `dest_fd`, completing the file copying process.

#### 15. `return 0;`
- The program returns 0, indicating successful execution.
