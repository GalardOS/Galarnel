#ifndef BCM2835AUXUART_H
#define BCM2835AUXUART_H

void bcm2835auxuart_initialize();

void bcm2835auxuart_send_char(char character);

void bcm2835auxuart_send_string(char* string);

#endif // BCM2835AUXUART_H