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
  id_state         INTEGER       NULL,
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
  sta_date     DATE          NULL,  -- date when the transport begins his journy
  fin_date     DATE          NULL,  -- date where the burden was delivered
  ended        BOOLEAN       NULL DEFAULT FALSE,
  canceled     BOOLEAN       NULL DEFAULT FALSE);

CREATE TABLE IF NOT EXISTS TRAVELS_DESTINATIONS (
  id               INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_travel        INTEGER       NULL,
  id_destination   INTEGER       NULL);

CREATE TABLE IF NOT EXISTS DESTINATIONS (
  id              INTEGER       NULL  PRIMARY KEY AUTOINCREMENT,
  id_driver       INTEGER       NULL,
  id_vehicle      INTEGER       NULL,
  id_state        INTEGER       NULL,
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
  id_state              INTEGER       NULL,
  name                  CHAR(15)      NULL,
  lic_nro               CHAR(20)      NULL,
  lic_caducity_date     DATE          NULL,
  phone                 CHAR(20)      NULL, -- |
  cellphone             CHAR(20)      NULL, -- | - one of this must be set
  mail                  CHAR(50)      NULL, -- |
  street                CHAR(50)      NULL,
  house_nro             CHAR(4)       NULL,
  post_code             CHAR(4)       NULL,
  blocked               BOOLEAN       NULL DEFAULT FALSE,
  nro_travels           INTEGER       NULL DEFAULT 0);

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
  name              CHAR(25)      NULL,
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

-- States
----------------------------------------------------------------------
INSERT INTO states (id, name) VALUES (1,  "buenos_aires");
INSERT INTO states (id, name) VALUES (2,  "catamarca");
INSERT INTO states (id, name) VALUES (3,  "chaco");
INSERT INTO states (id, name) VALUES (4,  "chubut");
INSERT INTO states (id, name) VALUES (5,  "cordoba");
INSERT INTO states (id, name) VALUES (6,  "corrientes");
INSERT INTO states (id, name) VALUES (7,  "entre_ríos");
INSERT INTO states (id, name) VALUES (8,  "formosa");
INSERT INTO states (id, name) VALUES (9,  "jujuy");
INSERT INTO states (id, name) VALUES (10, "la_pampa");
INSERT INTO states (id, name) VALUES (11, "la_rioja");
INSERT INTO states (id, name) VALUES (12, "mendoza");
INSERT INTO states (id, name) VALUES (13, "misiones");
INSERT INTO states (id, name) VALUES (14, "neuquen");
INSERT INTO states (id, name) VALUES (15, "rio_negro");
INSERT INTO states (id, name) VALUES (16, "salta");
INSERT INTO states (id, name) VALUES (17, "san_juan");
INSERT INTO states (id, name) VALUES (18, "san_luis");
INSERT INTO states (id, name) VALUES (19, "santa_cruz");
INSERT INTO states (id, name) VALUES (20, "santa_fe");
INSERT INTO states (id, name) VALUES (21, "santiago_del_estero");
INSERT INTO states (id, name) VALUES (22, "tierra_del_fuego");
INSERT INTO states (id, name) VALUES (23, "tucuman");

-- Clients
----------------------------------------------------------------------
INSERT INTO clients ( id_state, name,  phone
                     ,cellphone, mail, street, house_nro , post_code)
VALUES (1, "client_1", "11223344", "11111111111111",
        "client_1@domain.com", "street_1", "0001", "1111");

INSERT INTO clients ( id_state, name,  phone
                     ,cellphone, mail, street, house_nro , post_code)
VALUES (1, "client_2", "22334455", "22222222222222",
        "client_2@gmail.com", "street_2", "0002", "2222");

INSERT INTO clients ( id_state, name,  phone
                     ,cellphone, mail, street, house_nro , post_code)
VALUES (1, "client_3", "33445566", "33333333333333",
        "client_3@gmail.com", "street_3", "0003", "3333");

-- Drivers
----------------------------------------------------------------------
INSERT INTO drivers ( id_state, name,  lic_nro, lic_caducity_date, phone
                     ,cellphone, mail, street, house_nro, post_code)
