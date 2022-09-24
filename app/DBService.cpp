#include "DBService.h"

DBService::DBService() {
    reconectar();
}

DBService::~DBService() {
    try {
        conexion->disconnect();
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
}

bool DBService::reconectar() {
    bool isOk = false;
    try {
        if (conexion && conexion->is_open()) {
            isOk = true;
        } else {
            std::string db;
            const char *pgdb = std::getenv("PGDATABASE");
            if (pgdb == NULL) {
                db = "cpyddb";
            } else {
                db = pgdb;
            }

            std::string host;
            const char *pghost = std::getenv("PGHOST");
            if (pghost == NULL) {
                host = "192.168.67.17";
            } else {
                host = pghost;
            }

            std::string port;
            const char *pgport = std::getenv("PGPORT");
            if (pgport == NULL) {
                port = "5432";
            } else {
                port = pgport;
            }

            std::string user;
            const char *pguser = std::getenv("PGUSER");
            if (pguser == NULL) {
                user = "cpyd";
            } else {
                user = pguser;
            }

            std::string pwd;
            const char *pgpwd = std::getenv("PGPASSWORD");
            if (pgpwd == NULL) {
                pwd = "cpyd";
            } else {
                pwd = pgpwd;
            }

            const std::string url = "host='" + host + "' port='" + port + "' dbname='" + db + "' user='" + user + "' password='" + pwd + "'";
            this->conexion = new pqxx::connection(url);
            isOk = conexion->is_open();
            if (!isOk) {
                std::cerr << "No fue posible conectarse a la URL " << url << std::endl;
            }
        }
    } catch (std::exception const &e) {
        isOk = false;
        std::cerr << e.what() << std::endl;
    }
    return isOk;
}

Trx DBService::GetTrx(std::string token) {
    Trx trx;
    try {
        if (token.empty() && reconectar()) {
            pqxx::nontransaction sql(*(this->conexion));

            std::string consulta = "SELECT bin, monto, fecha FROM trxs WHERE token='" + sql.esc(token.c_str()) + "'";
            pqxx::result resultado = sql.exec(consulta);
            const pqxx::row fila = resultado.at(0);

            std::string bin = fila.at("bin").as<std::string>();
            long monto = fila.at("monto").as<long>();
            std::string fecha = fila.at("fecha").as<std::string>();

            trx.SetToken(token);
            trx.SetBin(bin);
            trx.SetMonto(monto);
            trx.SetFecha(fecha, "%Y-%m-%dT%H:%M:%SZ");
        }
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
    return trx;
}

bool DBService::GuardarTrx(Trx trx) {
    bool guardado = false;
    try {
        if (reconectar()) {
            Trx original = GetTrx(trx.GetToken());
            if (original.GetToken().empty()) {
                // No lo encontramos
                pqxx::work tx(*(this->conexion));
                std::string insert = "INSERT INTO trxs (token, bin, monto, fecha) VALUES ('" + trx.GetToken() + "','" + trx.GetBin() + "','" + std::to_string(trx.GetMonto()) + "','" + trx.GetFechaJson() + "')";
                tx.exec(insert);
                tx.commit();

                guardado = true;
            } else {
                // Si lo encontramos.
                guardado = true;
            }
        }
    } catch (std::exception const &e) {
        guardado = false;
        std::cerr << e.what() << std::endl;
    }
    return guardado;
}