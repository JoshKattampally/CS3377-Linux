#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *fp = fopen("data.txt", "w");
	
	int x;
	double y;
	char name[1000];

	puts("Enter an integer, a real number and a string in each line, as many lines as you want...");

	//read 3 things from the user, then write them out to the file
	//repeat until the user indicators end-of-file: press Control+D together
	while (scanf("%d%lf%s", &x, &y, name) == 3) 
		fprintf(fp, "%d %lf %s\n", x, y, name);

	fclose(fp);
}
