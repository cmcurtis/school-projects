#include "pic24_all.h"
uint16 x, y;
uint8 count;

void main(void){
	count = 3;
	x = 1;
	y = 3;
	
	while( count != 0 ) {  
		if (count == 0) { return; }
		
		if( x == y ) { y = y + 1; }
		
		else 
			{
				if( x >= y ) { count = count - 1; }
				else { x = x + 2; }
		}
	}
}

