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

void vuln() {
    char buf[48];
    printf("Welcome, rookie! Can you find the backdoor?\n");
    printf("Input: ");
    read(0, buf, 0x200);  // Stack overflow
}

int main() {
    init();
    vuln();
    printf("Bye!\n");
    return 0;
}
