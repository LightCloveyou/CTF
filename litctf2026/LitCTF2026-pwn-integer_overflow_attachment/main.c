#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void backdoor() {
    system("/bin/sh");
}

void read_data() {
    char buf[64];
    int size;
    
    printf("How many bytes do you want to read? (0-63): ");
    scanf("%d", &size);
    
    // Vulnerable: signed/unsigned integer mismatch
    // If size is negative, when cast to unsigned int, it becomes a huge value
    if (size >= 0 && size <= 63) {
        printf("Reading %d bytes...\n", size);
    } else {
        printf("Invalid size! But I'll still read it anyway...\n");
    }
    
    read(0, buf, (unsigned int)size);  // Cast: -1 -> 0xFFFFFFFF (huge)
}

int main() {
    init();
    printf("Welcome to the Integer Labyrinth!\n");
    printf("Can you find the hidden backdoor?\n");
    read_data();
    printf("Bye!\n");
    return 0;
}
