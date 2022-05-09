#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd = open("data1a.dat", O_RDONLY);
	
	int x;
	double y;
	char name[1000];

	while (read(fd, &x, sizeof(int)) > 0) {
		read(fd, &y, sizeof(double));

		//read the length of the string first.
		int n;
		read(fd, &n, sizeof(int));
		//now, read that many characters in one read() invocation.
		read(fd, name, n * sizeof(char));
		name[n] = 0; //terminate the string

		printf("%d %lf %s\n", x, y, name);
	}

	close(fd);
}
