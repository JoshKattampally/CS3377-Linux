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
	int leftParenthesis = 0;

	for(x; x< strlen(input); x++) {
		if(input[x] == '(' && input[x + 1] == '(') {
			leftParenthesis++;
		}
		if(input[x] == ')' && input[x + 1] == ')') {
			total+=leftParenthesis;
		}
	}
	
	printf("%d\n", total);
	return 0;
}
