#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLEN 1000

char operators[100];
int fds[100][2];
int operatorCount=0;
int numpipes;

void child(int index) {
	close(0);
	if(!index) 
		dup(fds[0][0]);
	else 
		dup(fds[operatorCount+index][0]);

	close(3);
	dup(fds[index+1][0]);

	close(1);
	dup(fds[operatorCount+index+1][1]);

	//close all pipes
	for(int i=0; i<numpipes; i++) {
		close(fds[i][0]);
		close(fds[i][1]);
	}
	
	switch(operators[index]) {
		case '+':
			execl("./add", "add", NULL);
		case '-':
			execl("./subtract", "subtract", NULL);
		case '*':
			execl("./multiply", "multiply", NULL);
		case '/':
			execl("./divide", "divide", NULL);
	}
	fputs("I hope you do not see this", stderr);
	exit(1);

}

int main(int argc, char *argv[]) {
	char line[MAXLEN], *temp;

	if(argc <2) {
		fprintf(stderr, "Usage: %s <filename> \n",argv[0]);
		exit(1);
	}

	FILE *dataFile = fopen(argv[1], "r");
	//read the first line - it contains the configuration
	fgets(line, MAXLEN, dataFile); 

	// sample content for line: a + b - c
	strtok(line, " \n"); //skip the symbol representing variable/parameter
	while (temp = strtok(NULL, " \n")) {
		operators[operatorCount] = temp[0];
		//printf("operator: %c\n", operators[operatorCount]);
		operatorCount++;
		strtok(NULL, " \n"); //skip the symbol representing variable/parameter
	}

	//create the necessary number of pipes
	numpipes = operatorCount * 2 + 1;
	for(int i=0; i<numpipes; i++) {
		pipe(fds[i]);

	}

	//set up config with necessary number of children
	for(int i=0; i < operatorCount; i++) {
		if(!fork())
			child(i);
	}
	//whole system ready to go
	
	//read rest of the file and pump into the pipes
	int x;
	while(fscanf(dataFile, "%d", &x) > 0) {
		write(fds[0][1], &x, sizeof(int));
		//let us assume that line has that many pieces of data
		for(int i=1; i<=operatorCount; i++) {
			fscanf(dataFile, "%d", &x);
			write(fds[i][1], &x, sizeof(int));
		}
		//read the final output and display on the screen
		read(fds[2*operatorCount][0], &x, sizeof(int));
		printf("%d\n", x);
	}
}
