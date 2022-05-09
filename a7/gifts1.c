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
        for(int x=0; x<numPlayers; x++){
            if(strcmp(name, names[x]) == 0)
               return x;
	     }

        return -1;
}

// use binary data file gifts1.dat to read and store the results.

int main(int argc, char *argv[]) {
	//code here!
	int p = 0;
	int fd;
	if(strcmp(argv[1], "new") == 0) {
		fd = open("gifts1.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		for(int i=2; i<argc; i+=2) {
			char arg[MAXLEN];
			double arg2;
			strcpy(arg, argv[i]);
			arg2 = atof(argv[i+1]);

//			printf("argv 3 %f", arg2);
			write(fd, &arg2, sizeof(double));
//			printf("name: %s", arg);
			write(fd, arg, sizeof(char) * (strlen(arg) + 1));
		}
		close(fd);
	}
	else {
		fd = open("gifts1.dat", O_RDONLY);
		while (read(fd, &balances[p], sizeof(double)) > 0) {
			int i =0;
			do {
				read(fd, &names[p][i], sizeof(char));
			} while(names[p][i++]);
			
//			printf("%s\n", names[p]);
			p++;
			numPlayers++;
		}
//		printf("P: %d\n", p);
		close(fd);

		double amount = atof(argv[2]);
		char currentName[MAXLEN];
		strcpy(currentName, argv[1]);
		int index= findIndex(currentName);


	
//		printf("Name: %s\n", names[0]);
//		printf("Name INdex 1: %s\n", argv[1]);
//		printf("Amount: %f\n", amount);
//		printf("Index: %d\n", index);

		if(index != -1) {
			balances[index] = balances[index] - amount;
		}
//		printf("%d", argc);
		amount = amount / (argc -3);
		for(int i = 3; i < argc; i++) {
			index = findIndex(argv[i]);
			balances[index] = balances[index] + amount;
		}
		fd = open("gifts1.dat", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
		for(int f = 0; f < p; f++) {
			char arg[MAXLEN];
			strcpy(arg, names[f]);
			double arg2 = balances[f];

//                      printf("argv 3 %f", arg2);
			write(fd, &arg2, sizeof(double));
//                      printf("name: %s", arg);
                        write(fd, arg, sizeof(char) * (strlen(arg) + 1));
		}

		close(fd);	
	}
	p = 0;
	fd = open("gifts1.dat", O_RDONLY);
	while (read(fd, &balances[p], sizeof(double)) > 0) {
		int i =0;
		do {
			read(fd, &names[p][i], sizeof(char));
		} while (names[p][i++]);
		printf("%10s: %5.2lf\n", names[p], balances[p]);
		p++;
	}

	close(fd);
}
