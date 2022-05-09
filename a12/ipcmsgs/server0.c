#include <stdio.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define MAXLEN 1000
char words[90000][MAXLEN];

struct mesg_buffer {
    long mesg_type;
        char mesg_text[100];
	} message;

	int main() {
	FILE *datafile = fopen("dictionary.txt", "r");
	int count = 0;
	while(fgets(words[count], MAXLEN, datafile)) {
		count++;
	}
	fclose(datafile);
	key_t key;
	int msgid;
	while (1) {
		int counter = 1;
		key = ftok(getenv("HOME"), counter);
		srand(time(NULL));
		int randWord =  (rand() * 64 * 1024 + rand()) % count;
		if (randWord < 0)
			randWord = randWord * -1;
		int length = strlen(words[randWord]);
		char str[length];
		char helper_str[length];
		strcpy(helper_str, words[randWord]);
		for (int i = 0; i < length - 1; i++) {
			str[i] = '*';
		}
		helper_str[length - 1] = 0;
		str[length - 1] = 0;
		int numCorrect = 0;
		while (1) {
			msgid = msgget(key, 0666 | IPC_CREAT);
							
			msgrcv(msgid, &message, sizeof(message), 1, 0);
			msgctl(msgid, IPC_RMID, NULL);

			counter++;
			if (counter > 2) {
				for (int x = 0; x < length - 1; x++) {
					if (helper_str[x] == message.mesg_text[0]) {
						helper_str[x] = '*';
						str[x] = message.mesg_text[0];
						numCorrect++;
						break;
					}
				}
			}
			key = ftok(getenv("HOME"), counter);
			msgid = msgget(key, 0666 | IPC_CREAT);

			if (numCorrect == length - 1) {
				char result[MAXLEN] = "!";
				strcat(result, str);
				strcpy(message.mesg_text, result);
				} else { 
					strcpy(message.mesg_text,str);
				}
				msgsnd(msgid, &message, sizeof(message), 0);
				counter++;
				key = ftok(getenv("HOME"), counter);
				if (numCorrect == length - 1)
					break;
			}
		}
		return 0;
	}
