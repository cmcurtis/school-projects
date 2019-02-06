#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void letter_C (int height, int width) {
int i = 0, j = 0, k = 0, c = 0, count = 0;

c = width/2;

//define value of k
if (height % 10 <= 5)
	k = height/10;
else
	k = height/10 + 1;


//top of c
for (i = 1; i <= width; i++){
	if (i > k && i < width - k + 1){
		printf("C");
		count++;
		}
	else 
		printf(" ");
}
printf("\n");

//curve of c 
for (i = 1; i <= k; i++){
	for (j = 1; j <= k - i; j++){
		printf(" ");
	}
	printf("C");
 	for (j = 1; j <= count; j++){
		printf(" ");
	}
	count += 2;
	printf("C");
	printf("\n");

}

//body of c 
for (i = 0; i < height - (2*k + 2); i++){ 
	printf("C\n");
}
//curve of c
for (i = k; i > 0; i--){
	for (j = k - i; j > 0; j--){
		printf(" ");
	}
	printf("C");
	for (j = 1; j < count - 1; j++){
		printf(" ");
	}
	count = count - 2;
	printf("C");
	printf("\n");
}

//base of c
for (i = 1; i <= width; i++){
	if (i > k && i < width - k + 1)
		printf("C");
	else
		printf(" ");
}
printf("\n");

}

void letter_M (int height, int width) {
int i = 0, j = 0, c = 0, count = 0;
if (c % 2 == 0) 
	c = width/2;
else
	c = width/2 - 1;
 
for (i = 0; i < height; i++){
	printf("M");
	if (i < c){
		for (j = 0; j < i; j++){
			printf(" ");
			count++;
		}
		if (i < c - 1 || i == c - 1 && width % 2 != 0)
			printf("M");
		for (j = 0; j < width - count * 2 - 4; j++)
			printf(" ");
		count = 0;
		if (i < c - 1)
			printf("M");
		for (j = 0; j < i; j++)
			printf(" ");
	}
	else {
		for (j = 0; j < width - 2; j++)
			printf(" ");
	}
	printf("M");
	printf("\n");
}


}


void letter_U (int height, int width) {
int i = 0, j = 0, k = 0, count = 0;

if (height % 10 <= 5)
	k = height/10;
else
	k = height/10 + 1;


for(i = 1; i < height - k; i++){
	printf("U");
	for (j = 0; j < width - 2; j++){
		printf(" ");
		if (i == 1){
			count++;
		}
	}
	printf("U\n");
}

//curve of U
for(i = k; i > 0; i--){
	for (j = k - i; j > 0; j--){
		printf(" ");
	}
	printf("U");
	for (j = 1; j < count+1; j++){
		printf(" ");
	}
	count = count - 2;
	printf("U");
	printf("\n");

}

//base of U
for(i = 1; i < width; i++){
	if (i > k && i <= width - k)
		printf("U");
	else
		printf(" ");
}
printf("\n");


}

void letter_R (int height, int width) {
int i = 0, j = 0, k = 0, count = 0;

k = height/2;

count = width - k;
//top of R

for (i = 0; i <= width - k; i++)
	printf("R");
printf("\n");

for (i = (height - k)/2 - 1; i > 0; i--){
	printf("R");
	for (j = 1; j <= count; j++)
		printf(" ");
	count += 1;
	printf("R");
	printf("\n");
}


/*if (i > (height - k)/2 && i < height - k){
	printf("R");
	for (j = 1; j < width - 2; j++)
		printf(" ");
	printf("R");
	printf("\n");
}
*/
count = count - 1;
for (i = (height - k)/2 - 1; i > 0; i--){
	printf("R");
	for (j = 1; j <= count; j++){
		printf(" ");
	}
	count -= 1;
	printf("R");
	printf("\n");
}
for (i = 0; i <= width - k; i++)
	printf("R");
printf("\n");


//bottom of R
count = width - k;
for (i = 0; i < k;i++){
	printf("R");
	for (j = 1; j < count; j++)	 	
		printf(" ");
	count++;
	printf("R");
	printf("\n");
}

	
}




void letter_T (int height, int width) {
int i = 0, j = 0;

for (i = 0; i < width; i++){
	printf("T");
}

printf("\n");

for (i = 0; i < height - 1; i++){
	if (width % 2 == 0){
		for (j = 0; j < width/2 - 1; j++){
			printf(" ");
		}
		printf("TT");
		for (j = 0; j < width/2 - 1; j++){
			printf(" ");
		}
		printf("\n");
	}
	else {
		for (j = 0; j < width/2; j++) {
			printf(" ");
		}
		printf("T");
		for (j = 0; j < width/2; j++) {
			printf(" ");
		}
		printf("\n");
	}
}

}

