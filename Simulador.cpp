#include "Simulador.h"
#include "InterfazConsola.h"
#include <iostream>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

Simulador::Simulador(const Configuracion& cfg)
    : config(cfg),
      memoria(cfg.memoriaMB),
      planificador(cfg.tamMaxProceso, cfg.cuantoMaxProceso),
      velocidadMs(1000),
      ejecutando(true),
      numeroCiclo(1) {}

void Simulador::leerControlesEnVivo() {
#ifdef _WIN32
    while (_kbhit()) {
        int tecla = _getch();
        if (tecla == '+' || tecla == '=') {
            if (velocidadMs > 200) {
                velocidadMs -= 200;
                cout << ">> Velocidad aumentada (Pausa actual: " << velocidadMs << " ms)\n";
            } else {
                cout << ">> Ya estas en la velocidad maxima (200 ms)\n";
            }
        } else if (tecla == '-') {
            if (velocidadMs < 5000) {
                velocidadMs += 200;
                cout << ">> Velocidad reducida (Pausa actual: " << velocidadMs << " ms)\n";
            } else {
                cout << ">> Ya estas en la velocidad minima (5000 ms)\n";
            }
        } else if (tecla == 'q' || tecla == 'Q' || tecla == 27) { // Q o ESC
            ejecutando = false;
            cout << "\n>> Condicion de paro activada por el usuario...\n";
        }
    }
#endif
}

EstadoCiclo Simulador::ejecutarUnCiclo() {
    EstadoCiclo estado{};
    estado.numeroCiclo = numeroCiclo;
    estado.velocidadMs = velocidadMs;

    Bloque candidato = planificador.getProcesoEnEspera();
    estado.procesoCandidato = candidato;
    bool pudoEntrar = (config.algoritmo == MEJOR_AJUSTE)
        ? memoria.insertarMejorAjuste(candidato)
        : memoria.insertarPeorAjuste(candidato);
    estado.entroProceso = pudoEntrar;

    if (pudoEntrar) {
        planificador.confirmarEntradaAMemoria();
    }
    estado.mapaTrasEntrada = memoria.obtenerMapaString();

    ResultadoCPU resCPU = planificador.ejecutarCicloCPU(config.cuantoSistema);
    estado.huboEjecucion = resCPU.huboProceso;
    estado.colaRRString = planificador.obtenerColaString();

    if (resCPU.huboProceso) {
        estado.procesoAtendidoPrevio = resCPU.procesoAntesDeResta;
        estado.procesoTermino = resCPU.termino;

        if (resCPU.termino) {
            estado.procesoDescargado = resCPU.procesoDespuesDeResta;
            memoria.liberarProceso(resCPU.procesoDespuesDeResta.id);
            estado.mapaTrasEjecucion = memoria.obtenerMapaString();
            estado.huboCondensacion = memoria.condensarHuecos();
            if (estado.huboCondensacion) {
                estado.mapaTrasCondensacion = memoria.obtenerMapaString();
            }
            stats.registrarProcesoTerminado(resCPU.procesoDespuesDeResta.ciclosAtendido);
        } else {
            memoria.actualizarCuanto(resCPU.procesoDespuesDeResta.id, resCPU.procesoDespuesDeResta.cuanto);
            estado.mapaTrasEjecucion = memoria.obtenerMapaString();
            estado.huboCondensacion = false;
        }
    } else {
        estado.procesoTermino = false;
        estado.huboCondensacion = false;
    }

    stats.registrarCiclo(memoria.getMemoriaOcupadaKB(), memoria.getMemoriaTotalKB());
    numeroCiclo++;
    return estado;
}

void Simulador::iniciar() {
    InterfazConsola::mostrarMemoriaInicial(memoria.obtenerMapaString());

    while (ejecutando) {
        leerControlesEnVivo();
        if (!ejecutando) break;

        EstadoCiclo estadoActual = ejecutarUnCiclo();
        InterfazConsola::renderizarCiclo(estadoActual);

        for (int t = 0; t < velocidadMs && ejecutando; t += 50) {
            leerControlesEnVivo();
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
    stats.mostrarReporteFinal();
}