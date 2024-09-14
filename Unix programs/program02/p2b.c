#include <stdio.h>
extern char **environ; // Declare the environ variable

int main() {
    char **env = environ; // Pointer to the environment list
    // Loop through and print each environment variable
    while (*env != NULL) {
        printf("%s\n", *env); // Print the current environment variable
        env++; // Move to the next variable
    }
    return 0; // Program executed successfully
}
