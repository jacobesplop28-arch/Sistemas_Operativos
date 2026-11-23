#ifndef INTERFAZ_CONSOLA_H
#define INTERFAZ_CONSOLA_H

#include "Bloque.h"
#include <string>

class InterfazConsola {
public:
    static Configuracion pedirConfiguracion();
    static void mostrarMemoriaInicial(const std::string& mapaInicial);
    static void renderizarCiclo(const EstadoCiclo& estado);
    static void mostrarMensaje(const std::string& msg);
};

#endif
