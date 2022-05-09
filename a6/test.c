#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define LINESIZE 16

//use one command line argument
int main(int argc, char *argv[]) {
	int args = 1;
	int fd = open("diagonal.out", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	char space=' ';
	if (argc != 2) {
		printf("Usage: diagonal <textstring>\n");
		return -1;
	}
	
	//create a file so that 16 rows of empty will appear with od -c command
	for(int line=0; line<LINESIZE; line++)
		for(int column=0; column<LINESIZE; column++)
			write(fd, &space, 1);

	while(args<argc) {
		int n=strlen(argv[args]);

		int offset = LINESIZE*LINESIZE*(args-1);
		for(int j=0; j<n; j++) {
			if(args%2 ==1)
				lseek(fd,offset+(LINESIZE+1)*j,SEEK_SET);
			else
				lseek(fd, offset+(LINESIZE*(j+1)-(j+1)),SEEK_SET);
			write(fd, argv[args][j], 1);
		}
		args++;
	}
	close(fd);
	puts("diagonal.out has been created. Use od -c diagonal.out to see the contents.");
}
