#include "pic24_all.h"
uint16 check_val;
uint8 ones_count, first_one, c;

void main(void) {

check_val = 0xF508;
ones_count = 0;
first_one = 0;


for (c = 0 ; c < 16 ; c++) {
    	if(check_val>>c & 1) {
	 	ones_count = ones_count + 1;
    		if (ones_count == 1) {
			first_one = c;
		}
	}
}

}
