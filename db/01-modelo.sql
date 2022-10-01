BEGIN TRANSACTION;

DROP TABLE IF EXISTS trxs CASCADE;
CREATE TABLE trxs (
    pk bigserial NOT NULL,
    token varchar(255) NOT NULL,
    bin varchar(255) NOT NULL,
    monto bigint NOT NULL,
    fecha timestamptz NOT NULL,
    UNIQUE (token),
    PRIMARY KEY (pk)
);

COMMIT;