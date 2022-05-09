#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd = open("data1.dat", O_RDONLY);
	
	int x;
	double y;
	char name[1000];

	while (read(fd, &x, sizeof(int)) > 0) {
		read(fd, &y, sizeof(double));
		int i=0;
		do {
			read(fd, &name[i], sizeof(char));
		} while (name[i++]);

		printf("%d %lf %s\n", x, y, name);
	}

	close(fd);
}
