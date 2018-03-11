#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

struct stat at;

void printAcP() {
	printf("Access privileges \t: ");
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
	printf("\n");
}

void printType() {
	printf("File type \t\t: ");
	mode_t mode = at.st_mode;
	if (S_ISBLK(mode) != 0)
		printf("Block Special File\n");
	else if (S_ISCHR(mode) != 0)
		printf("character special file\n");
	else if (S_ISDIR(mode) != 0)
		printf("directorie\n");
	else if (S_ISFIFO(mode) != 0)
		printf("Pipe and FIFO special file\n");
	else if (S_ISLNK(mode) != 0)
		printf("Symbolic link\n");
	else if (S_ISREG(mode) != 0)
		printf("regular file\n");
	else if (S_ISSOCK(mode) != 0)
		printf("socket\n");
	else
		printf("external link\n");
}

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		printf("2 arguments required\n");
		return 0;
	}
	int fd = lstat(argv[1], &at);

	printf("------------------- %s ------------------------\n", argv[1]);

	printType();
	printAcP();

	printf("inode-Number \t\t: %d\n", at.st_ino);
	printf("Device number \t\t: dev = %d rdev = %d\n", at.st_rdev, at.st_dev);
	printf("Links count \t\t: %d\n", at.st_nlink);
	printf("UID \t\t\t: %d\n", at.st_uid);
	printf("GID \t\t\t: %d\n", at.st_gid);
	printf("File size \t\t: %d Bytes\n", at.st_size);
	printf("Last access \t\t: %s", asctime(gmtime(&at.st_atimespec)));
	printf("Last modification \t: %s", asctime(gmtime(&at.st_mtimespec)));
	printf("Last inode change \t: %s", asctime(gmtime(&at.st_ctimespec)));
	return 0;
}