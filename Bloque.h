#ifndef BLOQUE_H
#define BLOQUE_H
#include <string>

const int MEJOR_AJUSTE = 1;
const int PEOR_AJUSTE  = 2;

struct Configuracion {
    int algoritmo;          // MEJOR_AJUSTE (1) o PEOR_AJUSTE (2)
    int memoriaMB;          // 1, 4 u 8 MB
    int cuantoSistema;      // Cuanto que se resta en cada turno de CPU
    int tamMaxProceso;      // Tamano maximo aleatorio en KB
    int cuantoMaxProceso;   // Cuanto maximo aleatorio generado por proceso
};

class Bloque {
public:
    int id;                 // 0 = Hueco libre | > 0 = ID de proceso
    int tamano;             // Tamano en KB
    int cuanto;             // Cuanto restante (0 si es hueco)
    int ciclosAtendido;     // Contador interno para estadisticas
    Bloque(int _id = 0, int _tam = 0, int _cuanto = 0)
        : id(_id), tamano(_tam), cuanto(_cuanto), ciclosAtendido(0) {}
    bool esHueco() const {
        return id == 0;
    }
    std::string toString() const {
        return "[" + std::to_string(id) + "," +
               std::to_string(tamano) + "," +
               std::to_string(cuanto) + "]";
    }
};

struct ResultadoCPU {
    bool huboProceso;               // false si la cola de listos estaba vacia
    Bloque procesoAntesDeResta;     // Estado previo al turno 
    Bloque procesoDespuesDeResta;   // Estado tras restar cuantoSistema
    bool termino;                   // true si cuanto <= 0 y debe descargarse
};

struct EstadoCiclo {
    int numeroCiclo;
    int velocidadMs;

    bool entroProceso;
    Bloque procesoCandidato;
    std::string mapaTrasEntrada;

    bool huboEjecucion;
    Bloque procesoAtendidoPrevio;
    std::string colaRRString;

    bool procesoTermino;
    Bloque procesoDescargado;
    std::string mapaTrasEjecucion;
    bool huboCondensacion;
    std::string mapaTrasCondensacion;
};

#endif