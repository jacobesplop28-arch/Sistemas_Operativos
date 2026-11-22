
#include "PlanificadorRR.h"
#include <cstdlib>

PlanificadorRR::PlanificadorRR(int _tamMax, int _cuantoMax)
    : siguienteId(1), tamMaxProceso(_tamMax), cuantoMaxProceso(_cuantoMax) {
    generarNuevoProcesoEnEspera();
}

void PlanificadorRR::generarNuevoProcesoEnEspera(){
    int minTam = (tamMaxProceso >= 32) ? 32 : 1;
    int tam = minTam + (std::rand() % (tamMaxProceso - minTam + 1));
    int cuanto = 1 + (std::rand() % cuantoMaxProceso);
    procesoEnEspera = Bloque(siguienteId++, tam, cuanto);
}

Bloque PlanificadorRR::getProcesoEnEspera() const{
    return procesoEnEspera;
}

void PlanificadorRR::confirmarEntradaAMemoria(){
    colaListos.push_back(procesoEnEspera);
    generarNuevoProcesoEnEspera();
}

bool PlanificadorRR::hayProcesosListos() const{
    return !colaListos.empty();
}

ResultadoCPU PlanificadorRR::ejecutarCicloCPU(int cuantoSistema){
    ResultadoCPU res;
    res.huboProceso = false;
    res.termino = false;
    if (colaListos.empty()) {
        return res;
    }
    res.huboProceso = true;

    //Tomamos proceso al frente de la cola, guardamos su estado previo exacto
    Bloque actual = colaListos.front();
    colaListos.pop_front();
    res.procesoAntesDeResta = actual;

    //Restamos el cuanto del sistema (uniprocesador, solo se resta a un proceso)
    actual.cuanto -= cuantoSistema;
    actual.ciclosAtendido++;
    if (actual.cuanto <= 0) {
        actual.cuanto = 0;
        res.termino = true;
    } 
    else {
        res.termino = false;
        colaListos.push_back(actual); // Regresa al final de la cola RR
    }

    //Guardamos el estado actualizado tras la resta
    res.procesoDespuesDeResta = actual;
    return res;
}

std::string PlanificadorRR::obtenerColaString() const {
    std::string salida = "Lista RR ";
    if (colaListos.empty()) {
        return salida + "[Vacia]";
    }
    for (const auto& p : colaListos) {
        salida += p.toString() + " ";
    }
    return salida;
}