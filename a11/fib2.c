#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
//       n: 0  1  2  3  4  5  6   7   8  ...

int fib(int n) {
	//create a pipe
	//create 2 children to compute fib(n-1) and fib(n-2)
	//write to pipe from each child & child is done!
	//parent read the results from pipe
	//and add and return.
	
	if(n == 0)
		return 0;
	else if(n == 1)
		return 1;
	int fds[2];
	pipe(fds);
	if (fork() == 0) {
		
		close(fds[0]);
		int return1 = fib(n-1);
		write(fds[1], &return1, sizeof(int));
		close(fds[1]);
		exit(0);
		//fib(..) --> write to pipe
	}
	else if (fork() == 0) {
		
		close(fds[0]);
		int return2 = fib(n-2);
		write(fds[1], &return2, sizeof(int));
		close(fds[1]);
		exit(0);
		//fib(..) --> write to pipe
	}
	else {
	int num1, num2;
	close(fds[1]);
	read(fds[0], &num1, sizeof(int));
	read(fds[0], &num2, sizeof(int));
	close(fds[0]);
	
	return num1 + num2;
	}
}


int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <number>\n", argv[0]);
		exit(1);
	}
	int n = atoi(argv[1]);
	printf("Result: %d\n", fib(n));
}
