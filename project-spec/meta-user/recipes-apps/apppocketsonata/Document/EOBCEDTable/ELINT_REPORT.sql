DROP TABLE EW701.E_REPORT CASCADE CONSTRAINTS;

CREATE TABLE EW701.E_REPORT
(
  TABLE_ID         VARCHAR2(22 BYTE)            NOT NULL,
  REPORT_ID        VARCHAR2(22 BYTE)            NOT NULL,
  REPORT_TYPE      NUMBER(2)                    NOT NULL,
  SERIAL_NO        VARCHAR2(10 BYTE),
  CREATE_DATE      TIMESTAMP(9)                 NOT NULL,
  AET_ID           NUMBER(5)                    NOT NULL,
  LOB_ID           NUMBER(5)                    NOT NULL,
  TASK_ID          VARCHAR2(22 BYTE)            NOT NULL,
  ELNOT            VARCHAR2(10 BYTE),
  REPORT_STATUS    NUMBER(1),
  TRANSMIT_DATE    TIMESTAMP(9),
  REPORT_CONTENT   VARCHAR2(4000 BYTE),
  RPT_MEMO         VARCHAR2(100 BYTE),
  OPER_ID          VARCHAR2(20 BYTE),
  DTCT_ID          VARCHAR2(22 BYTE),
  NUM_OF_RPT_OBJ   NUMBER(2),
  REPORT_CONTENTS  CLOB,
  BUFFER_SIZE      NUMBER(10),
  UPDATE_DATE      TIMESTAMP(9),
  MISSION_ID       VARCHAR2(22 BYTE),
  EST_LOC_LAT      NUMBER,
  EST_LOC_LONG     NUMBER,
  PIN_NUM          NUMBER(5),
  MISSION_NAME     VARCHAR2(40 BYTE),
  TASK_NAME        VARCHAR2(40 BYTE),
  ABT_ID           NUMBER
)
LOB (REPORT_CONTENTS) STORE AS (
  TABLESPACE  EW701
  ENABLE      STORAGE IN ROW
  CHUNK       8192
  RETENTION
  NOCACHE
  LOGGING
      STORAGE    (
                  INITIAL          64K
                  NEXT             1M
                  MINEXTENTS       1
                  MAXEXTENTS       UNLIMITED
                  PCTINCREASE      0
                  BUFFER_POOL      DEFAULT
                  FLASH_CACHE      DEFAULT
                  CELL_FLASH_CACHE DEFAULT
                 ))
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

COMMENT ON TABLE EW701.E_REPORT IS '보고서 관리';

COMMENT ON COLUMN EW701.E_REPORT.TABLE_ID IS '테이블ID,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.REPORT_ID IS '보고서ID,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.REPORT_TYPE IS '보고서종류,,0,0,2,,';

COMMENT ON COLUMN EW701.E_REPORT.SERIAL_NO IS '일련번호,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.CREATE_DATE IS '생성시간,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.AET_ID IS 'AET ID,,1,1,65535,,AET_ID';

COMMENT ON COLUMN EW701.E_REPORT.LOB_ID IS 'LOB ID,,1,1,65535,,LOB_ID';

COMMENT ON COLUMN EW701.E_REPORT.TASK_ID IS '과제 ID,,,,,,TASK_ID';

COMMENT ON COLUMN EW701.E_REPORT.ELNOT IS 'ELNOT,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.REPORT_STATUS IS '과제상태,,0,0,3,,';

COMMENT ON COLUMN EW701.E_REPORT.TRANSMIT_DATE IS '전송날짜,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.REPORT_CONTENT IS '보고서,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.RPT_MEMO IS '메모,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.OPER_ID IS '운용자ID,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.DTCT_ID IS '수집ID,,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.NUM_OF_RPT_OBJ IS '중첩수,,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.REPORT_CONTENTS IS '내용,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.BUFFER_SIZE IS '사이즈,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.UPDATE_DATE IS '갱신날짜,,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.MISSION_ID IS '임무ID,,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.EST_LOC_LAT IS 'EST위도,,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.EST_LOC_LONG IS 'EST경도,,,,,,,,,';

COMMENT ON COLUMN EW701.E_REPORT.PIN_NUM IS '핀수,,,,,,,,,';
