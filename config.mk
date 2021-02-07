MKSHELL=$PLAN9/bin/rc
ROOT=`{git rev-parse --show-toplevel}
CFLAGS=-Wall -Wextra -I$ROOT/lib -ffreestanding -std=c99 -nostdlib
