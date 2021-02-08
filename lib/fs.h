#ifndef __FS_H_
#define __FS_H_

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

#endif /* __FS_H_ */
