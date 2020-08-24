DECLARE
    nCnt NUMBER;
BEGIN

    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'E_AA_MSG_LOB';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.E_AA_MSG_LOB';
    end if;
   

       
END;


CREATE TABLE EW701.E_AA_MSG_LOB
(
  SEQ_NUM              NUMBER                   NOT NULL,
  
  HOUR                 NUMBER(3)                NOT NULL,
  MIN                  NUMBER(3)                NOT NULL,
  SEC                  NUMBER(3)                NOT NULL,
  
  ACQ_TIME             TIMESTAMP(9)             NOT NULL,
  LINK_NUM             NUMBER                   NOT NULL,
  MISSION_ID           VARCHAR2(22 BYTE),
  MISSION_NAME         VARCHAR2(64 BYTE),
  TASK_ID              VARCHAR2(22 BYTE),
  TASK_NAME            VARCHAR2(64 BYTE),
  TASK_TYPE            NUMBER(1),
  SEARCH_BAND_ID       NUMBER                   NOT NULL,
  RXPATH               NUMBER(3)                NOT NULL,
  ANTDIRECTION         NUMBER(3)                NOT NULL,
  LOB_ID               NUMBER                   NOT NULL,
  ABT_ID               NUMBER                   NOT NULL,
  AET_ID               NUMBER                   NOT NULL,
  ELNOT_PRIM           VARCHAR2(12 BYTE),
  MODE_CODE_PRIM       VARCHAR2(12 BYTE),
  ELNOT_SECON          VARCHAR2(12 BYTE),
  MODE_CODE_SECON      VARCHAR2(12 BYTE),
  ELNOT_TERT           VARCHAR2(12 BYTE),
  MODE_CODE_TERT       VARCHAR2(12 BYTE),
  MODULATION_CODE      VARCHAR2(12 BYTE),
  NICK_NAME            VARCHAR2(64 BYTE),
  PRIM_FUNC_CODE       VARCHAR2(12 BYTE),
  SIG_TYPE             NUMBER(3)                NOT NULL,
  
  POLIZATION           NUMBER(1)                NOT NULL,
  RATIOOFPOL           NUMBER(4)                NOT NULL,
  FISINTTASK           NUMBER(1)                NOT NULL,
  
  NUM_OF_PULSE_GRP     NUMBER(6)                NOT NULL,
  NUM_OF_PULSES        NUMBER(6)                NOT NULL,
  BL_STAT              NUMBER(1)                NOT NULL,
  FOV                  NUMBER(5)                NOT NULL,
  
  DOA_MEAN             NUMBER                   NOT NULL,
  DOA_MIN              NUMBER                   NOT NULL,
  DOA_MAX              NUMBER                   NOT NULL,
  DOA_DEV              NUMBER                   NOT NULL,
  DOA_STD              NUMBER                   NOT NULL,
  DI_RATIO             NUMBER                   NOT NULL,
  
  FRQ_TYPE             NUMBER(1)                NOT NULL,
  FRQ_PATTN_TYPE       NUMBER(1)                NOT NULL,
  HAS_FRQ_MOD_PRD      NUMBER                   NOT NULL,
  FRQ_CHNG_PRD         NUMBER                   NOT NULL,
  NUM_OF_FRQ_POSITION  NUMBER(3)                NOT NULL,
  NUM_OF_FRQ_ELEMENT   NUMBER(3)                NOT NULL,
  FRQ_MEAN             NUMBER                   NOT NULL,
  FRQ_MAX              NUMBER                   NOT NULL,
  FRQ_MIN              NUMBER                   NOT NULL,
  FRQ_DEV              NUMBER                   NOT NULL,
  PRI_TYPE             NUMBER(1)                NOT NULL,
  PRI_PATTN_TYPE       NUMBER(1)                NOT NULL,
  HAS_PRI_MOD_PRD      NUMBER(1)                NOT NULL,
  PRI_MOD_PRD          NUMBER                   NOT NULL,
  NUM_OF_PRI_POSITION  NUMBER(3)                NOT NULL,
  NUM_OF_PRI_ELEMENT   NUMBER(3)                NOT NULL,
  
  PRI_MEAN             NUMBER                   NOT NULL,
  PRI_MAX              NUMBER                   NOT NULL,
  PRI_MIN              NUMBER                   NOT NULL,
  PRI_DEV              NUMBER                   NOT NULL,
  PRI_JITTER_RTO       NUMBER                   NOT NULL,
  
  PW_MEAN              NUMBER                   NOT NULL,
  PW_MIN               NUMBER                   NOT NULL,
  PW_MAX               NUMBER                   NOT NULL,
  PW_DEV               NUMBER                   NOT NULL,
  PA_MEAN              NUMBER                   NOT NULL,
  PA_MIN               NUMBER                   NOT NULL,
  PA_MAX               NUMBER                   NOT NULL,
  PA_DEV               NUMBER                   NOT NULL,
  SCAN_TYPE            NUMBER(1)                NOT NULL,
  SCAN_TYPE_DETAIL     NUMBER(1)                NOT NULL,
  SCAN_PRD             NUMBER                   NOT NULL,
  INTRA_TYPE           NUMBER(2)                NOT NULL,
  INTRA_TYPE_DETAIL    NUMBER(2)                NOT NULL,
  INTRA_FRQ_MEAN       NUMBER                   NOT NULL,
  INTRA_FRQ_MIN        NUMBER                   NOT NULL,
  INTRA_FRQ_MAX        NUMBER                   NOT NULL,
  INTRA_FRQ_DEVIATION  NUMBER                   NOT NULL,
  AIRCRAFT_LAT         NUMBER                   NOT NULL,
  AIRCRAFT_LONG        NUMBER                   NOT NULL,
  AIRCRAFT_PITCH       NUMBER                   NOT NULL,
  AIRCRAFT_ROLL        NUMBER                   NOT NULL,
  AIRCRAFT_HEADING     NUMBER                   NOT NULL,
  AIRCRAFT_ALT         NUMBER                   NOT NULL,
  AIRCRAFT_FOM         NUMBER                   NOT NULL,
  IS_PDW_RESTORE       NUMBER(1)                NOT NULL,
  IS_IQ_RESTORE        NUMBER(1)                NOT NULL,
  IS_FILTERED          NUMBER(1)                NOT NULL,
  IS_MANUAL_INPUT      NUMBER(1)                NOT NULL,
  IS_VALIDITY          NUMBER(2)                NOT NULL,
  IS_CHECKPOSITION     NUMBER(1)                NOT NULL,
  
  FINAL_RPT_TIME       TIMESTAMP(9)             NOT NULL,
  FIRST_RPT_TIME       TIMESTAMP(9)             NOT NULL,
  
  ALOB_ID              NUMBER                   NOT NULL,
  AABT_ID              NUMBER                   NOT NULL,
  AAET_ID              NUMBER                   NOT NULL,
  
  EL_STAT              NUMBER(1)                NOT NULL,
  RAY_STAT             NUMBER(1)		NOT NULL,
  RCV_TIME             TIMESTAMP(9)           	NOT NULL
  
);

