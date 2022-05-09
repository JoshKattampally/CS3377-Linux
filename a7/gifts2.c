#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Go into ~veerasam/cs3377/a7/samples
//Look into binarywrite2b.c & binaryread2b.c for relevant code & ideas.

//let us assume that there will not be more than 100 players
#define MAXPLAYERS 100
//let us assume that max length for any name is 100 characters
#define MAXLEN 100

struct Player {
	char name[MAXLEN];
	double balance;
};

//struct is like class - we can use an array of struct (we can use like an array of objects).
struct Player players[MAXPLAYERS];
int numPlayers = 0; //set when actual player data is loaded

//search the player names array and return the index if specified name is found
//return -1 otherwise.
int findIndex(char *name) {
        for(int z=0; z<numPlayers; z++){
            if(strcmp(name, players[z].name) == 0)
               return z;
	}

        return -1;
}

// use binary data file gifts1.dat to read and store the results.

int main(int argc, char *argv[]) {
	//code here!
	FILE *filep;
	if(strcmp(argv[1], "new") == 0) {
		filep = fopen("gifts2.dat", "wb");
		for(int i = 2; i < argc; i+=2) {
			strcpy(players[numPlayers].name, argv[i]);
			players[numPlayers].balance = atof(argv[i+1]);

			numPlayers++;
		}
		fwrite(players, sizeof(struct Player), numPlayers, filep);
		fclose(filep);
	}
	else {
		filep = fopen("gifts2.dat", "rb");
		int j = 0;
		while(fread(&players[j], sizeof(struct Player), 1, filep) == 1) {
			numPlayers++;
			j++;
		}
		fclose(filep);


		char name[MAXLEN];
		strcpy(name, argv[1]);
//		printf("%s", name);
		int index = findIndex(name);
//		printf("%d", index);
		double amount = atof(argv[2]);
		players[index].balance -= amount;

		amount = amount / (argc - 3);
		for(int i = 3; i < argc; i++) {
			index = findIndex(argv[i]);
			players[index].balance += amount;
		}

		filep = fopen("gifts2.dat", "wb");
		fwrite(players, sizeof(struct Player), numPlayers, filep);
		fclose(filep);

	}
	
	
	filep = fopen("gifts2.dat", "rb");
	for(int k =0; k < numPlayers; k++) {
		fread(&players[k], sizeof(struct Player), 1, filep);
	 	printf("%10s: %5.2lf\n", players[k].name, players[k].balance);
	}
	fclose(filep);
}
