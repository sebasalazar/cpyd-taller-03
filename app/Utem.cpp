#include "Utem.h"

bool Utem::comienzaCon(std::string texto, std::string comienza) {
    bool ok = false;
    try {
        if (texto.rfind(comienza, 0) == 0) {
            ok = true;
        }
    } catch (...) {
        std::cerr << "Ha ocurrido un error fatal." << std::endl;
        ok = false;
    }
    return ok;
}

