MKSHELL = rc
CC = clang

# -Wall -Wextra
# -Weverything (use this when cleaning up the code base)
# No -Werror for now. It'll need a lot of work first.
CFLAGS = -Wall -Wextra -g -ggdb -fno-diagnostics-color \
	-std=gnu11 -O2 -fPIE -march=native -D_FORTIFY_SOURCE=2 \
	-fstack-protector-strong --param=ssp-buffer-size=1 -flto \
	`{pkg-config --cflags glew glfw3 libcurl sqlite3} \
	$CFLAGS

#	-fsanitize=undefined -fsanitize-trap=undefined \ # These cause problems; merits investigation
#	-Wno-disabled-macro-expansion # fprintf

LDFLAGS = -Wl,-z,relro,-z,now,--build-id -pie \
	`{pkg-config --libs glew glfw3 libcurl sqlite3} \
	-lm -lpthread \
	$LDFLAGS

all:V: $TARGS

%:Q: %.o
	echo $CC -o $target $prereq
	$CC $CFLAGS $LDFLAGS -o $target $prereq

%.o:Q: %.c
	echo $CC -c -o $target $stem.c
	$CC $CFLAGS -c -o $target $stem.c

clean:V:
	rm -f $TARGS *.o
