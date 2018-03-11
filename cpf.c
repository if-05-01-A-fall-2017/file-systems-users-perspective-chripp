#include "stdio.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#define MAX_N 2

struct stat at;

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		printf("3 arguments required\n");
		return 0;
	}

	int out = open(argv[2], O_WRONLY);
	if (out < 0) {
		out = creat(argv[2], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		out = open(argv[2], O_WRONLY);
	}
	int srcf = open(argv[1], O_RDONLY);
	if (srcf < 0) {
		printf("Source does not exist\n");
		return 0;
	}
	bool done = false;
	while (!done) {
		char data[MAX_N];
		int tmp = read(srcf, data, sizeof(data));
		if (tmp != MAX_N)
			done = true;
		write(out, data, tmp * sizeof(char));
	}

	write(out, '\0', sizeof(char));
	close(out);
	return 0;
}