MKSHELL=$PLAN9/bin/rc
ROOT=`{git rev-parse --show-toplevel}
CFLAGS=-Wall -Wextra -I$ROOT/lib -L$ROOT/lib -ffreestanding -std=c99 -nostdlib
LD=ld
CC=cc
AR=ar
LDFLAGS=-L$ROOT/lib
