#include <soporte_placa.h>
#include <stm32f1xx.h>
#include<stdint.h>



void SysTick_Handler(void); 

void SP_init(void){
    SystemCoreClockUpdate(); 

    uint32_t const frecuencia_hertz = SystemCoreClock;
    uint32_t const ciclos_por_milisegundo = frecuencia_hertz/1000;

    SysTick_Config(ciclos_por_milisegundo);
}

static uint32_t volatile ticks;

void Systick_Handler(void){
    ++ticks;
}

void SP_delay(uint32_t tiempo){
    uint32_t const ticks_inicial =ticks;
    uint32_t tiempo_transcurrido = ticks - ticks_inicial;
    while(tiempo_transcurrido < tiempo){
        tiempo_transcurrido = ticks - ticks_inicial;
    }
}

void SP_Pin_setModo(SP_Pin pin, SP_ModoPin modo){
    enum ConfigPin{
        ENTRADA_FLOTANTE = 0b0100,
        ENTRADA_PULLUP_PULLDN = 0b1000,
        SALIDA_2MHz = 0b0010,
        SALIDA_2MHz_OPEN_DRAIN = 0b0110
    };
}


