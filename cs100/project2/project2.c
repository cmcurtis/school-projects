#include <stdio.h>
#include <string.h>
int main(){

char str [35];
int length = 0, i = 0, total = 0, valid = 1, numValue = 0, nextValue = 0, count = 0, negative = 0, min = 3999999;
 
scanf("%s", str);
	
length = strlen(str);


while (i < length){ 
	if (str[i] == '-' && length == 1){
		break;
	}
	else if (str[i] == '-'){
		negative = 1;
		i++;
		continue;
	}
	else if (str[i] == 'N'){
		numValue = 1000000;
	}
	else if (str[i] == 'E'){
		numValue = 500000;
	}
	else if (str[i] == 'B'){
		numValue = 100000;
	}
	else if (str[i] == 'K'){
		numValue = 50000;
	}
	else if (str[i] == 'Y'){
		numValue = 10000;
	}
	else if (str[i] == 'U'){
		numValue = 5000;
	}
	else if (str[i] == 'M'){
		numValue = 1000;
	}
	else if (str[i] == 'D'){
		numValue = 500;
	}
	else if (str[i] == 'C'){
		numValue = 100;
	}
	else if (str[i] == 'L'){
		numValue = 50;
	}
	else if (str[i] == 'X'){
		numValue = 10;
	}
	else if (str[i] == 'V'){
		numValue = 5;
	}
	else if (str[i] == 'I'){
		numValue = 1;
	}
	else{
		valid = 0;
		break;	
	}



	if (str[i + 1] == 'N'){
		nextValue = 1000000;
	}
	else if (str[i + 1] == 'E'){
		nextValue = 500000;
	}
	else if (str[i + 1] == 'B'){
		nextValue = 100000;
	}
	else if (str[i + 1] == 'K'){
		nextValue = 50000;
	}
	else if (str[i + 1] == 'Y'){
		nextValue = 10000;
	}
	else if (str[i + 1] == 'U'){
		nextValue = 5000;
	}
	else if (str[i + 1] == 'M'){
		nextValue = 1000;
	}
	else if (str[i + 1] == 'D'){
		nextValue = 500;
	}
	else if (str[i + 1] == 'C'){
		nextValue = 100;
	}
	else if (str[i + 1] == 'L'){
		nextValue = 50;
	}
	else if (str[i + 1] == 'X'){
		nextValue = 10;
	}
	else if (str[i + 1] == 'V'){
		nextValue = 5;
	}
	else if (str[i + 1] == 'I'){
		nextValue = 1;
	}
	

	if (numValue < nextValue){
		if (numValue == 1){
			if (nextValue == 5){
				numValue = nextValue - numValue;
			}
			else if (nextValue == 10){
				numValue = nextValue - numValue;
			}
		}
		else if (numValue == 10 && (nextValue == 50 || nextValue == 100)){
			numValue = nextValue - numValue;
		}
		else if (numValue == 100 && (nextValue == 500 || nextValue == 1000)){
			numValue = nextValue - numValue;
		} 
		else if (numValue == 1000 && (nextValue == 5000 || nextValue == 10000)){		
			numValue = nextValue - numValue;
		}
		else if (numValue == 10000 && (nextValue == 50000 || nextValue == 100000)){
			numValue = nextValue - numValue;
		}
		else if (numValue == 100000 && (nextValue == 500000 || nextValue == 1000000)){
			numValue = nextValue - numValue;
		}
		else{
			valid = 0;
			break;
		}

		if (min < numValue){
			valid = 0;
			break;
		}
		else{
			min = numValue;
		}
		
		i++;

	}
	else{
		if (numValue == nextValue){
			count++;
			if (count > 3){
				valid = 0;
				break;
			}
		}
		else{
			count = 0;
		}
		
		if (min < numValue){
			valid = 0;
			break;
		}
		else{
			min = numValue;

		}

	}

total = total + numValue;

i++;
}

if (negative == 1){
	total = total * (-1);
}
else{
	total = total;
}

if (valid == 0){
	printf("Error\n");
}
else{
	printf("%d\n", total);
}



return 0;
}
