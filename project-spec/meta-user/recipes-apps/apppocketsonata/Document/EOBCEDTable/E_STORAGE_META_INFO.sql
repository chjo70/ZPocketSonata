ALTER TABLE EW701.E_STORAGE_META_INFO
 DROP PRIMARY KEY CASCADE;

DROP TABLE EW701.E_STORAGE_META_INFO CASCADE CONSTRAINTS;

CREATE TABLE EW701.E_STORAGE_META_INFO
(
  META_DATA_ID     VARCHAR2(20 BYTE),
  MISSION_ID       VARCHAR2(32 BYTE),
  TASK_ID          VARCHAR2(32 BYTE),
  SEARCH_BAND_ID   NUMBER(5),
  RECEIVER_TYPE    NUMBER(2),
  STOR_DATA_TYPE   NUMBER(4),
  CENTER_FREQ      NUMBER(11,3),
  RX_LIMIT_PA      NUMBER(5,2),
  FILEPATH         VARCHAR2(255 BYTE),
  FILENAME         VARCHAR2(127 BYTE),
  ACQ_START_TIME   TIMESTAMP(9),
  ACQ_TIME         NUMBER(12),
  ENDIAN           NUMBER(1),
  SAMPLE_RATE      NUMBER(1),
  BYTE_UNIT_SIZE   NUMBER(1),
  BANDWIDTH        NUMBER(11,3),
  FILESIZE         NUMBER(15),
  SZFILESIZE       VARCHAR2(40 BYTE),
  NUM_OF_DATA      NUMBER(10),
  ACQ_END_TIME     TIMESTAMP(9),
  NUM_OF_FILE      NUMBER(7),
  OPERATION_MODE   NUMBER(1),
  LINK_NO          NUMBER(1),
  DOWNLOAD_STATUS  NUMBER(2),
  CONVERT_STATUS   NUMBER(2)
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

COMMENT ON TABLE EW701.E_STORAGE_META_INFO IS '저장장치메타정보';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.META_DATA_ID IS '메타데이터ID';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.MISSION_ID IS '임무ID';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.TASK_ID IS '과제ID';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.SEARCH_BAND_ID IS '탐색대역ID';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.STOR_DATA_TYPE IS '저장데이터구분';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.CENTER_FREQ IS '중심주파수';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.RX_LIMIT_PA IS '수신임계치';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.FILENAME IS '파일명';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.ACQ_START_TIME IS '수집시작시각';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.ACQ_TIME IS '수집시각';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.ENDIAN IS 'ENDIAN';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.SAMPLE_RATE IS 'SAMPLERATE';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.FILESIZE IS '파일용량';

COMMENT ON COLUMN EW701.E_STORAGE_META_INFO.NUM_OF_DATA IS '데이터개수';


CREATE UNIQUE INDEX EW701.PK_E_STORAGE_META_INFO ON EW701.E_STORAGE_META_INFO
(META_DATA_ID)
LOGGING
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
NOPARALLEL;

ALTER TABLE EW701.E_STORAGE_META_INFO ADD (
  CONSTRAINT PK_E_STORAGE_META_INFO
  PRIMARY KEY
  (META_DATA_ID)
  USING INDEX EW701.PK_E_STORAGE_META_INFO
  ENABLE VALIDATE);
