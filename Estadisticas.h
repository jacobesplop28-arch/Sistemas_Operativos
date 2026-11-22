#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

class Estadisticas {
private:
    int totalCiclos;
    int procesosTerminados;
    long long sumaTurnosAtencion;
    double sumaPorcentajeMemoria;

public:
    Estadisticas();
    void registrarCiclo(int memOcupadaKB, int memTotalKB);
    void registrarProcesoTerminado(int turnosAtendido);
    void mostrarReporteFinal() const;
};
#endif