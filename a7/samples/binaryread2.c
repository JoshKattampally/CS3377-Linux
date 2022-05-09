#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *fp = fopen("data2.dat", "rb");
	
	int x;
	double y;
	char name[1000];

	//direct memory upload from file: load int, load double, load string 
	while (fread(&x, sizeof(int), 1, fp) == 1) {
		fread(&y, sizeof(double), 1, fp);
		int i=0;
		do {
			fread(&name[i], sizeof(char), 1, fp);
		} while (name[i++]);

		printf("%d %lf %s\n", x, y, name);
	}

	fclose(fp);
}
