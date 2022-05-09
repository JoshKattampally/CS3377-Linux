#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXQUOTES 10000
#define MAXLEN 1000

char *quotes[MAXQUOTES];
int pipes[100][2], tochild[2], toparent[2];
int numQuotes=0;
char *commands[10];
int numCommands;

//runs a simple command
//cmdname arg1 arg2 arg3 ...
void runCommand(char *command) {
	//split and assemble the arguments and invoke execvp()
	//use strtok(..)
	char *arguments[MAXLEN];
	char *currentCommand = strtok(command, " \n");
	arguments[0] = currentCommand;
	//printf("command %s\n", currentCommand);
	int i = 1;
	while((arguments[i] = strtok(NULL, " \n")) != NULL)
		i++;

	execvp(currentCommand, arguments);
	fputs("I hope you do not see this", stderr);
}

//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 
void child(int i) {
	//rewire pipes to 0 and 1 
	//close unnecessary pipes
	//run ith command
	//runCommand(commands[i]);
	//printf("made it: %d", i);
	if(i != 0) { //if it is not the first pipe
		close(0);
		dup(pipes[i-1][0]);
	}
	if(i != numCommands-1) {//if it is not the last pipe
		close(1);
		dup(pipes[i][1]);
	}
	for(int l = 0; l<numCommands-1; l++) {
		close(pipes[l][0]);
		close(pipes[l][1]);
	}
	
	runCommand(commands[i]);
}

void processLine(char *line) {
	char *pipePtr = strchr(line, '|');
	char *equalPtr = strchr(line, '=');
	if (pipePtr) { //not NULL
		//command has several sub-commands connected with pipes
		//setup commands array
		//setup pipes array
		//create children --> invoke child(i) in a loop
		//cmd0 | cmd1 | cmd2 | cmd3 | cmd4 
		
		int i = 0;
		commands[i] = strtok(line, "|\n");
		i++;
		while((commands[i] = strtok(NULL, "|\n")) != NULL)
			i++;
		numCommands = i;
		
		//printf("%d" , numCommands);
		//create operations-1 pipes
		for(int j = 0; j < numCommands-1; j++) {
			pipe(pipes[j]);
		}

		//fork for each command
		for(int k = 1; k < numCommands; k++) {
			if(!fork()){
				child(k);
			}
		}
		child(0);
		wait(NULL);

	} else if (equalPtr) {
		//command has = operator, so 2 commands --> 2 processes
		commands[0] = strtok(line, "=");
		commands[1] = strtok(NULL, "\n");

		pipe(tochild);
		pipe(toparent);

		if(fork() >0) {
			close(1);
			dup(tochild[1]);

			close(0);
			dup(toparent[0]);

			close(toparent[0]);
			close(toparent[1]);
			close(tochild[0]);
			close(tochild[1]);

			runCommand(commands[0]);
		}
		else {
			close(0);
			dup(tochild[0]);

			close(1);
			dup(toparent[1]);

			close(toparent[0]);
			close(toparent[1]);
			close(tochild[0]);
			close(tochild[1]);

			runCommand(commands[1]);
		}
    } else 
		//it is a simple command, no pipe or = character
		runCommand(line);
}

int main() {
	char line[MAXLEN];
	FILE *fp = fopen("quotes.txt", "r");

	if(!fp) {
	        puts("quotes.txt cannot be opened for reading.");
		exit(1);
	}
	int i=0;

	while(fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc (strlen(line) +1);
		strcpy(quotes[i], line);
		i++;
	}
	numQuotes = i;
	printf("%d quotes were read.\n", numQuotes);

	// infinite loop to serve the customer
	while (1) {
		//output a random quote to stderr
		fputs(quotes[rand()%numQuotes], stderr);
		fprintf(stderr, "# ");
		//get the user input
		fgets(line, 1000, stdin);

		//spawn a child for taking care of it
		if (fork() == 0) 
			processLine(line);

		//wait the child to finish the job!
		int x=0;
		wait(&x);
	}
}
