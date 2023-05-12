#include "soporte_placa.h"

int main (void){
    SP_init();
    SP_Pin_setModo(SP_PB9,SP_PIN_ENTRADA_PULLUP);
    SP_Pin_setModo(SP_PC13,SP_PIN_SALIDA);
    SP_Pin_write (SP_PC13,1);
    while (1)
    {
        if (!SP_Pin_read(SP_PB9))
        {
            SP_Pin_write (SP_PC13,0);
            SP_delay(60000);
            SP_Pin_write (SP_PC13,1);
        }
       
    }
return 0;
}