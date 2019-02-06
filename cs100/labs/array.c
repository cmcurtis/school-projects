#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
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

while(t == 1){
printf("M");
break;
}

while(t == 2){
printf("MM");
break;
}

while(t == 3){
printf("MMM");
break;
}

while(h == 1){
printf("C");
break;
}

while(h == 2){
printf("CC");
break;
}
while(h == 3){
printf("CCC");
break;
}

while(h == 4){
printf("CD");
break;
}

while(h == 5){
printf("D");
break;
}

while(h == 6){
printf("DC");
break;
}

while(h == 7){
printf("DCC");
break;
}

while(h == 8){
printf("DCCC");
break;
}

while(h == 9){
printf("CM");
break;
}

while(te == 1){
printf("X");
break;
}

while(te == 2){
printf("XX");
break;
}

while(te == 3){
printf("XXX");
break;
}

while(te == 4){
printf("XL");
break;
}

while(te == 5){
printf("L");
break;
}

while(te == 6){
printf("LX");
break;
}

while(te == 7){
printf("LXX");
break;
}

while(te == 8){
printf("LXXX");
break;
}

while(te == 9){
printf("XC");
break;
}

while(u == 1){
printf("I");
break;
}

while(u == 2){
printf("II");
break;
}

while(u == 3){
printf("III");
break;
}

while(u == 4){
printf("IV");
break;
}

while(u == 5){
printf("V");
break;
}

while (u == 6){
printf("VI");
break;
}

while (u == 7){
printf("VII");
break;
}

while (u == 8){
printf("VIII");
break;
}

while (u == 9){
printf("IX");
break;
}

printf("\n");

return 0;
}
