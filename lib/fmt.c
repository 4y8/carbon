#include <fmt.h>
#include <libc.h>

#include <stdarg.h>

#define MAX_FMTS 512

static int fmt_intd(char *buffer, int n, int flags, va_list ap);
static int fmt_intx(char *buffer, int n, int flags, va_list ap);
static int fmt_charc(char *buffer, int n, int flags, va_list ap);

static struct {
	int c;
	Fmt fun;
} fmts[MAX_FMTS] = {
	{ 'd', (Fmt)fmt_intd },
	{ 'x', (Fmt)fmt_intx },
	{ 'c', (Fmt)fmt_charc },
};

static int
fmt_intd(char *buffer, int n, int flags, va_list ap)
{
	int r;

	r = itoa(va_arg(ap, int), buffer, 10, n);
	if (r < 0)
		return -1;

	return r;
}

static int
fmt_intx(char *buffer, int n, int flags, va_list ap)
{
	int r;

	r = itoa(va_arg(ap, int), buffer, 16, n);
	if (r < 0)
		return -1;

	return r;
}

static int
fmt_charc(char *buffer, int n, int flags, va_list ap)
{
	/* The argument of type char is promoted to int so we retreive it as an
	 * int. */
	buffer[0] = (char)(va_arg(ap, int));
	return 1;
}

void
fmtinstall(Fmt fun, int c)
{
	for (int i = 0; i < MAX_FMTS; ++i) {
		if (fmts[i].c == 0) {
			fmts[i].c = c;
			fmts[i].fun = fun;
		}
	}
}

int
vsnprint(char *fmt, char *buffer, int n, va_list ap)
{
	int i;

	for (i = 0; *fmt != '\0'; ++fmt) {
		if (*fmt == '%') {
			++fmt;
			for (int j = 0; j < MAX_FMTS; ++j) {
				if (*fmt == (char)fmts[j].c) {
					int r;
					r = fmts[j].fun(buffer + i, n - i, 0,
					                ap);
					if (r < 0)
						return -1;
					i += r;
				}
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
