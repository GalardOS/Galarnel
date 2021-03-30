#ifndef BCM2835INTC_H
#define BCM2835INTC_H

void bcm2835intc_initialize();

void bcm2835intc_enable(int irqid);
void bcm2835intc_disable(int irqid);

#endif // BCM2835INTC_H