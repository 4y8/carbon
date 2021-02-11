#ifndef __IO_H_
#define __IO_H_

#include <stdarg.h>

void puts(char *s);

void putchar(char c);

void clear_terminal(void);

void vprint(char *fmt, va_list arg);
void print(char *fmt, ...);

#endif /* __IO_H_ */
