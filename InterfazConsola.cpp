#include "InterfazConsola.h"
#include <iostream>

Configuracion InterfazConsola::pedirConfiguracion() {
    Configuracion cfg;
    std::cout << "=== SIMULADOR DE MEMORIA Y ROUND ROBIN ===" << endl;

    do {
        std::cout << "Seleccione algoritmo (" << MEJOR_AJUSTE << " = Mejor Ajuste, "
                  << PEOR_AJUSTE << " = Peor Ajuste): ";
        std::cin >> cfg.algoritmo;
    } while (cfg.algoritmo != MEJOR_AJUSTE && cfg.algoritmo != PEOR_AJUSTE);

    do {
        std::cout << "Tamano de memoria en MB (1, 4 u 8): ";
        std::cin >> cfg.memoriaMB;
    } while (cfg.memoriaMB != 1 && cfg.memoriaMB != 4 && cfg.memoriaMB != 8);

    do {
        std::cout << "Cuanto del sistema: ";
        std::cin >> cfg.cuantoSistema;
    } while (cfg.cuantoSistema <= 0);

    int maxMemKB = cfg.memoriaMB * 1024;
    do {
        std::cout << "Tamano maximo de proceso en KB (1 a " << maxMemKB << "): ";
        std::cin >> cfg.tamMaxProceso;
    } while (cfg.tamMaxProceso <= 0 || cfg.tamMaxProceso > maxMemKB);

    do {
        std::cout << "Cuanto maximo por proceso: ";
        std::cin >> cfg.cuantoMaxProceso;
    } while (cfg.cuantoMaxProceso <= 0);

    return cfg;
}

void InterfazConsola::mostrarMemoriaInicial(const std::string& mapaInicial) {
    std::cout << endl << "Memoria Inicial: " << endl << mapaInicial << endl;
}

void InterfazConsola::renderizarCiclo(const EstadoCiclo& estado) {
    std::cout << endl << "------------------------------------------------------------" << endl;
    std::cout << "CICLO " << estado.numeroCiclo << " | Vel: " << estado.velocidadMs
              << "ms | [+] Mas rapido [-] Mas lento [Q] Salir" << endl;
    std::cout << "------------------------------------------------------------" << endl;

    if (estado.entroProceso) {
        std::cout << "Entra Proceso " << estado.procesoCandidato.toString() << endl;
        std::cout << estado.mapaTrasEntrada << endl;
    } else {
        std::cout << "En espera Proceso " << estado.procesoCandidato.toString()
                  << " (Sin hueco suficiente, esperando espacio)" << endl;
    }

    if (estado.huboEjecucion) {
        std::cout << "Atendiendo proceso " << estado.procesoAtendidoPrevio.toString() << endl;
        std::cout << estado.colaRRString << endl;

        if (estado.procesoTermino) {
            std::cout << "Descargando proceso " << estado.procesoDescargado.toString() << endl;
            std::cout << estado.mapaTrasEjecucion << endl;
            if (estado.huboCondensacion) {
                std::cout << "Condensando huecos\n";
                std::cout << estado.mapaTrasCondensacion << endl;
            }
        } else {
            std::cout << estado.mapaTrasEjecucion << endl;
        }
    }
}

void InterfazConsola::mostrarMensaje(const std::string& msg) {
    std::cout << msg << "\n";
}
