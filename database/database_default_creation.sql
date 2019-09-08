
CREATE TABLE COUNTRIES (
  id     INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  name   CHAR(30)          NOT NULL);

CREATE TABLE STATES (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_country INT(11)  UNSIGNED NOT NULL,
  name       CHAR(25)          NOT NULL);

CREATE TABLE TOWNS (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_state   INT(11)  UNSIGNED NOT NULL,
  name       CHAR(25)          NOT NULL);

CREATE TABLE CLIENTS (
  id               INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_town          INT(11)  UNSIGNED NOT NULL,
  name             CHAR(25)          NOT NULL,
  phone            CHAR(20)              NULL, -- |
  cellphone        CHAR(20)              NULL, -- | - on of this must be set
  mail             CHAR(50)              NULL, -- |
  address          CHAR(50)          NOT NULL,
  building_floor   CHAR(4)               NULL,
  apartment_nro    CHAR(4)               NULL);

CREATE TABLE INVOICES (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_client  INT(11)  UNSIGNED NOT NULL,
  inv_type   CHAR(1)           NOT NULL,
  inv_date   DATE              NOT NULL,
  balance    REAL                  NULL DEFAULT 0.0,
  sub_total  REAL              NOT NULL,
  tax        REAL              NOT NULL,
  total      REAL              NOT NULL);

CREATE TABLE RECEIPT (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_client  INT(11)  UNSIGNED NOT NULL,
  id_invoice INT(11)  UNSIGNED NOT NULL,
  rec_date   DATE              NOT NULL,
  total      REAL              NOT NULL);

CREATE TABLE TRAVELS (
  id           INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_invoice   INT(11)  UNSIGNED NOT NULL,
  tra_date     DATE              NOT NULL,
  price        REAL              NOT NULL);

CREATE TABLE TRAVELS_DESTINATIONS (
  id               INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_travel        INT(11)  UNSIGNED NOT NULL,
  id_destination   INT(11)  UNSIGNED NOT NULL);

CREATE TABLE DESTINATIONS (
  id              INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_driver       INT(11)  UNSIGNED NOT NULL,
  id_country      INT(11)  UNSIGNED NOT NULL,
  id_state        INT(11)  UNSIGNED NOT NULL,
  id_town         INT(11)  UNSIGNED NOT NULL,
  des_date        DATE              NOT NULL,
  address         CHAR(50)          NOT NULL,
  building_floor  CHAR(4)               NULL,
  apartment_nro   CHAR(4)               NULL,
  latitude        CHAR(12)              NULL,
  des_length      CHAR(12)              NULL);

CREATE TABLE BURDENS (
  id              INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_burden_type  INT(11)  UNSIGNED NOT NULL,
  id_destination  INT(11)  UNSIGNED NOT NULL,
  amount          INT(6)   UNSIGNED NOT NULL,
  weight_per_unit REAL              NOT NULL,
  width           REAL              NOT NULL,
  bur_length      REAL              NOT NULL,
  height          REAL              NOT NULL);

CREATE TABLE BURDEN_TYPES (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  name       CHAR(20)          NOT NULL);

CREATE TABLE DRIVERS (
  id                    INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_country            INT(11)  UNSIGNED NOT NULL,
  id_town               INT(11)  UNSIGNED NOT NULL,
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
  id           INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_driver    INT(11)  UNSIGNED NOT NULL,
  id_invoice   INT(11)  UNSIGNED NOT NULL,
  pay_com_date DATE              NOT NULL,
  total        REAL              NOT NULL);

CREATE TABLE BRANDS (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  name       CHAR(20)          NOT NULL);

CREATE TABLE MODELS (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_brand   INT(11)  UNSIGNED NOT NULL,
  name       CHAR(20)          NOT NULL);

CREATE TABLE VEHICLES (
  id                INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_type_vehicle   INT(11)  UNSIGNED NOT NULL,
  id_model          INT(11)  UNSIGNED NOT NULL,
  vin               CHAR(25)          NOT NULL, -- vehicule identification number
  vin_cad_date      DATE                  NULL, -- vin caducity
  year              CHAR(4)               NULL);

CREATE TABLE DRIVERS_VEHICLES (
  id         INT(11)  UNSIGNED NOT NULL AUTO_INCREMENT  PRIMARY KEY,
  id_driver  INT(11)  UNSIGNED NOT NULL,
  id_vehicle INT(11)  UNSIGNED NOT NULL);




