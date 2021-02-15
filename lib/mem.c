#include <mem.h>
#include <types.h>


void
memcpy(byte *src, byte *dest, ulong n)
{
	for (; n >= 0; --n)
		dest[n] = src[n];
}
