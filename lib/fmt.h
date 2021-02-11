#ifndef __FMT_H_
#define __FMT_H_

#include <stdarg.h>

void vsnprint(char *fmt, char *buffer, int n, va_list arg);
void vsprint(char *fmt, char *buffer, va_list arg);

#endif /* __FMT_H_ */
