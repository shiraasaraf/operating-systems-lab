
#include <unistd.h>
#include "stdio.h"
#include "wait.h"
#include <stdlib.h>


int main (int argc, char *argv[])
{
	int size;

	printf("Enter number of processes (nodes in tree): ");
	scanf("%d", &size);

	int* tree = (int*)malloc(size * sizeof(int));

	printf("Enter number of children for each process (Level Order):\n");
	for (int i = 0; i < size; i++) {
		int cell;
		printf("Process %d: ", i);
		scanf("%d", &tree[i]);
	}

	printf("\nTree in level order (index = process ID, value = num of children):\n [ ");
	for (int i = 0; i < size; i++) {
		printf("%d ", tree[i]);
	};
	printf("]\n");

	free(tree);

	return 0;

}


