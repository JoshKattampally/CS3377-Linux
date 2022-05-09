// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

// structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
    char guessedChar;
    char word[100];
} message;
#define MAXQUOTES 100000
#define MAXLEN 1000

char *quotes[MAXQUOTES];
int numQuotes=0;


int main()
{
	key_t key;
	int msgid;
	
	srand(getpid() + time(NULL) + getuid());

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

    	// ftok to generate unique key - main server
    	key = ftok(getenv("HOME"), 1);
  
  	int counter=3;
	
	printf("Guess the current word: ");

	while (1) {

	int solvedChars = 0;


    	// msgget creates a message queue and returns identifier
    	msgid = msgget(key, 0666 | IPC_CREAT);
  		printf("Key %d Msgid %d\n", key, msgid);
	
    	// msgrcv to receive message
    	msgrcv(msgid, &message, sizeof(message), 1, 0);
    	// to destroy the message queue
    	//msgctl(msgid, IPC_RMID, NULL);
  
    	// display the message
    	printf("Data Received is : %s, %c \n", message.mesg_text, message.guessedChar);
		int clientPid = atoi(message.mesg_text);


	char *currentWord = quotes[rand() % numQuotes];
	printf("%s \n", currentWord);
	char guessed[strlen(currentWord) - 1];
	for(int i=0; i < strlen(currentWord)-1; i++) {
		guessed[i] = '*';
	}
	guessed[strlen(currentWord) - 1] = '\0';
	strcpy(message.word, guessed);
	printf("%s \n", message.word);
		//use clientPid to come up with key & msgid to respond
		int key2 = ftok(getenv("HOME"), clientPid);
    	int msgid2 = msgget(key2, 0666 | IPC_CREAT);
		sprintf(message.mesg_text, "%d %d", counter, counter+1);
    	msgsnd(msgid2, &message, sizeof(message), 0);
    	printf("Data Sent is : %s\n", message.mesg_text);

		counter += 2;
  	} 
  
    return 0;
}
