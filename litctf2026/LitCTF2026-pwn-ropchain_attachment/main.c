#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char bss_buf[0x100];  // Global buffer in bss section

// Embed ROP gadgets so they exist in the binary
__attribute__((naked, noinline)) void gadget_pop_rdi(void) {
    __asm__ __volatile__("pop %rdi\nret\n");
}
__attribute__((naked, noinline)) void gadget_pop_rsi(void) {
    __asm__ __volatile__("pop %rsi\nret\n");
}
__attribute__((naked, noinline)) void gadget_pop_rdx(void) {
    __asm__ __volatile__("pop %rdx\nret\n");
}

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void vuln() {
    char buf[64];
    printf("Welcome to the ROP Master challenge!\n");
    printf("Can you chain the pieces together?\n");
    printf("Input: ");
    read(0, buf, 0x200);  // Stack overflow
}

int main() {
    init();
    // Prevent gadgets and system from being optimized away
    volatile void (*fp1)(void) = gadget_pop_rdi;
    volatile void (*fp2)(void) = gadget_pop_rsi;
    volatile void (*fp3)(void) = gadget_pop_rdx;
    volatile int dummy = 0;
    if (dummy) {
        fp1(); fp2(); fp3();
        system("echo hello");
    }
    vuln();
    return 0;
}
