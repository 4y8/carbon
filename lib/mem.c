#include <libc.h>

void
memcpy(byte *src, byte *dest, ulong n)
{
	for (; (long)n >= 0; --n)
		dest[n] = src[n];
}
