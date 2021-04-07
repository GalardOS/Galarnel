#ifndef CLTIMER_H
#define CLTIMER_H

#include "common.h"

uint64 cltimer_get_freq();

void cltimer_set_compare(uint64 cmp);

void cltimer_get_value(uint64 cmp);

#endif // CLTIMER_H