DECLARE
    nCnt NUMBER;
BEGIN

    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'E_AA_GMI_EMITTER';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.E_AA_GMI_EMITTER';
    end if;    
        
END;

CREATE TABLE EW701.E_AA_GMI_EMITTER
(
  SEQ_NUM                   NUMBER              NOT NULL,
  MISSION_ID                VARCHAR2(22 BYTE),
  MISSION_NAME              VARCHAR2(64 BYTE),
  AET_ID                    NUMBER              NOT NULL,
  TASK_TYPE                 NUMBER(1),
  RADARMODE_INDEX           NUMBER              NOT NULL,
  THREAT_INDEX              NUMBER              NOT NULL,
  IDINFO                    VARCHAR2(12 BYTE),
  ELNOT_PRIM                VARCHAR2(12 BYTE),
  MODE_CODE_PRIM            VARCHAR2(12 BYTE),
  NICK_NAME                 VARCHAR2(64 BYTE),
  PRIM_FUNC_CODE            VARCHAR2(12 BYTE),
  RADAR_PRIORITY            NUMBER,
  PIN_NUM                   NUMBER,
  THREAT_NAME               VARCHAR2(64 BYTE),
  BE_NUM                    VARCHAR2(64 BYTE),
  THREAT_FUNC_CODE          VARCHAR2(64 BYTE),
  THREAT_PRIORITY           NUMBER,
  DISTANCE_ERR_FROM_THREAT  NUMBER,
  EQUIP_NUM                 NUMBER,
  NUM_OF_LOBS               NUMBER              NOT NULL,
  NUM_OF_BEAMS              NUMBER              NOT NULL,
  RECORD_TIME_STA           TIMESTAMP(9)        NOT NULL,
  RECORD_TIME_FIN           TIMESTAMP(9)        NOT NULL,
  VALIDITY                  NUMBER(1)           NOT NULL,
  FRQ_MEAN                  NUMBER(8)           NOT NULL,
  FRQ_MAX                   NUMBER(8)           NOT NULL,
  FRQ_MIN                   NUMBER(8)           NOT NULL,
  FRQ_DEV                   NUMBER(8)           NOT NULL,
  PRI_MEAN                  NUMBER              NOT NULL,
  PRI_MAX                   NUMBER              NOT NULL,
  PRI_MIN                   NUMBER              NOT NULL,
  PRI_DEV                   NUMBER              NOT NULL,
  PW_MEAN                   NUMBER              NOT NULL,
  PW_MAX                    NUMBER              NOT NULL,
  PW_MIN                    NUMBER              NOT NULL,
  PW_DEV                    NUMBER              NOT NULL,
  PA_MEAN                   NUMBER              NOT NULL,
  PA_MAX                    NUMBER              NOT NULL,
  PA_MIN                    NUMBER              NOT NULL,
  PA_DEV                    NUMBER              NOT NULL,
  POS_EST_VALID             NUMBER(2)           NOT NULL,
  POS_EST_LAT               NUMBER              NOT NULL,
  POS_EST_LONG              NUMBER              NOT NULL,
  POS_EST_HEIGHT            NUMBER              NOT NULL,
  POS_EST_CEP               NUMBER              NOT NULL,
  POS_EST_MAJOR_AXIS        NUMBER              NOT NULL,
  POS_EST_MINOR_AXIS        NUMBER              NOT NULL,
  EEP_MAJOR_TILT_ANGLE      NUMBER              NOT NULL,
  FIRST_RPT_CRT_TIME        TIMESTAMP(9),
  FINAL_RPT_CRT_TIME        TIMESTAMP(9),
  FINAL_ALARM_TIME          TIMESTAMP(9),
  IS_MANUAL_INPUT           NUMBER(2)           NOT NULL,
  LINK_NUM                  NUMBER              NOT NULL,
  MANUALPOSESTPREFERRED     NUMBER(2)           NOT NULL,
  MANUAL_POS_EST_LAT        NUMBER,
  MANUAL_POS_EST_LONG       NUMBER,
  STAT       NUMBER
)