#ifndef __FMT_H_
#define __FMT_H_

#include <stdarg.h>

int vsnprint(char *fmt, char *buffer, int n, va_list args);

int snprint(char *fmt, char *buffer, int n, ...);

#endif /* __FMT_H_ */
