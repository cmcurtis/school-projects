#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){

int i = 0, j = 0, k = 0, num = 0, space = 0;

num = atoi(argv[1]);

printf("hollow square:\n");
for (i = 0; i < num; i++){
	for (j = 0; j < num; j++){
		if ( i == 0 || i == num - 1)
			printf("X");
		else if (j == 0 || j == num -1)
			printf("X");
		else
			printf(" ");
	}

printf("\n");
}


printf("\n");

printf("hollow lower left triangle:\n");
for (i = 1; i <= num; i++){
	for (j = 1; j <= i; j++){
		if (j == 1 || j == i || i == num)
			printf("X");
		else
			printf(" ");
	}
printf("\n");
}

printf("\n");

printf("hollow upper left triangle:");


printf("\n");

return 0;
}

