#include <stdio.h>
#include <stdlib.h>
int **B;
int count = 0;

int isValid(int size, int A[size][size], int row, int col, int num){
int i = 0;

for (i = 0; i < size; i++){
	if (A[row][i] == num) return 0;
	if (A[i][col] == num) return 0;
}
if (row == col){
	for (i = 0; i < size; i++){
		if (A[i][i] == num) return 0;
	}
}
if (row == size - 1 - col){
	for (i = 0; i < size; i++){
		if (A[i][size-1-i] == num) return 0;
	}
}
return 1;
}


void saveSolution(int size, int A[size][size], int count){
int i = 0, j = 0;
if (count == 1){
	B = malloc(sizeof(int*)*size);
	for (i = 0; i < size; i++){
		B[i] = malloc(sizeof(int) * size);
		for (j = 0; j < size; j++){
			B[i][j] = A[i][j];
		}	
	}
}

}

int magicSquare(int size, int A[size][size], int row, int col){
int i = 0, x = 0;

if (row == size){
	count++;
	saveSolution(size, A, count);
	return 1;
	}

if(A[row][col]){ 
	if (col == size - 1) {
		x = magicSquare(size, A, row + 1, 0);
		if (x != 0) return 1;
		}
	else {
		x = magicSquare(size, A, row, col + 1);
		if (x != 0) return 1;
		}
	return 0;
}
else{
for (i = 1; i <= size; i++){
	if (isValid(size, A, row, col, i)){
		A[row][col] = i;
		if (col == size - 1) {
			x = magicSquare(size, A, row + 1, 0);
			}
		else {
			x = magicSquare(size, A, row, col + 1);
			} 
		A[row][col] = 0;
	}
}

}

return x;
}

int main(int argc, char* argv[]){
FILE *input;
FILE *output;
int size = 0, i = 0, j = 0;


input = fopen(argv[1], "r");
output = fopen(argv[2], "w");


fscanf(input,"%d", &size);
int A[size][size];

for(i = 0; i < size; i++){
	for (j = 0; j < size; j++){
		fscanf(input, "%d", &A[j][i]);
	}
}

magicSquare(size, A, 0, 0);

fprintf(output, "%d\n", count);

if (count > 0){
for(i = 0; i < size; i++){
	for (j = 0; j < size; j++){
		fprintf(output, "%d ", B[j][i]);
	}
	fprintf(output, "\n");
} 
}

return 0;
}
