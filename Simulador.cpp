#include "Simulador.h"
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
            }
            cout << ">> Velocidad aumentada (Pausa actual: " << velocidadMs << " ms)\n";
        } else if (tecla == '-') {
            if (velocidadMs < 5000) {
                velocidadMs += 200;
            }
            cout << ">> Velocidad reducida (Pausa actual: " << velocidadMs << " ms)\n";
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

void Simulador::imprimirEstadoBasico(const EstadoCiclo& estado) const {
    cout << "\n------------------------------------------------------------\n";
    cout << "CICLO " << estado.numeroCiclo << " | Pausa: " << estado.velocidadMs
         << " ms | Controles: [+] Rapido  [-] Lento  [Q/ESC] Salir\n";
    cout << "------------------------------------------------------------\n";
    if (estado.entroProceso) {
        cout << "Entra Proceso " << estado.procesoCandidato.toString() << "\n";
        cout << estado.mapaTrasEntrada << "\n";
    } else {
        cout << "En espera Proceso " << estado.procesoCandidato.toString()
             << " (Sin espacio suficiente, esperando liberacion)\n";
    }
    if (estado.huboEjecucion) {
        cout << "Atendiendo proceso " << estado.procesoAtendidoPrevio.toString() << "\n";
        cout << estado.colaRRString << "\n";

        if (estado.procesoTermino) {
            cout << "Descargando proceso " << estado.procesoDescargado.toString() << "\n";
            cout << estado.mapaTrasEjecucion << "\n";
            if (estado.huboCondensacion) {
                cout << "Condensando huecos\n";
                cout << estado.mapaTrasCondensacion << "\n";
            }
        } else {
            cout << estado.mapaTrasEjecucion << "\n";
        }
    }
}

void Simulador::iniciar() {
    cout << "\nMemoria Inicial:\n" << memoria.obtenerMapaString() << "\n";
    while (ejecutando) {
        leerControlesEnVivo();
        if (!ejecutando) break;
        EstadoCiclo estadoActual = ejecutarUnCiclo();
        imprimirEstadoBasico(estadoActual);
        this_thread::sleep_for(chrono::milliseconds(velocidadMs));
    }
    stats.mostrarReporteFinal();
}