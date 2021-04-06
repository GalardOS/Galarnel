#ifndef AARCH64_H
#define AARCH64_H

#include "common.h"

void syscall(uint32 sys_number);

uint64 esr_el1();

#endif // AARCH64_H