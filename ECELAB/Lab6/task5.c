#include "pic24_all.h"
#if __PIC24HJ128GP502__
    #define CONFIG_LEDR() CONFIG_RB15_AS_DIG_OUTPUT()
	#define CONFIG_LEDG() CONFIG_RB14_AS_DIG_OUTPUT()
	#define CONFIG_LEDB() CONFIG_RB13_AS_DIG_OUTPUT()
    #define LEDR _LATB15 // MicroStick II definition
	#define LEDG _LATB14 // MicroStick II definition
	#define LEDB _LATB13 // MicroStick II definition

//SW1 configuration
inline void CONFIG_SW1() {
	CONFIG_RB12_AS_DIG_OUTPUT();
	ENABLE_RB12_PULLUP();
}

//SW2 configuration
inline void CONFIG_SW2() {
	CONFIG_RB11_AS_DIG_OUTPUT();
	ENABLE_RB11_PULLUP();
}

#define SW1 _RB12
#define SW1_PRESSED() (SW1==0)
#define SW1_RELEASED() (SW1==1)

#define SW2 _RB11
#define SW1_PRESSED() (SW2==0)
#define SW1_RELEASED() (SW2==1)

#endif

int binToGray(int x)
	{
	int y = x >> 1;
	int g = x ^ y;

	return g; 
	}

int main(void) {
	CONFIG_LEDR();
	CONFIG_LEDG();
	CONFIG_LEDB();
	CONFIG_SW1();
	CONFIG_SW2();

	LEDR = 0;
	LEDG = 0;
	LEDB = 0;
	
	int b = 0;
	int g = 0;
	while(1){
		if (SW1 == 1 && SW2 == 1) {
				LEDR = 1;
				LEDG = 1;
				LEDB = 1;
			}
		}
		if (SW1 == 0 && SW2 == 1) {
			while (1) {
				if (SW1 == 1 && SW2 == 0){ 
					for (b = 0; b <= 7; b++) {
						LEDB = b & 1;
						LEDR = (b >> 1) & 1;
						LEDG = (b >> 2) & 1;
						DELAY_MS(500); 
						}
				}
				else break;
				}	
			}
		if (SW1 == 1 && SW2 == 0) {
			while (SW1 == 1 && SW2 == 0) {
				b = 0;
				for (b = 0; b <= 7; b++) {
					g = binToGray(b);
					LEDB = g & 1;
					LEDR = (g >> 1) & 1;
					LEDG = (g >> 2) & 1;
					DELAY_MS(500); 
					}
				}
			}	
		if (SW1 == 0 && SW2 == 0){
			while (SW1 == 0 && SW2 == 0) {
				LEDR = 1; 
				LEDG = 1; 
				LEDB = 1;
				DELAY_MS(100);
			}
		}
	continue;
	}

return 0;
}