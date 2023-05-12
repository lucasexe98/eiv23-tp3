#ifndef SOPORTE_PLACA_H
#define SOPORTE_PLACA_H

#include<stdint.h>
#include<stdbool.h>

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

/**
 * @brief Lee el buffer de entrada de un pin
 * 
 * @param Pin 
 * @return true Entrada ALTA 
 * @return false Entrada BAJA
 */
bool SP_Pin_read(SP_Pin Pin);

/**
 * @brief Escribe el buffer de salida de un Pin
 * 
 * @param Pin Handle al objeto Pin
 * @param valor True: Salida ALTA. False: Salida BAJA
 */
void SP_Pin_write(SP_Pin Pin, bool valor);

#endif
