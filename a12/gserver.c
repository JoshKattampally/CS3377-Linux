#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>

//read all the quotes from quotes.txt
//when client asks for a motivational quote, select one randomly and send it out.

#define MAXQUOTES 100000
#define MAXLEN 1000

char *quotes[MAXQUOTES];
int numQuotes=0;
bool solved=false;

int main() {
	char line[MAXLEN];

	FILE *fp = fopen("dictionary.txt", "r");
	if (!fp) {
		puts("dictionary.txt cannot be opened for reading.");
		exit(1);
	}

	int i=0;

	//read one line at a time, allocate memory, then copy the line into array
	while (fgets(line, MAXLEN, fp)) {
		quotes[i] = (char *) malloc (strlen(line)+1);
		strcpy(quotes[i], line);
		i++;
	}
	numQuotes = i;
	printf("%d words were read.\n", numQuotes);

	srand(getpid() + time(NULL) + getuid());
	// puts(quotes[rand() % numQuotes]);
	
	//create a named pipes to read client's requests
	char filename[MAXLEN];
	sprintf(filename, "/tmp/%s-%d", getenv("USER"), getpid());
	mkfifo(filename, 0600);
	chmod(filename, 0622);
	printf("Send your requests to %s\n", filename);

	while (1) {

		FILE *fp = fopen(filename, "r");
		if (!fp) {
			printf("FIFO %s cannot be opened for reading.\n", filename);
			exit(2);
		}
		printf("Opened %s to read...\n", filename);

		//wait for clients' requests
		while(fgets(line, MAXLEN, fp)) {

			char *cptr = strchr(line, '\n');
			if (cptr) 
				*cptr = '\0';
	
			//create a child to work with this client
			if (fork() == 0) {
				FILE *clientfp = fopen(line, "w");
				//create and send new server fifo to the client
				//for private one-on-one communcations
				char serverfifo[MAXLEN];
				sprintf(serverfifo, "/tmp/%s-%d", getenv("USER"), getpid());
				mkfifo(serverfifo, 0600);
				chmod(serverfifo, 0622);

				fprintf(clientfp, "%s\n", serverfifo);
				fflush(clientfp);

				FILE *serverfp = fopen(serverfifo, "r");
			
				char letter;
		                char *currentWord = quotes[rand() % numQuotes];
				char guessed[strlen(currentWord)-1];
				for(int q=0; q<strlen(currentWord)-1; q++) {
					guessed[q] = '*';
					fprintf(clientfp, " %c", guessed[q]);
					fflush(clientfp);
				}
				printf("Random word: %s", currentWord);
				
				int lettersSolved=0;
				while (fscanf(serverfp, " %c", &letter)) {
					for(int i=0; i<strlen(currentWord)-1; i++) {
						if(letter == guessed[i]) {
							fprintf(clientfp, "This letter was already guessed");
							i = strlen(currentWord);
						}
						else if(letter == currentWord[i]){
							guessed[i] = letter;
							lettersSolved++;
						}
					}
					//fprintf(clientfp, "(Guess) Enter a letter in ");
					//fflush(clientfp);
					//client is asking for specific quote# - send that quote!
					for(int i=0; i<strlen(currentWord)-1; i++) {
						fprintf(clientfp, "%c ", guessed[i]);
						fflush(clientfp);
						printf("%c ", guessed[i]);
						fflush(stdout);
					}
					fprintf(clientfp, "\n");
					
					if(lettersSolved >= strlen(currentWord)-1)
						break;
					for(int i=0; i<strlen(currentWord)-1; i++) {
						if(letter == guessed[i]) {
							fprintf(clientfp, "This letter was already guessed");
							i = strlen(currentWord);
						}
						else if(letter == currentWord[i]){
							guessed[i] = letter;
							lettersSolved++;
						}
					}
				}
				printf("outside while");

				exit(0);
			}
		}
		
		fclose(fp);
	}
}

