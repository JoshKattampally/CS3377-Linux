#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *fp = fopen("data.txt", "r");
	
	int x;
	double y;
	char name[1000];

	//read 3 things from the file, then write them out to screen
	//repeat until all the data is read from the file
	while (fscanf(fp, "%d%lf%s", &x, &y, name) == 3) 
		printf("%d %lf %s\n", x, y, name);

	fclose(fp);
}
