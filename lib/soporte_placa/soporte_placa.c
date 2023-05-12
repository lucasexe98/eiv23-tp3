#include <soporte_placa.h>
#include <stm32f1xx.h>
#include<stdint.h>
#include<stdbool.h>


void SysTick_Handler(void); 

void SP_init(void){
    SystemCoreClockUpdate(); 

    uint32_t const frecuencia_hertz = SystemCoreClock;
    uint32_t const ciclos_por_milisegundo = frecuencia_hertz/1000;

    SysTick_Config(ciclos_por_milisegundo);
}

static uint32_t volatile ticks;

void SysTick_Handler(void){
    ++ticks;
}

void SP_delay(uint32_t tiempo){
    uint32_t const ticks_inicial =ticks;
    uint32_t tiempo_transcurrido = ticks - ticks_inicial;
    while(tiempo_transcurrido < tiempo){
        tiempo_transcurrido = ticks - ticks_inicial;
    }
}


typedef struct ST_Pin{
    GPIO_TypeDef * puerto; 
    int nrPin;
}ST_Pin;

static ST_Pin const pines[SP_NUM_PINES] = {
    [SP_PB9]={.puerto=GPIOB,.nrPin=9},
    [SP_PC13]={.puerto=GPIOC,.nrPin=13}
};

static ST_Pin const * pinDeHandle(SP_Pin Pin){
    return &pines[Pin];
}


static void habilitaRelojPuerto(GPIO_TypeDef const *puerto){
    enum{BYTES_POR_PERIFERICO = (uint32_t)GPIOB - (uint32_t)GPIOA,  //Numero de bytes entre las estructuras GPIO
        DIR_BASE_BUS_APB2 = APB2PERIPH_BASE}; 
    int const OFFSET_PUERTO_EN_BUS_APB2 = ((((uint32_t)(puerto) - DIR_BASE_BUS_APB2) / BYTES_POR_PERIFERICO)); 
    int const OFFSET_BIT_HABILITACION_EN_APB2ENR = OFFSET_PUERTO_EN_BUS_APB2;
    uint32_t const MASCARA_HABILITACION_PUERTO = 1UL << OFFSET_BIT_HABILITACION_EN_APB2ENR; 
    RCC->APB2ENR |= MASCARA_HABILITACION_PUERTO;
}

static void config_modo(ST_Pin const *pin_pt, int bits_modo){
    int const offset = (pin_pt->nrPin % 8)*4; // posicion de pin_pt 0-7 en CRL *4 y de 8-15 CRH *4
    uint32_t const mascara = 0xF;
    if (pin_pt->nrPin < 8){
        pin_pt->puerto->CRL =  (pin_pt->puerto->CRL & ~(mascara << offset))
                          | ((bits_modo & mascara)<<offset); 
    }else{
        pin_pt->puerto->CRH =  (pin_pt->puerto->CRH & ~(mascara << offset))
                          | ((bits_modo & mascara)<<offset); 
    }
}

void SP_Pin_setModo(SP_Pin Pin, SP_ModoPin modo){
    enum ConfigPin{
        ENTRADA_FLOTANTE = 0b0100,
        ENTRADA_PULLUP_PULLDN = 0b1000,
        SALIDA_2MHz = 0b0010,
        SALIDA_2MHz_OPEN_DRAIN = 0b0110
    };

    ST_Pin const *pin_pt = pinDeHandle(Pin);
    __disable_irq();
    habilitaRelojPuerto(pin_pt->puerto);
    switch (modo)
    {
    case SP_PIN_ENTRADA:
        config_modo(pin_pt,ENTRADA_FLOTANTE);
    break;
    case SP_PIN_ENTRADA_PULLUP:
        config_modo(pin_pt,ENTRADA_PULLUP_PULLDN);
        pin_pt->puerto->BSRR = (1 << pin_pt->nrPin);
    break;
    case SP_PIN_ENTRADA_PULLDN:
        config_modo(pin_pt,ENTRADA_PULLUP_PULLDN);
        pin_pt->puerto->BRR =( 1 << pin_pt->nrPin);
    break;
    case SP_PIN_SALIDA:
        config_modo(pin_pt,SALIDA_2MHz);
    break;
    case SP_PIN_SALIDA_OPEN_DRAIN:
        config_modo(pin_pt,SALIDA_2MHz_OPEN_DRAIN);
    break;
    default:
    break;
    }
    __enable_irq();
}

bool SP_Pin_read (SP_Pin Pin){
     return pines[Pin].puerto->IDR & (0x1UL << pines[Pin].nrPin);
}

void SP_Pin_write (SP_Pin Pin, bool valor){
    if (valor)
        pines[Pin].puerto->BSRR = (0x1UL << pines[Pin].nrPin);
    else
        pines[Pin].puerto->BRR  =  (0x1UL << pines[Pin].nrPin);
}