#include <libc.h>

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

unsigned char color = 0b00101111;

static long xpos = 0;
static long ypos = 0;

static long
next_pos(void)
{
	if (xpos == SCREEN_WIDTH) {
		xpos = 0;
		return ++ypos * 2 * SCREEN_WIDTH;
	} else {
		return (xpos++) * 2 + ypos * 2 * SCREEN_WIDTH;
	}
}

void
putchar(char c)
{
	long pos;

	if (c == '\n') {
		xpos = 0;
		++ypos;
		return;
	}
	pos = next_pos();
	*(unsigned char *)(0xB8000 + pos) = c;
	*(unsigned char *)(0xB8000 + pos + 1) = color;
}

void
puts(char *s)
{
	for (; *s != '\0'; ++s)
		putchar(*s);
	putchar('\n');
}

void
clear_terminal(void)
{
	unsigned char scolor;

	xpos = 0;
	ypos = 0;
	scolor = color;
	color = 0;
	for (int i = 0; i < SCREEN_WIDTH; ++i) {
		for (int j = 0; j < SCREEN_HEIGHT; ++j) {
			putchar(' ');
		}
	}
	color = scolor;
	xpos = 0;
	ypos = 0;
}

void
vprint(char *fmt, va_list ap)
{
	char buf[1024];

	if (vsnprint(fmt, buf, 1024, ap) < 0)
		return;
	puts(buf);
}

void
print(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vprint(fmt, ap);
	va_end(ap);
}
