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
  post_code        CHAR(4)       NULL);

CREATE TABLE IF NOT EXISTS INVOICES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_client  INTEGER       NULL,
  inv_type   CHAR(1)       NULL, -- invoice type ( A - B - C ...)
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
  id_client    INTEGER       NULL,
  sta_date     DATE          NULL); -- date when the transport begins his journy

CREATE TABLE IF NOT EXISTS TRAVELS_DESTINATIONS (
  id               INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_travel        INTEGER       NULL,
  id_destination   INTEGER       NULL);

CREATE TABLE IF NOT EXISTS DESTINATIONS (
  id              INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_driver       INTEGER       NULL,
  id_vehicle      INTEGER       NULL,
  arrival_date    DATE          NULL,
  street          CHAR(50)      NULL,
  house_nro       CHAR(4)       NULL,
  post_code       CHAR(4)       NULL);

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
  cellphone             CHAR(20)      NULL, -- | - one of this must be set
  mail                  CHAR(50)      NULL, -- |
  street                CHAR(50)      NULL,
  house_nro             CHAR(4)       NULL,
  post_code             CHAR(4)       NULL,
  blocked               BOOLEAN       NULL DEFAULT FALSE);

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
  max_weight        CHAR(25)      NULL,
  vin               CHAR(25)      NULL, -- vehicule identification number
  vin_cad_date      DATE          NULL, -- vin caducity
  year              CHAR(4)       NULL,
  blocked           BOOLEAN       NULL DEFAULT FALSE);

CREATE TABLE IF NOT EXISTS VEHICLE_TYPES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  name       CHAR(20)      NULL);

CREATE TABLE IF NOT EXISTS DRIVERS_VEHICLES (
  id         INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_driver  INTEGER       NULL,
  id_vehicle INTEGER       NULL);


----------------------------------------------------------------------
--  Inserts
----------------------------------------------------------------------

-- Clients
----------------------------------------------------------------------
INSERT INTO clients ( id_town, name,  phone
                     ,cellphone, mail, street, house_nro , post_code)
VALUES (1, "client_1", "11223344", "11111111111111",
        "client_1@domain.com", "street_1", "0001", "1111");

INSERT INTO clients ( id_town, name,  phone
                     ,cellphone, mail, street, house_nro , post_code)
VALUES (1, "client_2", "22334455", "22222222222222",
        "client_2@gmail.com", "street_2", "0002", "2222");

INSERT INTO clients ( id_town, name,  phone
                     ,cellphone, mail, street, house_nro , post_code)
VALUES (1, "client_3", "33445566", "33333333333333",
        "client_3@gmail.com", "street_3", "0003", "3333");

-- Drivers
----------------------------------------------------------------------
INSERT INTO drivers ( id_town, name,  lic_nro, lic_caducity_date, phone
                     ,cellphone, mail, street, house_nro, post_code)
VALUES (1, "driver_1", "1", "01/01/2021", "11223344", "11111111111111",
        "driver_1@domain.com", "street_1", "0001", "1111");

INSERT INTO drivers ( id_town, name,  lic_nro, lic_caducity_date, phone
                     ,cellphone, mail, street, house_nro, post_code)
VALUES (1, "driver_2", "2", "01/02/2021", "22334455", "22222222222222",
        "driver_2@gmail.com", "street_2", "0002", "2222");

INSERT INTO drivers ( id_town, name,  lic_nro, lic_caducity_date, phone
                     ,cellphone, mail, street, house_nro, post_code)
VALUES (1, "driver_3", "3", "01/03/2021", "33445566", "33333333333333",
        "driver_3@gmail.com", "street_3", "0003", "3333");

-- Brands
----------------------------------------------------------------------
INSERT INTO brands (name) VALUES ("ford");
INSERT INTO brands (name) VALUES ("fiat");
INSERT INTO brands (name) VALUES ("chevrolet");
INSERT INTO brands (name) VALUES ("scania");

-- Models
----------------------------------------------------------------------
INSERT INTO models (id_brand, name) VALUES (1, "focus");
INSERT INTO models (id_brand, name) VALUES (2, "uno");
INSERT INTO models (id_brand, name) VALUES (3, "camaro");
INSERT INTO models (id_brand, name) VALUES (4, "113");

-- Vehicle Types
----------------------------------------------------------------------
INSERT INTO vehicle_types (name) VALUES ("bici");
INSERT INTO vehicle_types (name) VALUES ("moto");
INSERT INTO vehicle_types (name) VALUES ("auto");
INSERT INTO vehicle_types (name) VALUES ("camioneta");
INSERT INTO vehicle_types (name) VALUES ("camion");
INSERT INTO vehicle_types (name) VALUES ("tren");
INSERT INTO vehicle_types (name) VALUES ("barco");
INSERT INTO vehicle_types (name) VALUES ("avion");

-- Vehicles
----------------------------------------------------------------------
INSERT INTO vehicles ( id_type_vehicle, id_model, max_weight, vin, vin_cad_date, year)
VALUES ( 3, 1, 200, 112233, "01/01/2021", "2001");

INSERT INTO vehicles ( id_type_vehicle, id_model, max_weight, vin, vin_cad_date, year)
VALUES ( 4, 2, 300, 223344, "01/02/2021", "2002");

INSERT INTO vehicles ( id_type_vehicle, id_model, max_weight, vin, vin_cad_date, year)
VALUES ( 5, 3, 800, 334455, "01/03/2021", "2003");