VALUES (1, "driver_1", "1"
        , strftime('%Y-%m-%dT12:%M:%f', 'now', 'start of month', '-1 month')
        , "11223344", "11111111111111",
        "driver_1@domain.com", "street_1", "0001", "1111");

INSERT INTO drivers ( id_state, name,  lic_nro, lic_caducity_date, phone
                     ,cellphone, mail, street, house_nro, post_code)
VALUES (1, "driver_2", "2"
        , strftime('%Y-%m-%dT12:%M:%f', 'now', 'start of month')
        , "22334455", "22222222222222",
        "driver_2@gmail.com", "street_2", "0002", "2222");

INSERT INTO drivers ( id_state, name,  lic_nro, lic_caducity_date, phone
                     ,cellphone, mail, street, house_nro, post_code)
VALUES (1, "driver_3", "3"
        , strftime('%Y-%m-%dT12:%M:%f', 'now', 'start of month', '+1 month')
        , "33445566", "33333333333333",
        "driver_3@gmail.com", "street_3", "0003", "3333");

-- Brands
----------------------------------------------------------------------
INSERT INTO brands (name) VALUES ("ford");
INSERT INTO brands (name) VALUES ("fiat");
INSERT INTO brands (name) VALUES ("chevrolet");
INSERT INTO brands (name) VALUES ("renault");

-- Models
----------------------------------------------------------------------
INSERT INTO models (id_brand, name) VALUES (1, "focus");
INSERT INTO models (id_brand, name) VALUES (1, "mondeo");
INSERT INTO models (id_brand, name) VALUES (1, "escort");
INSERT INTO models (id_brand, name) VALUES (1, "mustang");
INSERT INTO models (id_brand, name) VALUES (1, "falcon");
INSERT INTO models (id_brand, name) VALUES (2, "uno");
INSERT INTO models (id_brand, name) VALUES (2, "palio");
INSERT INTO models (id_brand, name) VALUES (2, "ducato");
INSERT INTO models (id_brand, name) VALUES (2, "argo");
INSERT INTO models (id_brand, name) VALUES (2, "doblo");
INSERT INTO models (id_brand, name) VALUES (2, "toro");
INSERT INTO models (id_brand, name) VALUES (3, "camaro");
INSERT INTO models (id_brand, name) VALUES (3, "corsa");
INSERT INTO models (id_brand, name) VALUES (3, "onix");
INSERT INTO models (id_brand, name) VALUES (3, "cruze");
INSERT INTO models (id_brand, name) VALUES (4, "clio");
INSERT INTO models (id_brand, name) VALUES (4, "zandero");
INSERT INTO models (id_brand, name) VALUES (4, "scenic");
INSERT INTO models (id_brand, name) VALUES (4, "laguna");
INSERT INTO models (id_brand, name) VALUES (4, "megane");
INSERT INTO models (id_brand, name) VALUES (4, "logan");

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
INSERT INTO vehicles (
  id_type_vehicle, id_model, name, max_weight, vin, vin_cad_date, year)
VALUES ( 3, 1, "auto_1", 200, 112233
        , strftime('%Y-%m-%dT12:%M:%f', 'now', 'start of month', '+1 month')
        , strftime('%Y-%m-%dT12:%M:%f', 'now', '-5 years'));

INSERT INTO vehicles (
  id_type_vehicle, id_model, name, max_weight, vin, vin_cad_date, year)
VALUES ( 3, 2, "auto_2", 300, 223344
        , strftime('%Y-%m-%dT12:%M:%f', 'now', 'start of month', '+2 month')
        , strftime('%Y-%m-%dT12:%M:%f', 'now', '-10 years'));

INSERT INTO vehicles (
  id_type_vehicle, id_model, name, max_weight, vin, vin_cad_date, year)
VALUES ( 3, 3, "auto_3", 800, 334455
        , strftime('%Y-%m-%dT12:%M:%f', 'now', 'start of month', '+3 month')
        , strftime('%Y-%m-%dT12:%M:%f', 'now', '-15 years'));
