#include "pic24_all.h"
#if __PIC24HJ128GP502__
    #define LED1 _LATA0 // MicroStick II definitions
    #define CONFIG_LED1() CONFIG_RA0_AS_DIG_OUTPUT()
#endif
int main(void) {
    int count = 0;
    int swap = 0;
    CONFIG_LED1();
    LED1=0;
    while (1) // alternates every 5s
    { 
        LED1 = !LED1; // Toggle LED1
        if (count % 50 == 0 && count != 0) { swap = !swap; } // alternates every 5s
        if (swap == 0) { DELAY_MS(100); } // Delay 100ms
        else DELAY_MS(200);
        count++;
    }

return 0;
}