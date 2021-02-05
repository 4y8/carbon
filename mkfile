MKSHELL=$PLAN9/bin/rc

OFILES=kernel/kernel.o\
	boot/boot.o

img:V: $OFILES
	echo "ee"

clean:V:
	for (file in $OFILES)
	    rm $file

%.o:
	cd `{dirname $stem.o}; mk; cd `{git rev-parse --show-toplevel}
