MKSHELL=$PLAN9/bin/rc
ROOT=`{git rev-parse --show-toplevel}
CFLAGS=-Wall -Wextra -I$ROOT/lib -ffreestanding -nostdinc -nostdlib -nostartfiles
