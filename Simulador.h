#ifndef SIMULADOR_H
#define SIMULADOR_H
#include "Bloque.h"
#include "GestorMemoria.h"
#include "PlanificadorRR.h"
#include "Estadisticas.h"

class Simulador {
private:
    Configuracion config;
    GestorMemoria memoria;
    PlanificadorRR planificador;
    Estadisticas stats;

    int velocidadMs;
    bool ejecutando;
    int numeroCiclo;

    void leerControlesEnVivo();
    EstadoCiclo ejecutarUnCiclo();
    void imprimirEstadoBasico(const EstadoCiclo& estado) const;

public:
    Simulador(const Configuracion& cfg);
    void iniciar();
};
#endif