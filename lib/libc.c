#include <libc.h>
#include <io.h>

int
abs(int value)
{
	return value >= 0 ? value : -value;
}

int
itoa(int value, char *buf, int base, int bufsize)
{
	int n, i, r;
	char c;

	i = 0;
	if (value == 0)
		buf[i++] = '0';
	n = abs(value);
	while (n) {
		r = n % base;
		buf[i++] = r >= 10 ? 'A' + (r - 10) : '0' + r;
		n /= base;
		if (i >= bufsize)
			return -1;
	}
	buf[i] = '\0';

	/* Reverse the string */
	for (int j = 0; j < i / 2; ++j) {
		c = buf[j];
		buf[j] = buf[i - j - 1];
		buf[i - j - 1] = c;
	}
	return i;
}
