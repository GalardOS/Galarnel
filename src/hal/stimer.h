#ifndef HAL_STIMER_H
#define HAL_STIMER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*stimer_event)(void);

void stimer_initialize(int freq);

void stimer_set_event(stimer_event event);

#ifdef __cplusplus
}
#endif

#endif // HAL_INTC_H