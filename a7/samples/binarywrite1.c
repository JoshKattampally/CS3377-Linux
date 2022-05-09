#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//using open(), write() and close() system calls

int main() {

	int fd = open("data1.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	int x;
	double y;
	char name[1000];

	puts("Enter an integer, a real number and a string in each line, as many lines as you want...");
	while (scanf("%d%lf%s", &x, &y, name) == 3) {
		write(fd, &x, sizeof(int));
		write(fd, &y, sizeof(double));
		write(fd, name, sizeof(char) * (strlen(name)+1));
	}

	close(fd);
}
