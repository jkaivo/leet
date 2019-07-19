.POSIX:

CFLAGS=-Wall -Wextra -Werror -Wpedantic

leet: leet.c

clean:
	rm -f *.o leet
