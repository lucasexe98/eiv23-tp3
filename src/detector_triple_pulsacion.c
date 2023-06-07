#include <detector_triple_pulsacion.h>
#include <maquina_estado_impl.h>
#include <controlador_luz.h>

static Resultado estadoEspera(Maquina *maq,Evento evento);
static Resultado estadoContador(Maquina *maq,Evento evento);

void DetectorTriple_init(DetectorTriple *self,DespachoRetardado *despacho, uint32_t tiempoLimite, Maquina *destino ){
    Maquina_init(&self->maquina,estadoEspera);
    self->despacho= despacho;
    self->contadorPulsaciones=0;
    self->tiempoLimite=tiempoLimite;
    self->destino=destino;
}

Maquina  *DetectorTriple_asMaquina(DetectorTriple *self){
    return &self->maquina;
}

static Resultado estadoEspera(Maquina *maq,Evento evento){
    DetectorTriple *self=(DetectorTriple*)maq;
    Resultado r={0};
    switch (evento)
    {
    case EV_RESET:
        r.codigo=RES_PROCESADO;
        break;
    case EV_BOTON_PULSADO:
        self->contadorPulsaciones=1;
        r.codigo = RES_TRANSICION;
        r.nuevoEstado = estadoContador;
        DespachoRetardado_programa(self->despacho,maq,EV_TIMEOUT_BOTON,self->tiempoLimite);
        Maquina_despacha(self->destino,EV_BOTON_PULSADO);
        break;

    default:
        r.codigo= RES_IGNORADO;
        break;
    }
    return r;
}

static Resultado estadoContador(Maquina *maq,Evento evento){
    DetectorTriple *self=(DetectorTriple*)maq;
    Resultado r={0};
    switch (evento)
    {
    case EV_TIMEOUT_BOTON:
        r.codigo=RES_TRANSICION;
        r.nuevoEstado= estadoEspera;
        break;
    
    case EV_BOTON_PULSADO:
        ++(self->contadorPulsaciones);
        r.codigo=RES_PROCESADO;
        if (self->contadorPulsaciones==3)
        {
            r.codigo=RES_TRANSICION;
            r.nuevoEstado= estadoEspera;
            Maquina_despacha(self->destino,EV_MUDANZA);
        }
        break;
    default:
        r.codigo= RES_IGNORADO;
        break;
    }
    return r;
}