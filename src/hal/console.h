#ifndef HAL_CONSOLE_H
#define HAL_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

void console_initialize();

void console_writechar(char character);

void console_writestring(char* string);

#ifdef __cplusplus
}
#endif

#endif // HAL_CONSOLE_H