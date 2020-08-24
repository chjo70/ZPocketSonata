DECLARE
    nCnt NUMBER;
BEGIN

    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'E_AA_GMI_BEAM';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.E_AA_GMI_BEAM';
    end if;         
    
        
END;


CREATE TABLE EW701.E_AA_GMI_BEAM
(
  SEQ_NUM                 NUMBER                    NOT NULL,
  MISSION_ID              VARCHAR2(22 BYTE),
  MISSION_NAME            VARCHAR2(64 BYTE),
  
  ABT_ID                  NUMBER                    NOT NULL,
  AET_ID                  NUMBER                    NOT NULL,

  RADARMODE_INDEX         NUMBER                    NOT NULL,  
  THREAT_INDEX            NUMBER                    NOT NULL,  
  
  ELNOT_PRIM              VARCHAR2(12 BYTE),
  MODE_CODE_PRIM          VARCHAR2(12 BYTE),
  MODULATION_CODE         VARCHAR2(12 BYTE),
  NICK_NAME               VARCHAR2(64 BYTE),
  PRIM_FUNC_CODE          VARCHAR2(12 BYTE),
  
  PLATFORM_TYPE           VARCHAR2(25 BYTE),
  RADAR_MODE_PRIORITY     NUMBER(5),
  RADAR_PRIORITY          NUMBER(5),
  
  SIG_TYPE                NUMBER(1)                 NOT NULL,
  
  POLIZATION           		NUMBER(1)                 NOT NULL,
  TASK_TYPE               NUMBER(1),
  
  NUM_OF_PULSE_GRP        NUMBER                    NOT NULL,
  NUM_OF_LOBS             NUMBER                    NOT NULL,
  RECORD_TIME_STA         TIMESTAMP(9)             NOT NULL,
  RECORD_TIME_FIN         TIMESTAMP(9)             NOT NULL,  
  VALIDITY                NUMBER(1)                 NOT NULL,
  
  FRQ_TYPE                NUMBER(1)                 NOT NULL,
  FRQ_PATTN_TYPE          NUMBER(1)                 NOT NULL,
  HAS_FRQ_MOD_PRD         NUMBER(1)                 NOT NULL,
  FRQ_MOD_PRD_MEAN        NUMBER                    NOT NULL,
  FRQ_MOD_PRD_MAX         NUMBER                    NOT NULL,
  FRQ_MOD_PRD_MIN         NUMBER                    NOT NULL,
  NUM_OF_FRQ_POSITION     NUMBER(3)                 NOT NULL,
  NUM_OF_FRQ_ELEMENT      NUMBER(3)                 NOT NULL,
  FRQ_MEAN                NUMBER                    NOT NULL,
  FRQ_MAX                 NUMBER                    NOT NULL,
  FRQ_MIN                 NUMBER                    NOT NULL,
  FRQ_DEV                 NUMBER                    NOT NULL,
  
  PRI_TYPE                NUMBER(1)                 NOT NULL,
  PRI_PATTN_TYPE          NUMBER(1)                 NOT NULL,
  HAS_PRI_MOD_PRD         NUMBER(1)                 NOT NULL,
  PRI_MOD_PRD_MEAN        NUMBER(6)                 NOT NULL,
  PRI_MOD_PRD_MAX         NUMBER(6)                 NOT NULL,
  PRI_MOD_PRD_MIN         NUMBER(6)                 NOT NULL,
  NUM_OF_PRI_POSITION     NUMBER(3)                 NOT NULL,
  NUM_OF_PRI_ELEMENT      NUMBER(3)                 NOT NULL,
  PRI_MEAN                NUMBER                    NOT NULL,
  PRI_MAX                 NUMBER                    NOT NULL,
  PRI_MIN                 NUMBER                    NOT NULL,
  PRI_DEV                 NUMBER                    NOT NULL,
  PRI_JITTER_RTO          NUMBER(4)                 NOT NULL,
  
  PW_MEAN                 NUMBER                    NOT NULL,
  PW_MAX                  NUMBER                    NOT NULL,
  PW_MIN                  NUMBER                    NOT NULL,
  PW_DEV                  NUMBER                    NOT NULL,
  
  PA_MEAN                 NUMBER                    NOT NULL,
  PA_MAX                  NUMBER                    NOT NULL,
  PA_MIN                  NUMBER                    NOT NULL,
  PA_DEV                  NUMBER                    NOT NULL,
  
  SCAN_TYPE               NUMBER(1)                 NOT NULL,
  SCAN_PRD_MAX_SEC        NUMBER                    NOT NULL,  
  SCAN_PRD_MIN_SEC        NUMBER                    NOT NULL,
  
  HAS_INTRA_MOD           NUMBER(1)                 NOT NULL,
  INTRA_FRQ_CHNG_WID_MAX  NUMBER                    NOT NULL,
  INTRA_FRQ_CHNG_WID_MIN  NUMBER                    NOT NULL,  
  
  POS_EST_VALID           NUMBER(2)                 NOT NULL,
  POS_EST_LAT             NUMBER,
  POS_EST_LONG            NUMBER,
  POS_EST_HEIGHT          NUMBER,
  POS_EST_CEP             NUMBER,
  POS_EST_MAJOR_AXIS      NUMBER,
  POS_EST_MINOR_AXIS      NUMBER,
  EEP_MAJOR_TILT_ANGLE    NUMBER,
  
  FIRST_RPT_CRT_TIME      TIMESTAMP(9),
  FINAL_RPT_CRT_TIME      TIMESTAMP(9),
  FINAL_ALARM_TIME        TIMESTAMP(9),  
  
  IS_MANUAL_INPUT         NUMBER(1)                 NOT NULL,

  LINK_NUM                NUMBER                    NOT NULL,
  
  MANUALPOSESTPREFERRED   NUMBER(2)                 NOT NULL,
  
  MANUAL_POS_EST_LAT      NUMBER,
  MANUAL_POS_EST_LONG     NUMBER,

  DISTANCE_ERR_FROM_THREAT NUMBER,

  STAT                    NUMBER                    NOT NULL,
  KOREASITE_NAME            VARCHAR2(64 BYTE)

);

