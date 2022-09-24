#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <iostream>
#include <string>
#include <vector>
#include <pqxx/pqxx>
#include "Trx.h"

class DBService {
public:
    /**
     * Constructor del servicio, que usa variables de entorno para los datos de conexión.
     */
    DBService();

    /**
     * Destructor del servicio, que libera la conexión al motor de base de datos.
     */
    virtual ~DBService();

    /**
     * 
     * @param token Identificador único
     * @return El objeto asociado a este identificador.
     */
    Trx GetTrx(std::string token);

    /**
     * 
     * @param trx Objeto de transacción
     * @return true si se almaceno o false en cualquier otro caso.
     */
    bool GuardarTrx(Trx trx);
private:
    bool reconectar();
    pqxx::connection *conexion;
};

#endif /* DBSERVICE_H */

