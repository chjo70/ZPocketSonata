DROP SEQUENCE EW701.AUTO_E_MSG_IF_DATA;

CREATE SEQUENCE EW701.AUTO_E_MSG_IF_DATA
  START WITH 2
  MAXVALUE 9999999999999999999999999999
  MINVALUE 1
  NOCYCLE
  CACHE 20
  NOORDER;

DROP TABLE EW701.E_MSG_IF_DATA CASCADE CONSTRAINTS;

CREATE TABLE EW701.E_MSG_IF_DATA
(
  IF_SET_ID       NUMBER(22)                    NOT NULL,
  TASK_ID         VARCHAR2(22 BYTE),
  SEARCH_BAND_ID  NUMBER(5),
  CREATE_TIME     TIMESTAMP(9),
  NUM_IF          NUMBER(15),
  FILE_NAME       VARCHAR2(100 BYTE),
  FILE_LOCATION   VARCHAR2(300 BYTE),
  FILE_SIZE       NUMBER(10),
  LINK_NUM        NUMBER(1),
  TRIAL_NUM       NUMBER
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

COMMENT ON TABLE EW701.E_MSG_IF_DATA IS 'IF데이터전송메시지';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.IF_SET_ID IS 'IF셋트번호';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.TASK_ID IS '과제ID';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.SEARCH_BAND_ID IS '탐색밴드ID';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.CREATE_TIME IS '저장시각';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.NUM_IF IS 'IF개수';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.FILE_NAME IS '저장파일명';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.FILE_LOCATION IS '저장파일위치';

COMMENT ON COLUMN EW701.E_MSG_IF_DATA.FILE_SIZE IS '파일크기';


CREATE OR REPLACE TRIGGER EW701.AUTO_TRG_E_MSGIF 
BEFORE INSERT ON EW701.E_MSG_IF_DATA
FOR EACH ROW
BEGIN
    SELECT AUTO_E_MSG_IF_DATA.NEXTVAL
    INTO :NEW.IF_SET_ID
    FROM DUAL;
END;
/
