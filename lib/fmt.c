#include <libc.h>

#define MAX_FMTS 512

static int fmt_int(char *buffer, int n, int flags, va_list ap, int base);
static int fmt_intd(char *buffer, int n, int flags, va_list ap);
static int fmt_intx(char *buffer, int n, int flags, va_list ap);
static int fmt_intb(char *buffer, int n, int flags, va_list ap);
static int fmt_into(char *buffer, int n, int flags, va_list ap);

static int fmt_charc(char *buffer, int n, int flags, va_list ap);

static int fmt_strings(char *buffer, int n, int flags, va_list ap);

static struct {
	int c;
	Fmt fun;
} fmts[MAX_FMTS] = {
	{ 'd', (Fmt)fmt_intd },
	{ 'x', (Fmt)fmt_intx },
	{ 'o', (Fmt)fmt_into },
	{ 'b', (Fmt)fmt_intb },
	{ 'c', (Fmt)fmt_charc },
	{ 's', (Fmt)fmt_strings },
};

static int
fmt_int(char *buffer, int n, int flags, va_list ap, int base)
{
	int r;

	r = itoa(va_arg(ap, int), buffer, base, n);
	if (r < 0)
		return -1;

	return r;
}

static int
fmt_intd(char *buffer, int n, int flags, va_list ap)
{
	return fmt_int(buffer, n, flags, ap, 10);
}

static int
fmt_intx(char *buffer, int n, int flags, va_list ap)
{
	return fmt_int(buffer, n, flags, ap, 16);
}

static int
fmt_intb(char *buffer, int n, int flags, va_list ap)
{
	return fmt_int(buffer, n, flags, ap, 2);
}

static int
fmt_into(char *buffer, int n, int flags, va_list ap)
{
	return fmt_int(buffer, n, flags, ap, 8);
}

static int
fmt_charc(char *buffer, int n, int flags, va_list ap)
{
	/* The argument of type char is promoted to int so we retreive it as an
	 * int. */
	buffer[0] = (char)(va_arg(ap, int));
	return 1;
}

static int
fmt_strings(char *buffer, int n, int flags, va_list ap)
{
	int i;
	char *s;

	s = va_arg(ap, char *);
	i = 0;

	for (; *s != '\0'; ++s)
		buffer[i++] = *s;

	return i;
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
