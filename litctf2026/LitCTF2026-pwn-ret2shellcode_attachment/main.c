#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void vuln() {
    char buf[100];
    printf("Welcome to the Shellcode Workshop!\n");
    printf("Here is a hint for you: buf is at %p\n", buf);
    printf("Leave your mark on the stack: ");
    read(0, buf, 0x200);  // Read way more than buf size -> overflow
    printf("Your work is done.\n");
}

int main() {
    init();
    vuln();
    return 0;
}
