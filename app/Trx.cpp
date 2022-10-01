#include <iomanip>

#include "Trx.h"
#include "Utem.h"

Trx::Trx() {
    this->token = "";
    this->bin = "";
    this->monto = 0;
    this->fecha = {};
}

Trx::Trx(const Trx& orig) {
    this->token = orig.GetToken();
    this->bin = orig.GetBin();
    this->monto = orig.GetMonto();
    this->fecha = orig.GetFecha();
}

Trx::Trx(std::string linea) {
    std::vector<std::string> datos;
    std::stringstream flujo(linea);
    /** Un string temporal que almacena una parte de la línea. */
    std::string valor;

    // token;bin;monto;fecha
    while (std::getline(flujo, valor, ';')) {
        // Deja en valor el texto encontrado hasta el ;
        // Por ejemplo "token", la siguiente "bin" ...
        datos.push_back(valor);
    }

    this->token = datos.at(0);
    this->bin = datos.at(1);
    this->monto = std::atol(datos.at(2).c_str());

    // Procesamiento de la Fecha (2021-02-11T16:01:58Z)
    std::istringstream ss(datos.at(3));
    ss >> std::get_time(&(this->fecha), "%Y-%m-%dT%H:%M:%SZ");
    if (ss.fail()) {
        std::cerr << "Fallo en el parseo de la fecha (" << datos.at(3) << ")" << std::endl;
    }
}

Trx::~Trx() {
}

std::string Trx::GetBin() const {
    return bin;
}

void Trx::SetBin(std::string bin) {
    this->bin = bin;
}

std::tm Trx::GetFecha() const {
    return fecha;
}

void Trx::SetFecha(std::tm fecha) {
    this->fecha = fecha;
}

void Trx::SetFecha(std::string fecha, std::string formato) {
    std::istringstream ss(fecha);
    ss >> std::get_time(&(this->fecha), formato.c_str());
    if (ss.fail()) {
        std::cerr << "Fallo en el parseo de la fecha (" << fecha << ")" << std::endl;
    }
}

long Trx::GetMonto() const {
    return monto;
}

void Trx::SetMonto(long monto) {
    this->monto = monto;
}

std::string Trx::GetToken() const {
    return token;
}

void Trx::SetToken(std::string token) {
    this->token = token;
}

std::string Trx::GetFechaLocal() const {
    // Reservamos la memoria dinámica para 'dd-mm-YYYY\0'
    char* puntero = new char[11];
    // guardamos el formato en el arreglo
    strftime(puntero, 11, "%d-%m-%Y", &(fecha));

    // Asignar este dato a un string
    std::string resultado(puntero);

    // liberar la memoria
    delete [] puntero;

    // Retornamos resultado.
    return resultado;
}

std::string Trx::GetFechaJson() const {
    // Reservamos la memoria dinámica para 'YYYY-mm-ddTHH:MM:SSZ\0'
    char* puntero = new char[21];
    // guardamos el formato en el arreglo
    strftime(puntero, 21, "%Y-%m-%dT%H:%M:%SZ", &(fecha));

    // Asignar este dato a un string
    std::string resultado(puntero);

    // liberar la memoria
    delete [] puntero;

    // Retornamos resultado.
    return resultado;
}

bool Trx::isVisa() const {
    return Utem::comienzaCon(bin, "4");
}

bool Trx::isMastercard() const {
    return (Utem::comienzaCon(bin, "2") || Utem::comienzaCon(bin, "5"));
}

bool Trx::isAmex() const {
    return (Utem::comienzaCon(bin, "34") || Utem::comienzaCon(bin, "37"));
}

bool Trx::isDiners() const {
    bool diners = false;

    if (Utem::comienzaCon(bin, "30")) {
        diners = true;
    }

    if (Utem::comienzaCon(bin, "36")) {
        diners = true;
    }

    if (Utem::comienzaCon(bin, "38")) {
        diners = true;
    }

    if (Utem::comienzaCon(bin, "39")) {
        diners = true;
    }

    if (Utem::comienzaCon(bin, "60")) {
        diners = true;
    }

    return diners;
}

double Trx::GetComision(double porcentaje) const {
    return monto * porcentaje;
}