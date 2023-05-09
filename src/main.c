#include <stm32f1xx.h>
#define FREC_RELOJ 8000000 
#define CICLOS_PASADA_LAZO 13

int main(void){              //Main es una funcion que no tiene parametros y retorna a un valor entero.
    RCC -> APB2ENR |= RCC_APB
    //configurar GPIO pag 172 del PDF
    //CONIFIGURO C13 como salida
    GPIOC->CRH = (GPIOC->CRH & ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13))
                GPIO_CRH_MODE13_1;
    // Configuro 09 como entrada con pull up
    GPIOB->CRH = (GPIOB->CRH & ~ (GPIO_CRH_CNF9 | GPIO_CRH_CNF9))
                | GPIO_CRH_CNF9_1;
    GPIO -> ODR |= GPIO_ODR_ODR9;
    //para inicializar los puertos, tengo que ponerlos todos en 0


    //Inicio con la luz apagada
    GPIO

    while (1)
    {
        /* Esperar que se presione el pulsador*/
        while ((GPIOB->IDR &GPIO_IDR_IDR9));
        GPIIOC -> ODR |= GPIO_ODR_ODR13;
        //Espera 1 minuto si divido 8M en 100 me da 1 segundo
        for(unsigned i=0;i<60000; ++i){
            for (unsigned volatile j=0; j < ((REC_RELOJ/1000)/CICLOS_PASADA_LAZO); ++j);
        }
       // Apaga Luz.
        GPIOC -> ODR |= GPIO_GDR_ODR13;
    }
    



    return 0;                //Retorna a la funcion y devuelve el valor 0.
}