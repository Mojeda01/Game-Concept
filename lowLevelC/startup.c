extern void c_entry(void);
extern unsigned int _estack; // This should be defined in your linker script

void Reset_Handler(void){
    c_entry();
}

void Default_Handler(void){
    while(1);
}

// Define weak aliases for all interrupt handlers to the Default_Handler
#define WEAK_ALIAS(x) void x(void) __attribute__((weak, alias("Default_Handler")))

// Define weak aliases
WEAK_ALIAS(NMI_Handler);
WEAK_ALIAS(HardFault_Handler);
// ... define more weak aliases as needed

// Vector table
__attribute__((section(".vector_table")))
void(* const vector_table[])(void) = {
    (void*)&_estack,    // Initial stack pointer
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    //... add more vectors as needed
};