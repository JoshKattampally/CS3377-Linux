#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Box {
	int x;
	double y;
	char name[100];
};

struct Box boxes[100];

int main() {

	//we can directly read into boxes.
	//int x;
	//double y;
	//char name[1000];

	puts("Enter an integer, a real number and a string in each line, as many lines as you want...");

	//read all the user input data first.
	int n=0;
	while (scanf("%d%lf%s", &boxes[n].x, &boxes[n].y, boxes[n].name) == 3) 
		n++;

	//now, open file, dump the boxes array and close!
	FILE *fp = fopen("data2b.dat", "wb");
	fwrite(boxes, sizeof(struct Box), n, fp);
	fclose(fp);
}
