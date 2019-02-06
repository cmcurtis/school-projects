#include <stdio.h>
#include <stdlib.h>

void fun (int num, char x){
	if (num == 0)
		return; 
	else {
		printf("%c", x);
		fun(num-1, x);
	}
}

void square (int num, int num2, char x){
	if (num2 == 0)
		return;
	else {
		fun(num, x);
		printf("\n");
		square(num, num2-1, x);
	}
}

void lowerLeft (int num, int num2, char x){
	if (num2 == num + 1)
		return;
	else {
		fun(num2, x);
		printf("\n");
		lowerLeft(num, num2 + 1, x);
	}
}	


void upperLeft (int num, char x){
	if (num == 0)
		return;
	else {
		fun(num, x);
		printf("\n");
		upperLeft(num-1, x);
	}
}

void lowerRight (int num, int num2, char x){
	if (num2 == num + 1)
		return;
	else {
		fun(num - num2, ' ' );
		fun(num2, x);
		printf("\n");
		lowerRight(num, num2 + 1,x);
	}
}

void upperRight (int num, int num2, char x){
	if (num2 == 0)
		return;
	else {
		fun(num - num2, ' ');
		fun(num2, x);
		printf("\n");
		upperRight (num, num2 - 1, x);
	}
}


int main(int argc, char* argv[]){
int num = 0;
char letter = 'X';

num = atoi(argv [1]);

printf("solid square:\n");
square(num, num, letter);
printf("\n");
printf("solid lower left triangle:\n");
lowerLeft(num, 1, letter);
printf("\n");
printf("solid upper left triangle:\n");
upperLeft(num, letter);
printf("\n");
printf("solid lower right triangle:\n");
lowerRight(num, 1, letter);
printf("\n");
printf("solid upper right triangle:\n");
upperRight(num, num, letter);
printf("\n");


return 0;
}
