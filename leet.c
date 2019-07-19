#define _XOPEN_SOURCE 500
#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COLOR(_n) (31 + (_n % 9))

#define BUFSIZE 16

void hexdump(uintmax_t address, size_t n, unsigned char buf[static n])
{
	if (n > BUFSIZE) {
		n = BUFSIZE;
	}

	printf("\033[1m\r%015jx ", address);
	for (size_t i = 0; i < n; i++) {
		printf("\033[%hhdm%02hhx\033[0m ", COLOR(buf[i]), buf[i]);
		usleep(100 * buf[i]);
	}
	for (size_t i = n; i < BUFSIZE; i++) {
		printf("-- ");
	}

	for (size_t i = 0; i < n; i++) {
		printf("\033[%hhdm%c\033[0m", COLOR(buf[i]), isprint(buf[i]) ? buf[i] : '.');
		usleep(100 * buf[i]);
	}
	for (size_t i = n; i < 16; i++) {
		printf(".");
	}
}

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	unsigned char buf[BUFSIZE];
	uintmax_t address = 0;
	srand(time(NULL));

	for (;;) {
		for (size_t i = 0; i <= sizeof(buf); i++) {
			buf[i] = rand();
			hexdump(address, i, buf);
		}
		printf("\n");
		address += sizeof(buf);
	}
}
