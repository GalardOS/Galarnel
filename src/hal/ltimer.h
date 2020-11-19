#ifndef HAL_LTIMER_H
#define HAL_LTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*ltimer_event)(void);

void ltimer_initialize(int freq);

void ltimer_set_event(ltimer_event event);


#ifdef __cplusplus
}
#endif

#endif // HAL_LTIMER_H