#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

struct stat at;

void printAcP() {
	printf((S_ISDIR(at.st_mode)) ? "d" : "-");
	printf((at.st_mode & S_IRUSR) ? "r" : "-");
	printf((at.st_mode & S_IWUSR) ? "w" : "-");
	printf((at.st_mode & S_IXUSR) ? "x" : "-");
	printf((at.st_mode & S_IRGRP) ? "r" : "-");
	printf((at.st_mode & S_IWGRP) ? "w" : "-");
	printf((at.st_mode & S_IXGRP) ? "x" : "-");
	printf((at.st_mode & S_IROTH) ? "r" : "-");
	printf((at.st_mode & S_IWOTH) ? "w" : "-");
	printf((at.st_mode & S_IXOTH) ? "x" : "-");
}

void printType(mode_t mode) {
	if (S_ISBLK(mode) != 0)
		printf("b");
	else if (S_ISCHR(mode) != 0)
		printf("c");
	else if (S_ISDIR(mode) != 0)
		printf("d");
	else if (S_ISFIFO(mode) != 0)
		printf("f");
	else if (S_ISLNK(mode) != 0)
		printf("Symbolic link\n");
	else if (S_ISREG(mode) != 0)
		printf("-");
	else if (S_ISSOCK(mode) != 0)
		printf("s");
}

int main(int argc, char const *argv[]) {
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (dir->d_name[0] != '.') {
				lstat(dir->d_name, &at);
				printType(at.st_mode);
				printf(" ");
				printAcP();
				printf("%5d%5d %9d", at.st_uid, at.st_gid, at.st_size);
				struct tm *i;
				i = gmtime(&at.st_mtimespec);
				printf("%6d-%2d-%2d-%2d-%2d ", (1990 + i->tm_year), i->tm_mon + 1, i->tm_mday, i->tm_hour + 1, i->tm_min + 1);
				printf("%s\n", dir->d_name);
			}
		}
		closedir(d);
	}
	return 0;
}