#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {

	int fd = open("data1a.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	int x;
	double y;
	char name[1000];

	puts("Enter an integer, a real number and a string in each line, as many lines as you want...");
	while (scanf("%d%lf%s", &x, &y, name) == 3) {
		write(fd, &x, sizeof(int));
		write(fd, &y, sizeof(double));

		//write the length of the string first.
		int n = strlen(name);
		write(fd, &n, sizeof(int));
		//now dump the string contents.
		write(fd, name, sizeof(char) * strlen(name));
	}

	close(fd);
}
