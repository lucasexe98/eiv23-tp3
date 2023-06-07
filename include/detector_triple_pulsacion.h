#ifndef DETECTOR_TRIPLE_PULSACION_H
#define DETECTOR_TRIPLE_PULSACION_H
#include <maquina_estado.h>
#include "despacho_retardado.h"
#include <stdint.h>

typedef struct DetectorTriple{
    Maquina maquina;
    DespachoRetardado *despacho;
    uint32_t contadorPulsaciones;
    uint32_t tiempoLimite;
    Maquina *destino;

}DetectorTriple;

void DetectorTriple_init(DetectorTriple *self,DespachoRetardado *despacho , uint32_t tiempoLimite, Maquina *destino);

Maquina *DetectorTriple_asMaquina(DetectorTriple *self);


#endif
