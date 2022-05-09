#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 1000000
char input[MAXLEN];

//startup code

int main() {
	scanf("%s", input);
	printf("%d\n", strlen(input));
}
