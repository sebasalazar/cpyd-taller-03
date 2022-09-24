#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Trx.h"
#include "Utem.h"
#include "DBService.h"


/**
 * Función que muestra los participantes del grupo
 * @param programa nombre del ejecutable
 */
void participantes(std::string programa);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {

    /**
     * Incluir acá la lógica del programa
     * 
     */
    if (argc > 1) {
        std::ifstream archivo(argv[1]);
        std::string linea;
        std::getline(archivo, linea); // Al llamar esta operación, se ignora la línea

        double visa = 0;
        double mastercard = 0;
        double amex = 0;
        double diners = 0;

        DBService servicio;

        while (std::getline(archivo, linea)) {
            Trx trx(linea);

            if (trx.isVisa()) {
                visa += trx.GetComision(VISA_FEE);
            }

            if (trx.isMastercard()) {
                mastercard += trx.GetComision(MASTERCARD_FEE);
            }

            if (trx.isAmex()) {
                amex += trx.GetComision(AMEX_FEE);
            }

            if (trx.isDiners()) {
                diners += trx.GetComision(DINERS_FEE);
            }

            servicio.GuardarTrx(trx);
        }

        std::cout << std::endl; // salto de línea
        std::cout << "Comisión Visa:             " << visa << std::endl;
        std::cout << "Comisión Mastercard:       " << mastercard << std::endl;
        std::cout << "Comisión American Express: " << amex << std::endl;
        std::cout << "Comisión Diners:           " << diners << std::endl;

        archivo.close();
    } else {
        // Mostrar los integrantes
        participantes(argv[0]);
    }
    return EXIT_SUCCESS;
}

void participantes(std::string programa) {
    std::cout << std::endl << "=== Taller " << programa << " ===" << std::endl;
    std::cout << std::endl << "Sebastián Salazar Molina." << std::endl; // Reemplazar por su nombre
}
