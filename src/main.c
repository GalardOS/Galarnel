#include "drivers/bcm2835auxuart.h"

void main() {
    bcm2835auxuart_send_string("[+] Jelou guorl!\r\n");
}