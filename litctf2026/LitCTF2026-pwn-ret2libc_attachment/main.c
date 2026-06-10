#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

// Embed pop rdi; ret gadget
__attribute__((naked, noinline)) void gadget_pop_rdi(void) {
    __asm__ __volatile__(
        "pop %rdi\n"
        "ret\n"
    );
}

// Embed xor rax, rax; ret gadget (for printf AL requirement)
__attribute__((naked, noinline)) void gadget_xor_rax(void) {
    __asm__ __volatile__(
        "xor %rax, %rax\n"
        "ret\n"
    );
}

// Helper to leak the value at a given address (dereferences the pointer)
void __attribute__((noinline)) leak_value(void **addr) {
    printf("Leak: %p\n", *addr);
}

void vuln() {
    char buf[64];
    printf("The backdoor is lost, but maybe libc can help?\n");
    printf("Tell me your name: ");
    read(0, buf, 0x200);  // Overflow! 0x200 >> 64
}

int main() {
    init();
    // Prevent gadget functions from being optimized away
    volatile void (*fp1)(void) = gadget_pop_rdi;
    volatile void (*fp2)(void) = gadget_xor_rax;
    if (strlen("always_true") == 0) {
        fp1();
        fp2();
    }
    vuln();
    printf("Goodbye!\n");
    return 0;
}
