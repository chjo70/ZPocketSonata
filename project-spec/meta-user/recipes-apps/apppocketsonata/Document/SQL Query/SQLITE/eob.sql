# 2020-08-26 오후 3:22:26

# EOB 관련 테이블을 삭제합니다.
drop table if exists "THREAT";
drop table if exists "THREAT_P";
drop table if exists "DEVICE";
drop table if exists "DEVICE_P";

# EOB 관련 테이블을 생성합니다.
CREATE TABLE THREAT
(
  THREAT_INDEX      NUMBER                      NOT NULL,
  PIN               NUMBER UNIQUE               NOT NULL,
  BE_NUMBER         CHAR(10 ),
  FACILITY_NAME     VARCHAR2(50 ),
  PLACE_NAME_KOR    VARCHAR2(50 ),
  PLACE_NAME_ENG    VARCHAR2(50 ),
  USER_COUNTRY      CHAR(2 ),
  PRIMARY_FUNCTION  CHAR(2 ),
  FRIEND_OR_FOE     VARCHAR2(10 ),
  PRIORITY          NUMBER,
  ADA               CHAR(6 ),
  CATEGORY          NUMBER,
  STATUS            CHAR(1 ),
  DTC               TIMESTAMP(6),
  DTLI              TIMESTAMP(6),
  DTFI              TIMESTAMP(6),
  PLATFORM          NUMBER,
  DISTINCTION       VARCHAR2(10 ),
  SYMBOL_CODE       VARCHAR2(30 ),
  LATITUDE          CHAR(7 ),
  LONGITUDE         CHAR(8 ),
  PRIMARY KEY (THREAT_INDEX)
);
CREATE TABLE THREAT_P
(
  THREAT_INDEX      NUMBER                      NOT NULL,
  PIN               NUMBER UNIQUE               NOT NULL,
  BE_NUMBER         CHAR(10 ),
  FACILITY_NAME     VARCHAR2(50 ),
  PLACE_NAME_KOR    VARCHAR2(50 ),
  PLACE_NAME_ENG    VARCHAR2(50 ),
  USER_COUNTRY      CHAR(2 ),
  PRIMARY_FUNCTION  CHAR(2 ),
  FRIEND_OR_FOE     VARCHAR2(10 ),
  PRIORITY          NUMBER,
  ADA               CHAR(6 ),
  CATEGORY          NUMBER,
  STATUS            CHAR(1 ),
  DTC               TIMESTAMP(6),
  DTLI              TIMESTAMP(6),
  DTFI              TIMESTAMP(6),
  PLATFORM          NUMBER,
  DISTINCTION       VARCHAR2(10 ),
  SYMBOL_CODE       VARCHAR2(30 ),
  LATITUDE          CHAR(7 ),
  LONGITUDE         CHAR(8 ),
  PRIMARY KEY (THREAT_INDEX)
);
CREATE TABLE DEVICE
(
  THREAT_INDEX          NUMBER                      NOT NULL,
  DEVICE_INDEX          NUMBER                      NOT NULL,
  ELNOT                 VARCHAR2(15 ),
  DEVICE_NAME           VARCHAR2(50 ),
  STATUS                CHAR(1 ),
  IDENTIFICATION_RANGE  NUMBER,
  LATITUDE              VARCHAR2(13 ),
  LONGITUDE             VARCHAR2(14 ),
  ELEVATION             NUMBER,

  LATITUDE_NUM          NUMBER,
  LONGITUDE_NUM         NUMBER,
  PRIMARY KEY (THREAT_INDEX, DEVICE_INDEX)
);
CREATE TABLE DEVICE_P
(
  THREAT_INDEX          NUMBER                      NOT NULL,
  DEVICE_INDEX          NUMBER                      NOT NULL,
  ELNOT                 CHAR(5 ),
  DEVICE_NAME           VARCHAR2(50 ),
  STATUS                CHAR(1 ),
  IDENTIFICATION_RANGE  NUMBER,
  LATITUDE              VARCHAR2(13 ),
  LONGITUDE             VARCHAR2(14 ),
  ELEVATION             NUMBER,

  LATITUDE_NUM          NUMBER,
  LONGITUDE_NUM         NUMBER,
  PRIMARY KEY (THREAT_INDEX, DEVICE_INDEX)
);
