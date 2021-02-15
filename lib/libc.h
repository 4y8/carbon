#ifndef __LIBC_H_
#define __LIBC_H_

int abs(int value);

int itoa(int value, char *buf, int base, int bufsize);

#define nil ((void *)0)

#endif /* __LIBC_H_ */
