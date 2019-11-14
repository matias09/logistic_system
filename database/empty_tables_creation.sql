CREATE TABLE COUNTRIES (
  id     INTEGER               NULL  PRIMARY KEY AUTOINCREMENT,
  name   CHAR(30)          NOT NULL);

  CREATE TABLE STATES (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_country INTEGER   NOT NULL,
    name       CHAR(25)          NOT NULL);

  CREATE TABLE TOWNS (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_state   INTEGER   NOT NULL,
    name       CHAR(25)          NOT NULL);

  CREATE TABLE CLIENTS (
    id               INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_town          INTEGER   NOT NULL,
    name             CHAR(25)          NOT NULL,
    phone            CHAR(20)              NULL, -- |
    cellphone        CHAR(20)              NULL, -- | - on of this must be set
    mail             CHAR(50)              NULL, -- |
    address          CHAR(50)          NOT NULL,
    building_floor   CHAR(4)               NULL,
    apartment_nro    CHAR(4)               NULL);

  CREATE TABLE INVOICES (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_client  INTEGER   NOT NULL,
    inv_type   CHAR(1)           NOT NULL,
    inv_date   DATE              NOT NULL,
    balance    REAL                  NULL DEFAULT 0.0,
    sub_total  REAL              NOT NULL,
    tax        REAL              NOT NULL,
    total      REAL              NOT NULL);

  CREATE TABLE RECEIPT (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_client  INTEGER   NOT NULL,
    id_invoice INTEGER   NOT NULL,
    rec_date   DATE              NOT NULL,
    total      REAL              NOT NULL);

  CREATE TABLE TRAVELS (
    id           INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_invoice   INTEGER   NOT NULL,
    tra_date     DATE              NOT NULL,
    price        REAL              NOT NULL);

  CREATE TABLE TRAVELS_DESTINATIONS (
    id               INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_travel        INTEGER   NOT NULL,
    id_destination   INTEGER   NOT NULL);

  CREATE TABLE DESTINATIONS (
    id              INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_driver       INTEGER   NOT NULL,
    id_country      INTEGER   NOT NULL,
    id_state        INTEGER   NOT NULL,
    id_town         INTEGER   NOT NULL,
    des_date        DATE              NOT NULL,
    address         CHAR(50)          NOT NULL,
    building_floor  CHAR(4)               NULL,
    apartment_nro   CHAR(4)               NULL,
    latitude        CHAR(12)              NULL,
    des_length      CHAR(12)              NULL);

  CREATE TABLE BURDENS (
    id              INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_burden_type  INTEGER   NOT NULL,
    id_destination  INTEGER   NOT NULL,
    amount          INT(6)    NOT NULL,
    weight_per_unit REAL              NOT NULL,
    width           REAL              NOT NULL,
    bur_length      REAL              NOT NULL,
    height          REAL              NOT NULL);

  CREATE TABLE BURDEN_TYPES (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    name       CHAR(20)          NOT NULL);

  CREATE TABLE DRIVERS (
    id                    INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_country            INTEGER   NOT NULL,
    id_town               INTEGER   NOT NULL,
    name                  CHAR(15)          NOT NULL,
    lic_nro               CHAR(20)          NOT NULL,
    lic_caducity_date     DATE              NOT NULL,
    phone                 CHAR(20)              NULL, -- |
    cellphone             CHAR(20)              NULL, -- | - on of this must be set
    mail                  CHAR(50)              NULL, -- |
    address               CHAR(50)          NOT NULL,
    building_floor        CHAR(4)               NULL,
    apartment_nro         CHAR(4)               NULL);

  CREATE TABLE PAYED_COMMISSIONS (
    id           INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_driver    INTEGER   NOT NULL,
    id_invoice   INTEGER   NOT NULL,
    pay_com_date DATE              NOT NULL,
    total        REAL              NOT NULL);

  CREATE TABLE BRANDS (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    name       CHAR(20)          NOT NULL);

  CREATE TABLE MODELS (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_brand   INTEGER   NOT NULL,
    name       CHAR(20)          NOT NULL);

  CREATE TABLE VEHICLES (
    id                INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_type_vehicle   INTEGER   NOT NULL,
    id_model          INTEGER   NOT NULL,
    vin               CHAR(25)          NOT NULL, -- vehicule identification number
    vin_cad_date      DATE                  NULL, -- vin caducity
    year              CHAR(4)               NULL);

  CREATE TABLE DRIVERS_VEHICLES (
    id         INTEGER   NOT NULL  PRIMARY KEY AUTOINCREMENT,
    id_driver  INTEGER   NOT NULL,
    id_vehicle INTEGER   NOT NULL);
