#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000
char input[MAXLEN];

//startup code

int main() {
	scanf("%s", input);
	int x = 0;
	int total = 0;

	for(x; x< strlen(input); x++) {
		if(input[x] == '(' && input[x + 1] == '(') {
			for (int i = x; i < strlen(input); i++) {
				if(input[i] == ')' && input[i + 1] == ')') {
					total++;
				}
			}
		}
	}
	printf("%d\n", total);
	return 0;
}
