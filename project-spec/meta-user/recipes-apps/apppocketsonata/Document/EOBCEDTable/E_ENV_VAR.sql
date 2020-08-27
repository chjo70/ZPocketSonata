DECLARE
    nCnt NUMBER;
BEGIN

    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'E_ENV_VAR';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.E_ENV_VAR';
    end if;         
    
        
END;


CREATE TABLE EW701.E_ENV_VAR
(
  SEQ_ID                          NUMBER(22)    NOT NULL,
  OPER_ID                         VARCHAR2(20 BYTE),
  RESTORE_TIME                    TIMESTAMP(9),
  VAR_CW_DEC_PW                   NUMBER(6),
  VAR_CW_CHOP_COUNT               NUMBER(6),
  VAR_CW_CHOP_SPAN                NUMBER(6),
  VAR_NRT_THRESHOLD               NUMBER(3),
  MTSK_WB_SP_UNIT_COLL_TIME       NUMBER(6),
  MTSK_WB_SP_UNIT_COLL_NUM        NUMBER(6),
  MTSK_SPIN_DF_UNIT_COLL_TIME     NUMBER(6),
  MTSK_SPIN_DF_UNIT_COLL_NUM      NUMBER(6),
  EMMG_NUM_OF_MIN_PULSE_TO_LOB    NUMBER(6),
  EMMG_NUM_OF_MIN_LOB_TO_BEAM     NUMBER(6),
  EMMG_EMITTER_DEL_TIME           NUMBER(6),
  RPT_TACREP_RECEIVER             VARCHAR2(22 BYTE),
  RPT_TACREP_DEFAULT_ADDRESSEE    VARCHAR2(22 BYTE),
  RTP_TACREP_SENDER               VARCHAR2(22 BYTE),
  RPT_TACREP_SOURCE               VARCHAR2(22 BYTE),
  RPT_TACREP_CONTROL_SIGN         VARCHAR2(22 BYTE),
  RPT_TACREP_SEND_PRIORITY        VARCHAR2(22 BYTE),
  RPT_TACREP_RELAY                VARCHAR2(22 BYTE),
  RPT_TACREP_END_OF_HEADER        VARCHAR2(60 BYTE),
  MISC_POD_TEMP_PERIOD_SEC        NUMBER(6),
  MISC_HG_ANT_INFO_PERIOD_SEC     NUMBER(6),
  MISC_LATLONG_DISPLAY            NUMBER(1),
  MISC_DISTANCE_UNIT              NUMBER(1),
  MAP_DISPLAY_PINNUM              NUMBER(1),
  MAP_RGB_DT_ANT_RANGE            NUMBER(30),
  MAP_RGB_AET_KNOWN               NUMBER(30),
  MAP_RGB_AET_UNKNOWN             NUMBER(30),
  MAP_RGB_AET_VALID_DATA          NUMBER(30),
  MAP_RGB_AET_VALID_POSEST        NUMBER(30),
  MAP_RGB_AET_INVALID_POSEST      NUMBER(30),
  MAP_RGB_ABT_VALID_POSEST        NUMBER(30),
  MAP_RGB_ABT_INVLAID_POSEST      NUMBER(30),
  MAP_RGB_DT_LOB_VALID            NUMBER(30),
  MAP_RGB_DT_LOB_INVALID          NUMBER(30),
  MAP_RGB_HG_LOB                  NUMBER(30),
  MAP_RGB_OTHERSITE_LOB           NUMBER(30),
  MAP_RGB_THREAT_SYMBOL           NUMBER(30),
  MAP_RGB_DT_ANT_RANGE_FIG        NUMBER(1),
  MAP_RGB_AET_KNOWN_FIG           NUMBER(1),
  MAP_RGB_AET_UNKNOWN_FIG         NUMBER(1),
  MAP_RGB_AET_VALID_DATA_FIG      NUMBER(1),
  MAP_RGB_AET_VALID_POSEST_FIG    NUMBER(1),
  MAP_RGB_AET_INVALID_POSEST_FIG  NUMBER(1),
  MAP_RGB_ABT_VALID_POSEST_FIG    NUMBER(1),
  MAP_RGB_ABT_INVLAID_POSEST_FIG  NUMBER(1),
  MAP_RGB_DT_LOB_VALID_FIG        NUMBER(1),
  MAP_RGB_DT_LOB_INVALID_FIG      NUMBER(1),
  MAP_RGB_HG_LOB_FIG              NUMBER(1),
  MAP_RGB_OTHERSITE_LOB_FIG       NUMBER(1),
  MAP_RGB_THREAT_SYMBOL_FIG       NUMBER(1),
  RPT_TACELINT_DISTRIBUTOR        VARCHAR2(22 BYTE),
  RPT_TACELINT_COLLECTOR          VARCHAR2(22 BYTE),
  RPT_UNIFORMC_SECRET_LEVEL       VARCHAR2(10 BYTE),
  RPT_UNIFORMC_SIG_CAT            VARCHAR2(10 BYTE),
  RPT_UNIFORMC_SENSOR             VARCHAR2(10 BYTE),
  RPT_UNIFORMC_COLLECT_SOURCE     VARCHAR2(10 BYTE),
  RPT_UNIFORMC_PLATFORM           VARCHAR2(10 BYTE),
  MIL_SYMBOL_BITMAP_SIZE          NUMBER
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