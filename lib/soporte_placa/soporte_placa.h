#ifndef SOPORTE_PLACA_H
#define SOPORTE_PLACA_H

#include<stdint.h>

/** @file soporte_placa.h
 * @brief Capa de abstraccion de hardware y funciones de utilidad
 * 
 */

typedef enum SP_Pin{
    SP_PB9,
    SP_PC13,
    SP_NUM_PINES 
}SP_Pin;

typedef enum SP_ModoPin{
    SP_PIN_ENTRADA,             //Entrada flotante
    SP_PIN_ENTRADA_PULLUP,      //Entrada con resistencia pull-up interna
    SP_PIN_ENTRADA_PULLDN,      //Entrada con resistencia pull-down interna
    SP_PIN_SALIDA,              //Salida push-pull
    SP_PIN_SALIDA_OPEN_DRAIN    //Salida con drenador abierto
}SP_ModoPin;

/**
 * @brief Iniciamos el timer del sistema y configuramos la interrupcion del mismo
 * 
 */
void SP_init(void);

/**
 * @brief Interrumpe el Systick, segun el tiempo que ingresamos
 * 
 * @param tiempo 
 */
void SP_delay(uint32_t tiempo);

/**
 * @brief Configuramos el modo del pin
 * 
 * @param Pin 
 * @param modo 
 */
void SP_Pin_setModo(SP_Pin Pin,SP_ModoPin modo);


#endif
