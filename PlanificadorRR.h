
}#ifndef PLANIFICADOR_RR_H
#define PLANIFICADOR_RR_H

#include "Bloque.h"
#include <deque>
#include <string>

class PlanificadorRR{
private:
    std::deque<Bloque> colaListos;
    Bloque procesoEnEspera;
    int siguienteId;
    int tamMaxProceso;
    int cuantoMaxProceso;

public:
    PlanificadorRR(int _tamMax,int _cuantoMax);

    void generarNuevoProcesoEnEspera();
    Bloque getProcesoEnEspera() const;
    void confirmarEntradaAMemoria();
    bool hayProcesosListos() const;
    ResultadoCPU ejecutarCicloCPU(int cuantoSistema);
    std::string obtenerColaString() const;
};

#endif