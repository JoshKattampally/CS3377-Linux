#include <stdio.h>
#include <stdlib.h>

struct Box {
	int x;
	double y;
	char name[100];
};

struct Box boxes[100];

int main() {

	FILE *fp = fopen("data2b.dat", "rb");
	int n = fread(boxes, sizeof(struct Box), 100, fp);
	
	//int x;
	//double y;
	//char name[1000];

	for(int i=0; i<n; i++)
		printf("%d %lf %s\n", boxes[i].x, boxes[i].y, boxes[i].name);

	fclose(fp);
}
