#ifndef TRX_H
#define TRX_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include "Utem.h"

#define VISA_FEE 0.0045
#define MASTERCARD_FEE 0.005
#define AMEX_FEE 0.003
#define DINERS_FEE 0.008

class Trx {
public:
    /**
     * Constructor vacío
     */
    Trx();

    /**
     * Constructor por copia
     * @param orig Transacción de origen
     */
    Trx(const Trx& orig);

    /**
     * 
     * @param linea Una línea del archivo a procesar
     */
    Trx(std::string linea);

    /**
     * Destructor virtual
     */
    virtual ~Trx();

    /**
     * 
     * @return retorna el bin
     */
    std::string GetBin() const;
    /**
     * 
     * @param bin Primeros dígitos de una tarjeta
     */
    void SetBin(std::string bin);

    /**
     * 
     * @return retorna la estructura de la fecha
     */
    std::tm GetFecha() const;
    /**
     * 
     * @param fecha estructura de fecha
     */
    void SetFecha(std::tm fecha);
    /**
     * 
     * @param fecha String que representa la fecha
     * @param formato formato a procesar
     */
    void SetFecha(std::string fecha, std::string formato);

    /**
     * 
     * @return El monto de la transacción
     */
    long GetMonto() const;
    /**
     * 
     * @param monto el monto de la transacción
     */
    void SetMonto(long monto);

    /**
     * 
     * @return Identificador único de la operación.
     */
    std::string GetToken() const;
    /**
     * 
     * @param token identificador único de la operación.
     */
    void SetToken(std::string token);

    /**
     * 
     * @return La fecha en formato dd-mm-YYYY
     */
    std::string GetFechaLocal() const;

    /**
     * 
     * @return La fecha en formato YYYY-mm-ddTHH:MM:SSZ
     */
    std::string GetFechaJson() const;

    /**
     * 
     * @return true si el bin es Visa o false en cualquier otro caso.
     */
    bool isVisa() const;

    /**
     * 
     * @return true si el bin es Mastercard o false en cualquier otro caso.
     */
    bool isMastercard() const;

    /**
     * 
     * @return true si el bin es American Express o false en cualquier otro caso.
     */
    bool isAmex() const;

    /**
     * 
     * @return true si el bin es Diners o false en cualquier otro caso.
     */
    bool isDiners() const;

    /**
     * 
     * @param porcentaje Porcentaje de comisión
     * @return El monto multiplicado por el porcentaje;
     */
    double GetComision(double porcentaje) const;
private:
    /**
     * Identificador único de la transacción.
     */
    std::string token;

    /**
     * Primeros 6 u 8 dígitos de una tarjeta.
     */
    std::string bin;

    /**
     * Monto de la operación.
     */
    long monto;

    /**
     * Fecha de la operación
     */
    std::tm fecha;
};

#endif /* TRX_H */

