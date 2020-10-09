CREATE TABLE IF NOT EXISTS COUNTRIES (
  id     INTEGER               NULL  PRIMARY KEY AUTOINCREMENT,
  name   CHAR(30)              NULL);

CREATE TABLE IF NOT EXISTS STATES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_country INTEGER       NULL,
  name       CHAR(25)      NULL);

CREATE TABLE IF NOT EXISTS TOWNS (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_state   INTEGER       NULL,
  name       CHAR(25)      NULL);

CREATE TABLE IF NOT EXISTS CLIENTS (
  id               INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_town          INTEGER       NULL,
  name             CHAR(25)      NULL,
  phone            CHAR(20)      NULL, -- |
  cellphone        CHAR(20)      NULL, -- | - one of this must be set
  mail             CHAR(50)      NULL, -- |
  street           CHAR(50)      NULL,
  house_nro        CHAR(4)       NULL,
  post_code        CHAR(4)       NULL,
  building_floor   CHAR(4)       NULL,
  apartment_nro    CHAR(4)       NULL);

CREATE TABLE IF NOT EXISTS INVOICES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_client  INTEGER       NULL,
  inv_type   CHAR(1)       NULL,
  inv_date   DATE          NULL,
  balance    REAL          NULL DEFAULT 0.0,
  sub_total  REAL          NULL,
  tax        REAL          NULL,
  total      REAL          NULL);

CREATE TABLE IF NOT EXISTS RECEIPT (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_client  INTEGER       NULL,
  id_invoice INTEGER       NULL,
  rec_date   DATE          NULL,
  total      REAL          NULL);

CREATE TABLE IF NOT EXISTS TRAVELS (
  id           INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_invoice   INTEGER       NULL,
  tra_date     DATE          NULL,
  price        REAL          NULL);

CREATE TABLE IF NOT EXISTS TRAVELS_DESTINATIONS (
  id               INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_travel        INTEGER       NULL,
  id_destination   INTEGER       NULL);

CREATE TABLE IF NOT EXISTS DESTINATIONS (
  id              INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_driver       INTEGER       NULL,
  id_country      INTEGER       NULL,
  id_state        INTEGER       NULL,
  id_town         INTEGER       NULL,
  des_date        DATE          NULL,
  address         CHAR(50)      NULL,
  building_floor  CHAR(4)       NULL,
  apartment_nro   CHAR(4)       NULL,
  latitude        CHAR(12)      NULL,
  des_length      CHAR(12)      NULL);

CREATE TABLE IF NOT EXISTS BURDENS (
  id              INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_burden_type  INTEGER       NULL,
  id_destination  INTEGER       NULL,
  amount          INT(6)        NULL,
  weight_per_unit REAL          NULL,
  width           REAL          NULL,
  bur_length      REAL          NULL,
  height          REAL          NULL);

CREATE TABLE IF NOT EXISTS BURDEN_TYPES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  name       CHAR(20)      NULL);

CREATE TABLE IF NOT EXISTS DRIVERS (
  id                    INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_town               INTEGER       NULL,
  name                  CHAR(15)      NULL,
  lic_nro               CHAR(20)      NULL,
  lic_caducity_date     DATE          NULL,
  phone                 CHAR(20)      NULL, -- |
  cellphone             CHAR(20)      NULL, -- | - on of this must be set
  mail                  CHAR(50)      NULL, -- |
  street                CHAR(50)      NULL,
  house_nro             CHAR(4)       NULL,
  post_code             CHAR(4)       NULL,
  building_floor        CHAR(4)       NULL,
  apartment_nro         CHAR(4)       NULL);

CREATE TABLE IF NOT EXISTS PAYED_COMMISSIONS (
  id           INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_driver    INTEGER       NULL,
  id_invoice   INTEGER       NULL,
  pay_com_date DATE          NULL,
  total        REAL          NULL);

CREATE TABLE IF NOT EXISTS BRANDS (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  name       CHAR(20)      NULL);

CREATE TABLE IF NOT EXISTS MODELS (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_brand   INTEGER       NULL,
  name       CHAR(20)      NULL);

CREATE TABLE IF NOT EXISTS VEHICLES (
  id                INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_type_vehicle   INTEGER       NULL,
  id_model          INTEGER       NULL,
  vin               CHAR(25)      NULL, -- vehicule identification number
  vin_cad_date      DATE          NULL, -- vin caducity
  year              CHAR(4)       NULL);

CREATE TABLE IF NOT EXISTS VEHICLES_TYPES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  name       CHAR(20)      NULL);

CREATE TABLE IF NOT EXISTS DRIVERS_VEHICLES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_driver  INTEGER       NULL,
  id_vehicle INTEGER       NULL);



-- ----------------------------------------------------------------------
--  Inserts
-- ----------------------------------------------------------------------

INSERT INTO clients ( id_town, name,  phone,  cellphone, mail, street, house_nro
                     , post_code, building_floor, apartment_nro)
VALUES (1, "matias", "12345678", "54111512345678", "name@domain.com"
      , "street_1", "0002", "1234", null, null);

INSERT INTO drivers ( id_town, name,  lic_nro, lic_caducity_date, phone,
                      cellphone, mail, street, house_nro, post_code
                     , building_floor, apartment_nro)
VALUES (1, "driver_1", "1", "12/12/2022", "12345678", "54111512345678",
        "name@domain.com", "street_1", "0002", "1234", null ,null);

insert into brands (name) values ("ford");
insert into brands (name) values ("fiat");
insert into brands (name) values ("chevrolet");
insert into brands (name) values ("scania");

insert into models (id_brand, name) values (1, "focus");
insert into models (id_brand, name) values (2, "uno");
insert into models (id_brand, name) values (3, "camaro");
insert into models (id_brand, name) values (4, "113");

insert into VEHICLES_TYPES (name) values ("bici");
insert into VEHICLES_TYPES (name) values ("moto");
insert into VEHICLES_TYPES (name) values ("auto");
insert into VEHICLES_TYPES (name) values ("camioneta");
insert into VEHICLES_TYPES (name) values ("camion");
insert into VEHICLES_TYPES (name) values ("tren");
insert into VEHICLES_TYPES (name) values ("barco");
insert into VEHICLES_TYPES (name) values ("avion");

INSERT INTO vehicles ( id_type_vehicle, id_model, vin, vin_cad_date, year)
VALUES ( 1, 1, 123455, "12/12/2021", "2000");



