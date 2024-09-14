#include <fcntl.h>  // For open()
#include <unistd.h> // For read(), write(), close()
#include <stdio.h>  // For perror()

int main() {
    // Open the source file (read-only)
    int source_fd = open("source.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        return 1;
    }
    // Open or create the destination file (write-only, with read/write permissions for the user)
    int dest_fd = open("destination.txt", O_WRONLY | O_CREAT, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);  // Close source file if destination file cannot be opened
        return 1;
    }
    // Buffer to hold data during the copy
    char buffer[1024];
    ssize_t bytes_read;
    // Read from source and write to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes_read);
    }
    printf("Succesfully Copied!")
    // Close both files
    close(source_fd);
    close(dest_fd);
    return 0;
}
