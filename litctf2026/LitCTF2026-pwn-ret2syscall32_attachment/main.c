#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char data_buf[0x100];  // Writable buffer in data section

// Embed ROP gadgets so they exist in the binary regardless of libc version
__attribute__((naked, noinline)) void gadget_pop_eax(void) {
    __asm__ __volatile__("pop %eax\nret\n");
}
__attribute__((naked, noinline)) void gadget_pop_ebx(void) {
    __asm__ __volatile__("pop %ebx\nret\n");
}
__attribute__((naked, noinline)) void gadget_pop_ecx_ebx(void) {
    __asm__ __volatile__("pop %ecx\npop %ebx\nret\n");
}
__attribute__((naked, noinline)) void gadget_pop_edx(void) {
    __asm__ __volatile__("pop %edx\nret\n");
}
__attribute__((naked, noinline)) void gadget_mov_edx_eax(void) {
    __asm__ __volatile__("mov %eax, (%edx)\nret\n");
}
__attribute__((naked, noinline)) void gadget_int_0x80(void) {
    __asm__ __volatile__("int $0x80\n");
}

void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void vuln() {
    char buf[64];
    printf("Welcome to the 32-bit Time Machine!\n");
    printf("No system(), no /bin/sh... but int 0x80 still works.\n");
    printf("Input: ");
    read(0, buf, 0x200);  // Stack overflow
}

int main() {
    init();
    // Prevent gadget functions from being optimized away
    volatile void (*fp1)(void) = gadget_pop_eax;
    volatile void (*fp2)(void) = gadget_pop_ebx;
    volatile void (*fp3)(void) = gadget_pop_ecx_ebx;
    volatile void (*fp4)(void) = gadget_pop_edx;
    volatile void (*fp5)(void) = gadget_mov_edx_eax;
    volatile void (*fp6)(void) = gadget_int_0x80;
    if (strlen("always_true") == 0) {
        fp1(); fp2(); fp3(); fp4(); fp5(); fp6();
    }
    vuln();
    printf("Goodbye!\n");
    return 0;
}
