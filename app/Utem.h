#ifndef UTEM_H
#define UTEM_H

#include <iostream>
#include <string>
#include <iomanip>

namespace Utem {
    /**
     * 
     * @param texto Texto base
     * @param comienza Patrón de búsqueda
     * @return true si el texto comienza con el parámetro ingresado o false en cualquier otro caso.
     */
    bool comienzaCon(std::string texto, std::string comienza);
};

#endif /* UTEM_H */

