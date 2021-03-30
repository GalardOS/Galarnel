#include "drivers/bcm2835auxuart.h"

extern void main();

void gimme_all_your_lovin() {
    bcm2835auxuart_initialize();
    bcm2835auxuart_send_string("[+] Kernel alive!\r\n");

    // Call the main function from the kernel
    main();

    // As the kernel should never exit, infinite loop
    while(1);
}