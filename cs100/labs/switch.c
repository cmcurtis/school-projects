#include <stdio.h>
#include <stdlib.h>

int main (){
int x = 0, t = 0, tR = 0, h = 0, hR = 0, te = 0, teR = 0, u = 0; 

printf("Enter a number from 1 to 3999:\n");

scanf("%d", &x);

t = x / 1000;
tR = x % 1000;
h = tR / 100;
hR = tR % 100;
te = hR / 10;
teR = hR % 10;
u = teR % 10;

switch (t){
	case (1):
		printf("M");
		break;
	case (2):
		printf("MM");
		break;
	case (3):
		printf("MMM");
		break;
	default:
		break;
}

switch (h){
	case (1):
		printf("C");
		break;
	case (2):
		printf("CC");
		break;
	case (3):
		printf("CCC");
		break;
	case (4):
		printf("CD");
		break;
	case (5):
		printf("D");
		break;
	case (6):
		printf("DC");
		break;
	case (7):
		printf("DCC");
		break;
	case (8):
		printf("DCCC");
		break;
	case (9):
		printf("CM");
		break;
	default:
		break;
}
switch(te){
	case(1):
		printf("X");
		break;
	case(2):
		printf("XX");
		break;
	case(3):
		printf("XXX");
		break;
	case(4):
		printf("XL");
		break;
	case(5):
		printf("L");
		break;
	case(6):
		printf("LX");
		break;
	case(7):
		printf("LXX");
		break;
	case(8):
		printf("LXXX");
		break;
	case(9):
		printf("XC");
		break;
	default:
		break;
}

switch (u){
	case (1):
		printf("I");
		break;
	case (2):
		printf("II");
		break;
	case (3):
		printf("III");
		break;
	case (4):
		printf("IV");
		break;
	case (5):
		printf("V");
		break;
	case (6):
		printf("VI");
		break;
	case (7):
		printf("VII");
		break;
	case (8):
		printf("VIII");
		break;
	case (9):
		printf("IX");
		break;
	default:
		break;
}
printf("\n");
		

return 0;
}
