#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
int i = 0, num = 0, j = 0, k = 0;

num = atoi(argv[1]);

printf("solid square:\n");
for (i = 0; i < num; i++){ 
	for (j = 0; j < num; j++){ 
		printf("X");
	}	
	printf("\n");
}


printf("\n");

printf("solid lower left triangle:\n");
for (i = 0; i < num; i++){
	for (j = 0; j <= i; j++){
		printf("X");
	}
	printf("\n");
}
		

printf("\n");

printf("solid upper left triangle:\n");
for (i = num; i >= 1; --i){
	for (j = 0; j < i; j++){
		printf("X");
	}
	printf("\n");
}
	
printf("\n");

printf("solid lower right triangle:\n");
for (i = 0; i < num; ++i){
	for (j = 1; j < num - i; ++j){
		printf(" ");
	}
		for (k = 0; k <= i; ++k){
			printf("X");
		}
		printf("\n");
	}
		

	printf("\n");

	printf("solid upper right triangle:\n");
	for (i = num; i >= 1; --i){
	for (j = 0; j <= num; j++){  
		printf("X");
		for (k = 0; k <= num - j; k++){
			printf(" ");
		}
	}
	printf("\n");
}
		
return 0;
}
