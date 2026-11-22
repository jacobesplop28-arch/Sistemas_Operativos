#include "Estadisticas.h"
#include <iostream>
#include <iomanip>
using namespace std;

Estadisticas::Estadisticas()
    : totalCiclos(0),
      procesosTerminados(0),
      sumaTurnosAtencion(0),
      sumaPorcentajeMemoria(0.0) {}
void Estadisticas::registrarCiclo(int memOcupadaKB, int memTotalKB) {
    totalCiclos++;
    if (memTotalKB > 0) {
        double porcentajeActual = (static_cast<double>(memOcupadaKB) / memTotalKB) * 100.0;
        sumaPorcentajeMemoria += porcentajeActual;
    }
}

void Estadisticas::registrarProcesoTerminado(int turnosAtendido) {
    procesosTerminados++;
    sumaTurnosAtencion += turnosAtendido;
}

void Estadisticas::mostrarReporteFinal() const {
    cout << "          ESTADISTICAS DE SIMULACION          \n";
    cout << "----------------------------------------------\n";
    cout << "Ciclos totales ejecutados: " << totalCiclos << "\n";
    cout << "Procesos terminados: " << procesosTerminados << "\n";
    double promMemoria = (totalCiclos > 0)
        ? (sumaPorcentajeMemoria / totalCiclos)
        : 0.0;
    double promTurnos = (procesosTerminados > 0)
        ? (static_cast<double>(sumaTurnosAtencion) / procesosTerminados)
        : 0.0;

    cout << fixed << setprecision(2);
    cout << "Ocupacion media de memoria: " << promMemoria << " %\n";
    cout << "Turnos medios por proceso: " << promTurnos << " turnos\n";
    cout << "-----------------------------------------------\n";
}