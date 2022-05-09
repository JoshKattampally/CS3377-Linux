#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *fp = fopen("data2a.dat", "rb");
	
	int x;
	double y;
	char name[1000];

	while (fread(&x, sizeof(int), 1, fp) == 1) {
		fread(&y, sizeof(double), 1, fp);

		//read the string length first, then read the actual string 
		int n=0;
		fread(&n, sizeof(int), 1, fp);
		fread(name, sizeof(char), n, fp);
		name[n] = 0;

		printf("%d %lf %s\n", x, y, name);
	}

	fclose(fp);
}
