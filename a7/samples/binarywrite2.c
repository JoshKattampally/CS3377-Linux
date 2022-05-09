#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//C library functions: fopen(), fwrite(), fclose()

int main() {

	FILE *fp = fopen("data2.dat", "wb");
	
	int x;
	double y;
	char name[1000];

	puts("Enter an integer, a real number and a string in each line, as many lines as you want...");
	while (scanf("%d%lf%s", &x, &y, name) == 3) {

		//dump x contents, y contents, then the string including trailing 0
		fwrite(&x, sizeof(int), 1, fp);
		fwrite(&y, sizeof(double), 1, fp);
		fwrite(name, sizeof(char), strlen(name)+1, fp);
	}

	fclose(fp);
}
