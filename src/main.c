#include <stm32f1xx.h>
#define FREC_RELOJ 8000000 
#define CICLOS_PASADA_LAZO 

//Main es una funcion que no tiene parametros y retorna a un valor entero.
int main(void){              
    //Habilita el reloj para el puerto GPIO C
    RCC -> APB2ENR |= RCC_APB2ENR_IOPCEN; 

    //Configuro 13 como salida push pull
    GPIOC->CRH = (GPIOC->CRH & ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13)) | (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0);
    
    //Configuro 9 como entrada con pull up
    GPIOB->CRH = (GPIOB->CRH & ~ (GPIO_CRH_CNF9 | GPIO_CRH_MODE9)) | GPIO_CRH_CNF9_0;

    //Apaga la luz
    GPIOC -> ODR &= ~GPIO_ODR_ODR13;

    while (1)
    {
        /* Esperar que se presione el pulsador*/
        while ((GPIOB->IDR &GPIO_IDR_IDR9));
        GPIOC -> ODR |= GPIO_ODR_ODR13;
        //Espera 1 minuto si divido 8M en 100 me da 1 segundo
        for(unsigned i=0;i<60000; ++i){
            for (unsigned volatile j=0; j < ((FREC_RELOJ/1000)/CICLOS_PASADA_LAZO); ++j);
        }
       // Apaga Luz.
        GPIOC -> ODR |= GPIO_ODR_ODR13;
    }
    
    return 0;                //Retorna a la funcion y devuelve el valor 0.
}