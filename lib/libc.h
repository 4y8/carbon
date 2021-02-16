#include <stdarg.h>

#define nil ((void *)0)

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;

int abs(int value);

int itoa(int value, char *buf, int base, int bufsize);

void memcpy(byte *src, byte *dest, ulong n);

int strlen(char *s);
int streq(char *s1, char *s2);


enum seek {
	SEEK_CUR,
	SEEK_BEGIN,
	SEEK_END
};

long seek(int fd, long off, enum seek type);
int open(char *file, int mode);
int create(char *file, int mode, long perm);
int close(int fd);
int chdir(char *path);
long read(int fd, void *buf, long nbytes);
long write(int fd, void *buf, long nbytes);

void puts(char *s);
void putchar(char c);
void clear_terminal(void);

typedef int (*Fmt)(char *buffer, int n, int flags, va_list ap);

void vprint(char *fmt, va_list ap);
void print(char *fmt, ...);
int vsnprint(char *fmt, char *buffer, int n, va_list ap);
int snprint(char *fmt, char *buffer, int n, ...);

void fmtinstall(Fmt fun, int c);
