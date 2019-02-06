#include <stdio.h>
int main (){

int number = 0, thousands = 0, hundreds = 0, tens = 0, units = 0, thousandsRemainder = 0, hundredsRemainder = 0, tensRemainder = 0;
scanf("%d", &number);

if (number >= 1 && number <= 3999){
	thousands = number / 1000;
	thousandsRemainder = number % 1000;
	hundreds = thousandsRemainder / 100;
	hundredsRemainder = thousandsRemainder % 100;
	tens = hundredsRemainder / 10;
	tensRemainder = hundredsRemainder % 10;
	units = tensRemainder % 10;


	if (number >= 1000){
		if (thousands == 1){
			printf("M");
		}
		else if (thousands == 2){	
			printf("MM");
		}
		else if (thousands == 3){
			printf("MMM");
		}
	}	
	if (number >= 100){
		if (hundreds == 1){
			printf("C");
		}	
		else if (hundreds == 2){
			printf("CC");
		}
		else if (hundreds == 3){
			printf("CCC");
		}
		else if (hundreds == 4){
			printf("CD");
		}	
		else if (hundreds == 5){
			printf("D");
		}
		else if (hundreds == 6){
			printf("DC");
		}
		else if (hundreds == 7){
			printf("DCC");
		}
		else if (hundreds == 8){
			printf("DCCC");
		}
		else if (hundreds == 9){
			printf("CM");
		}
	}
	if (number >= 10){
		if (tens == 1){
			printf("X");
		}
		else if (tens == 2){
			printf("XX");
		}
		else if (tens == 3){
			printf("XXX");
		}
		else if (tens == 4){
			printf("XL");
		}
		else if (tens == 5){
			printf("L");
		}
		else if (tens == 6){
			printf("LX");
		}
		else if (tens == 7){
			printf("LXX");
		}
		else if (tens == 8){
			printf("LXXX");
		}
		else if (tens == 9){
			printf("XC");
		}
	}
	if (number >= 1){
		if (units == 1){
			printf("I");
		}
		else if (units == 2){
			printf("II");
		}
		else if (units == 3){
			printf("III");
		}
		else if (units == 4){
			printf("IV");
		}
		else if (units == 5){
			printf("V");
		}
		else if (units == 6){
			printf("VI");
		}
		else if (units == 7){
			printf("VII");
		}
		else if (units == 8){
			printf("VII");
		}
		else if (units == 9){
			printf("IX");
		}
	}
	printf("\n");
}
else if (number < 1){
	printf("The number %d is too small\n", number);
}
else{
	printf("The number %d is too large\n", number);
}

return 0;
}

