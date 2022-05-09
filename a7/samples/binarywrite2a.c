#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	FILE *fp = fopen("data2a.dat", "wb");
	
	int x;
	double y;
	char name[1000];

	puts("Enter an integer, a real number and a string in each line, as many lines as you want...");
	while (scanf("%d%lf%s", &x, &y, name) == 3) {
		fwrite(&x, sizeof(int), 1, fp);
		fwrite(&y, sizeof(double), 1, fp);

		//write the string length first, followed by the actual contents of the string
		int n = strlen(name);
		fwrite(&n, sizeof(int), 1, fp);
		fwrite(name, sizeof(char), strlen(name), fp);
	}

	fclose(fp);
}