void letter_I (int height, int width) {
int i = 0, j = 0, k = 0;

for (i = 0; i < width; i++) {
	printf("I");
}
printf("\n");

for (i = 0; i < height - 2; i++) {
	if (width % 2 == 0) {
		for (j = 0; j < width/2 - 1; j++){
			printf(" ");
		}
		printf("II");
		for (j = 0; j < width/2 - 1; j++){
			printf(" ");
		}
		printf("\n");
	}
	else {
		for (j = 0; j < width/2; j++){
			printf(" ");
		}
		printf("I");
		for (j = 0; j < width/2; j++){
			printf(" ");
		}
		printf("\n");
	}
}

for (i = 0; i < width; i++) {
	printf("I");
}
printf("\n");

}

void letter_S (int height, int width) {
int i = 0, j = 0, k = 0, count = 0, b = 0, even = 1;

if (height % 5 < 3)
	k = height/5;
else 
	k = height/5 + 1;

if (height % 2 == 1)
	even = 0;

b = (height - 2* k - 2)/2;

//top of S
// v top
for (i = 1; i <= width; i++){
	if (i > k && i < width - k + 1){
		printf("S");
		count++;
		}
	else 
		printf(" ");
}
printf("\n");

//curve
for (i = 1; i <= k; i++){
	for (j = 1; j <= k - i; j++){
		printf(" ");
	}
	printf("S");
 	for (j = 1; j <= count; j++){
		printf(" ");
	}
	count += 2;
	printf("S");
	printf("\n");

}
//body of S
for(i = b; i > 0; i--){
	for (j = b-i; j > 0; j--){
		printf(" ");
	}
	printf("S");
	printf("\n");
}
//middle of body

for (j = 0; j < b; j++)
	printf(" ");
for (j = 0; j < (width - 2 * b) + even; j++)
	printf("S");

printf("\n");

for(i = b - even; i > 0; i--){
	for (j = 1; j <= width - i; j++){
		printf(" ");
	}
	printf("S");
	printf("\n");
}	
	
//base of S
//curve
for (i = k; i > 0; i--){
	for (j = k - i; j > 0; j--){
		printf(" ");
	}
	printf("S");
	for (j = 1; j < count - 1; j++){
		printf(" ");
	}
	count = count - 2;
	printf("S");
	printf("\n");
}

//base
for (i = 1; i <= width; i++){
	if (i > k && i < width - k + 1)
		printf("S");
	else
		printf(" ");
}
printf("\n");


}

void number_1 (int height, int width) {
int i = 0, j = 0, k = 0;
if (height % 8 <= 4)
	k = height/8;
else
	k = height/8 + 1;

//top of 1
for (i = 0; i < k; i++){
	for(j = 0; j < width/2 - i - 2; j++){
		printf(" ");
	}
	printf("1");
	for(j = 0; j < i; j++)
		printf(" ");
	if (width % 2 == 0)
		printf("11");
	else 
		printf("1");
	printf("\n");
}


/*if (width % 2 == 0){
	for (i = 0; i < width/2-1; i++){
		printf(" ");
	}
	printf("11");
}
*/

//body of 1
for (i = 0; i < height - k - 1; i++){
	if (width % 2 == 0){
		for (j = 0; j < width/2-1; j++){
			printf(" ");
		}
		printf("11");
		for (j = 0; j < width/2-1; j++){
			printf(" ");
		}
	}
	else{
		for (j = 0; j < width/2; j++){
			printf(" ");
		}
		printf("1");
		for (j = 0; j < width/2; j++){
			printf(" ");
		}
	}
	printf("\n");
}

//base of 1

for (i = 0; i < width; i++){
	printf("1");
}
printf("\n");


}


int main(int argc, char *argv[]) {
int height = 0, width = 0;

height = atoi(argv[1]);
width = atoi(argv[2]);
letter_C(height, width);
printf("\n");
letter_M(height, width);
printf("\n");
letter_C(height, width);
printf("\n");
letter_U(height, width);
printf("\n");
letter_R(height, width);
printf("\n");
letter_T(height, width);
printf("\n");
letter_I(height, width);
printf("\n");
letter_S(height, width);
printf("\n");
number_1(height, width);
printf("\n");

return 0;
}
