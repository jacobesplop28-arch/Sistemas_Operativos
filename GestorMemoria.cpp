#include "GestorMemoria.h"
#include <climits>

GestorMemoria::GestorMemoria(int memoriaMB) {
    memoriaTotalKB = memoriaMB * 1024;
    bloques.push_back(Bloque(0, memoriaTotalKB, 0));
}

bool GestorMemoria::insertarEnIterador(std::list<Bloque>::iterator it, const Bloque& proc) {
    if (it == bloques.end()) return false;

    int sobrante = it->tamano - proc.tamano;
    bloques.insert(it, proc);

    if (sobrante > 0) {
        it->tamano = sobrante;
    } else {
        bloques.erase(it);
    }
    return true;
}

bool GestorMemoria::insertarMejorAjuste(const Bloque& proc) {
    auto mejorIt = bloques.end();
    int menorSobrante = INT_MAX;

    for (auto it = bloques.begin(); it != bloques.end(); ++it) {
        if (it->esHueco() && it->tamano >= proc.tamano) {
            int sobrante = it->tamano - proc.tamano;
            if (sobrante < menorSobrante) {
                menorSobrante = sobrante;
                mejorIt = it;
            }
        }
    }
    return insertarEnIterador(mejorIt, proc);
}

bool GestorMemoria::insertarPeorAjuste(const Bloque& proc) {
    auto peorIt = bloques.end();
    int mayorTamano = -1;

    for (auto it = bloques.begin(); it != bloques.end(); ++it) {
        if (it->esHueco() && it->tamano >= proc.tamano) {
            if (it->tamano > mayorTamano) {
                mayorTamano = it->tamano;
                peorIt = it;
            }
        }
    }
    return insertarEnIterador(peorIt, proc);
}

void GestorMemoria::actualizarCuanto(int idProceso, int nuevoCuanto) {
    for (auto& b : bloques) {
        if (b.id == idProceso) {
            b.cuanto = nuevoCuanto;
            break;
        }
    }
}

void GestorMemoria::liberarProceso(int idProceso) {
    for (auto& b : bloques) {
        if (b.id == idProceso) {
            b.id = 0;
            b.cuanto = 0;
            break;
        }
    }
}

bool GestorMemoria::condensarHuecos() {
    bool huboCondensacion = false;
    auto it = bloques.begin();

    while (it != bloques.end()) {
        auto nextIt = std::next(it);
        if (nextIt != bloques.end() && it->esHueco() && nextIt->esHueco()) {
            it->tamano += nextIt->tamano;
            bloques.erase(nextIt);
            huboCondensacion = true;
        } else {
            ++it;
        }
    }
    return huboCondensacion;
}

int GestorMemoria::getMemoriaOcupadaKB() const {
    int ocupada = 0;
    for (const auto& b : bloques) {
        if (!b.esHueco()) ocupada += b.tamano;
    }
    return ocupada;
}

int GestorMemoria::getMemoriaTotalKB() const {
    return memoriaTotalKB;
}

std::string GestorMemoria::obtenerMapaString() const {
    std::string salida;
    for (const auto& b : bloques) {
        salida += b.toString() + " ";
    }
    return salida;
}