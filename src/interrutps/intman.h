#ifndef INTMAN_H
#define INTMAN_H

#include "common.h"
#include "exceptions.h"

void intman_initialize();

void intman_add_interrupt(uint32 irqid, void(*handler)(struct cpu_status));

void intman_add_synchronous(uint32 siid, void(*handler)(struct cpu_status));

#endif // INTMAN_H