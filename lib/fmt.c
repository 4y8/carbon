#include <fmt.h>
#include <libc.h>

#include <stdarg.h>

int
vsnprint(char *fmt, char *buffer, int n, va_list args)
{
	int i;

	for (i = 0; *fmt != '\0'; ++fmt) {
		if (*fmt == '%') {
			switch (*(++fmt)) {
			case 'd':
				break;
			case 'x':
				break;
			case 'c':
				break;
			case 's':
				break;
			}
		} else {
			buffer[i++] = *fmt;
		}
		if (i >= n)
			return -1;
	}
	buffer[i] = '\0';
	return 0;
}

int
snprint(char *fmt, char *buffer, int n, ...)
{
	va_list args;
	int ret;

	va_start(args, n);
	ret = vsnprint(fmt, buffer, n, args);
	va_end(args);
	return ret;
}
