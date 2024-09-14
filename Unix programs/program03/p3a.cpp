#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " source_file target_file" << std::endl;
        return 1;
    }
    // Assign the first and second command-line arguments to variables
    const char *source_file = argv[1];
    const char *target_file = argv[2];
    // Create a hard link from source_file to target_file
    if (link(source_file, target_file) == 0) {
        std::cout << "Hard link created: " << target_file << " -> " << source_file << std::endl;
        return 0;
    } else {
        // Print an error message if creating the hard link fails
        perror("Error creating hard link");
        return 2;
    }
}
