#include "Simulador.h"
#include "InterfazConsola.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Configuracion cfg = InterfazConsola::pedirConfiguracion();

    Simulador sim(cfg);
    sim.correr();

    std::cout << endl << "Presione Enter para cerrar...";
    std::cin.ignore();
    std::cin.get();
    return 0;
}
