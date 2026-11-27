#include "Simulador.h"
#include "InterfazConsola.h"
#include "PantallaCaca.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    PantallaCaca::mostrarBienvenida();

    Configuracion cfg = InterfazConsola::pedirConfiguracion();

    Simulador sim(cfg);
    sim.iniciar();

    PantallaCaca::mostrarDespedida();

    std::cout << std::endl << "Presione Enter para cerrar...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
