#include "pic24_all.h"
#if __PIC24HJ128GP502__
#define LED1 LATB15 // MicroStick II definitions
#define CONFIG_LED1() CONFIG_RB15_AS_DIG_OUTPUT()

#define LED2 LATB1
#define CONFIG_LED2() CONFIG_RB2_AS_DIG_OUTPUT()	

#define SW1 _RB14
#define SW1_PRESSED() (SW1==0)
#define SW1_RELEASED() (SW1==1)

#define SW2 _RB12
#define SW1_PRESSED() (SW1==0)
#define SW1_RELEASED() (SW1==1)
	
inline void CONFIG_SW1()
{
	CONFIG_RB14_AS_DIG_OUTPUT();
	ENABLE_RB14_PULLUP;
}

inline void CONFIG_SW2()
{
	CONFIG_RB12_AS_DIG_OUTPUT();
	ENABLE_RB12_PULLUP;
}

		
#endif

typedef enum
{
		STEP1=0,
		STEP2,
		STEP3,
		STEP4,
		STEP5
} STATE;

int main(void) {
  	configBasic(HELLO_MSG);
    CONFIG_LED1();
	CONFIG_LED2();
	CONFIG_SW1();
	CONFIG_SW2();

	int count = 0;
	while(1){
		if (SW1a = 0 && SW1b = 1){
			LED1 = !LED1
			if (SW1a == 0 && SW1b == 1){ 
				for (int i = 0; i < 5; i++) { LED1 = !LED1; }
					if (SW1a == 0 && SW1b == 1){
						if (SW2 == 0){ continue; }
						if (SW1a == 0 && SW1b == 0) {
							while(count < 2){
								LED2 = !LED2;
								DELAY_MS(200);
								if (SW1 = 1) {
									count++;
									LED2 = 0;
								}
							LED2 = !LED2;
							DELAY_MS(100);
							if (SW2a == 0 && SW2b == 1) continue;
							}
						}
			}
		}

return 0;
}
