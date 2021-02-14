#ifndef __FMT_H_
#define __FMT_H_

#include <stdarg.h>

typedef int (*Fmt)(char *buffer, int n, int flags, va_list ap);

void fmtinstall(Fmt fun, int c);

int vsnprint(char *fmt, char *buffer, int n, va_list ap);

int snprint(char *fmt, char *buffer, int n, ...);

#endif /* __FMT_H_ */
