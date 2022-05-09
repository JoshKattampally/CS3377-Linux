#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Go into ~veerasam/cs3377/a7/samples
//Look into binarywrite1.c & binaryread1.c OR binarywrite1a.c & binaryread1a.c 
//for relevant code & ideas.

//let us assume that there will not be more than 100 players
#define MAXPLAYERS 100
//let us assume that max length for any name is 100 characters
#define MAXLEN 100

//arrays to store the player names and balances
char names[MAXPLAYERS][MAXLEN];
double balances[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int i=0; i<numPlayers; i++)
            if(strcmp(name, names[i]) == 0)
               return i;

        return -1;
}

// use binary data file gifts1.dat to read and store the results.

int main(int argc, char *argv[]) {
	//code here!
	int p = 0;
	if(strcmp(argv[1], "new") == 0) {
//		printf("hello world");
		
		for(int i=2; i<argc; i+=2) {
//			printf("%s", argv[i]);
//			printf("%f", argv[i+1]);
			strcpy(names[p], argv[i]);
			balances[p] = atof(argv[i+1]);
			p++;
		}
//		printf("p: %d", p);

	}
	printf("balance: %f", balances[0]);
	int fd = open("gifts1.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	write(fd, balances, sizeof(double)*p);
	close(fd);


	fd = open("gifts1.dat", O_RDONLY);
	int i = 0;
	double currentBalance = 23;
	read(fd, &currentBalance, sizeof(double));
	printf("%f", currentBalance);
	
	close(fd);
}
