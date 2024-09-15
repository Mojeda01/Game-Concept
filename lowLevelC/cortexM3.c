#define UART0DR *((volatile unsigned int*)0x4000C000)

void print_uart0(const char *s) {
    while(*s != '\0') {
        UART0DR = (unsigned int)(*s);
        s++;
    }
}

void c_entry() {
    print_uart0("Hello, Embedded World!\n");
    while(1) {
        // Enter low-power mode or just loop indefinitely
        __asm__("wfi");  // Wait for interrupt (low-power mode)
    }
}