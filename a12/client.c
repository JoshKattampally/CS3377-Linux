nclude <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

struct mesg_buffer {
	long mesg_type;
		char mesg_text[100];
		} message;

		int game_over(char word[], int misses) {
			printf("The word is ");
				for (int i = 1; i < strlen(word); i++)
						printf("%c", word[i]);
							printf(". You missed %d times\n", misses);
							}
							int main() {
								key_t key;
									int msgid;
										
											int counter = 1;

												key = ftok(getenv("HOME"), 1);
													counter++;
														msgid = msgget(key, 0666 | IPC_CREAT);
															printf("Key %d Msgid %d\n", key, msgid);

																message.mesg_type = 1;
																	strcpy(message.mesg_text,"new");

																		msgsnd(msgid, &message, sizeof(message), 0);
																			printf("Data send is : %s \n", message.mesg_text);
																				
																					int numWrong = 0;
																						char tempStr[MAX];
																							char tempChar[MAX];
																								bool gameOver = false;
																									while(gameOver == false) {
																											key = ftok(getenv("HOME"), counter);
																													msgid = msgget(key, 0666 | IPC_CREAT);
																															

																																	msgrcv(msgid, &message, sizeof(message), 1, 0);
																																			
																																					msgctl(msgid, IPC_RMID, NULL);
																																							
																																									if (counter > 2) {
																																												if (strcmp(message.mesg_text, tempStr) == 0) {
																																																numWrong++;
																																																				printf("%c is not in the word\n", tempChar[0]);
																																																							}
																																																									}

																																																											strcpy(tempStr, message.mesg_text);
																																																													if (message.mesg_text[0] == '!') {
																																																																gameOver = true;
																																																																			printf("Game over\n");
																																																																						game_over(message.mesg_text, numWrong);
																																																																									continue;
																																																																											}
																																																																													

																																																																															key = ftok(getenv("HOME"), ++counter);
																																																																																	msgid = msgget(key, 0666 | IPC_CREAT);

																																																																																			printf("(Guess) Enter a letter in word %s > ", message.mesg_text);
																																																																																					fgets(message.mesg_text,MAX,stdin);
																																																																																							strcpy(tempChar, message.mesg_text);
																																																																																								
																																																																																										msgsnd(msgid, &message, sizeof(message), 0);
																																																																																												counter++;
																																																																																													}
																																																																																														return 0;

																																																																																														}
