
#include "pch.h"
#include <iostream>

int main(int argc, char** argv) {

	if (argc == 1) return -1;

	if ((strcmp(argv[1], "plane") == 0) && (argc == 3)) {
		int x = atoi(argv[2]);
		printf("%d \n", x);
	}
	else if ((strcmp(argv[1], "box") == 0) && (argc >= 5)) {
		int x = atoi(argv[2]);
		int y = atoi(argv[3]);
		int z = atoi(argv[4]);
		int d = 0;
		if (argc == 6) {
			d = atoi(argv[5]);
			printf("%d-%d-%d-%d \n", x, y, z, d);
		}
		else printf("%d-%d-%d \n", x, y, z);
	}
	else if ((strcmp(argv[1], "sphere") == 0) && (argc == 5)) {
		int r = atoi(argv[2]);
		int slices = atoi(argv[3]);
		int stacks = atoi(argv[4]);
		printf("%d-%d-%d \n", r, slices, stacks);
	}
	else if ((strcmp(argv[1], "cone") == 0) && (argc == 6)) {
		int r = atoi(argv[2]);
		int h = atoi(argv[3]);
		int slices = atoi(argv[4]);
		int stacks = atoi(argv[5]);
		printf("%d-%d-%d-%d \n", r, h, slices, stacks);
	}
	else {
		printf("Por favor, verifique os argumentos inseridos.\n");
	}

}
