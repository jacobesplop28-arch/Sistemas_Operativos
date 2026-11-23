#ifndef GESTOR_MEMORIA_H
#define GESTOR_MEMORIA_H

#include "Bloque.h"
#include <list>
#include <string>

class GestorMemoria {
private:
    std::list<Bloque> bloques;
    int memoriaTotalKB;

    bool insertarEnIterador(std::list<Bloque>::iterator it, const Bloque& proc);

public:
    GestorMemoria(int memoriaMB);

    bool insertarMejorAjuste(const Bloque& proc);
    bool insertarPeorAjuste(const Bloque& proc);
    void actualizarCuanto(int idProceso, int nuevoCuanto);

    void liberarProceso(int idProceso);
    bool condensarHuecos();

    int getMemoriaOcupadaKB() const;
    int getMemoriaTotalKB() const;
    std::string obtenerMapaString() const;
};

#endif