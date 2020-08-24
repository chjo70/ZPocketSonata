ALTER TABLE EW701.THREAT
 DROP PRIMARY KEY CASCADE;

DROP TABLE EW701.THREAT CASCADE CONSTRAINTS;

CREATE TABLE EW701.THREAT
(
  THREAT_INDEX      NUMBER                      NOT NULL,
  PIN               NUMBER                      NOT NULL,
  BE_NUMBER         CHAR(10 BYTE),
  FACILITY_NAME     VARCHAR2(70 BYTE),
  PLACE_NAME_KOR    VARCHAR2(50 BYTE),
  PLACE_NAME_ENG    VARCHAR2(50 BYTE),
  USER_COUNTRY      CHAR(2 BYTE),
  PRIMARY_FUNCTION  CHAR(3 BYTE),
  FRIEND_OR_FOE     VARCHAR2(10 BYTE),
  PRIORITY          NUMBER,
  ADA               CHAR(6 BYTE),
  CATEGORY          NUMBER,
  STATUS            CHAR(1 BYTE),
  DTC               TIMESTAMP(6),
  DTLI              TIMESTAMP(6),
  DTFI              TIMESTAMP(6),
  PLATFORM          NUMBER,
  DISTINCTION       CHAR(10 BYTE),
  SYMBOL_CODE       VARCHAR2(30 BYTE),
  LATITUDE          CHAR(7 BYTE),
  LONGITUDE         CHAR(8 BYTE)
)
TABLESPACE EW701
RESULT_CACHE (MODE DEFAULT)
PCTUSED    0
PCTFREE    10
INITRANS   1
MAXTRANS   255
STORAGE    (
            INITIAL          64K
            NEXT             1M
            MAXSIZE          UNLIMITED
            MINEXTENTS       1
            MAXEXTENTS       UNLIMITED
            PCTINCREASE      0
            BUFFER_POOL      DEFAULT
            FLASH_CACHE      DEFAULT
            CELL_FLASH_CACHE DEFAULT
           )
LOGGING 
NOCOMPRESS 
NOCACHE
NOPARALLEL
MONITORING;


--  There is no statement for index EW701.SYS_C0054465.
--  The object is created when the parent object is created.

--  There is no statement for index EW701.SYS_C0054466.
--  The object is created when the parent object is created.

ALTER TABLE EW701.THREAT ADD (
  PRIMARY KEY
  (THREAT_INDEX)
  USING INDEX
    TABLESPACE EW701
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          64K
                NEXT             1M
                MAXSIZE          UNLIMITED
                MINEXTENTS       1
                MAXEXTENTS       UNLIMITED
                PCTINCREASE      0
                BUFFER_POOL      DEFAULT
                FLASH_CACHE      DEFAULT
                CELL_FLASH_CACHE DEFAULT
               )
  ENABLE VALIDATE,
  UNIQUE (PIN)
  USING INDEX
    TABLESPACE EW701
    PCTFREE    10
    INITRANS   2
    MAXTRANS   255
    STORAGE    (
                INITIAL          64K
                NEXT             1M
                MAXSIZE          UNLIMITED
                MINEXTENTS       1
                MAXEXTENTS       UNLIMITED
                PCTINCREASE      0
                BUFFER_POOL      DEFAULT
                FLASH_CACHE      DEFAULT
                CELL_FLASH_CACHE DEFAULT
               )
  ENABLE VALIDATE);
