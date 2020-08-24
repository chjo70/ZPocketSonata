DECLARE
    nCnt NUMBER;
BEGIN

    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'CEF_WIND_CSTM';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.CEF_WIND_CSTM';
    end if;         
    
   
END;

CREATE TABLE EW701.CEF_WND_CSTM
(
  SEQ_ID       NUMBER(22)                       NOT NULL,
  CEFP_DIV     NUMBER(1)                        NOT NULL,
  OPER_ID      VARCHAR2(10 BYTE)                NOT NULL,
  WINDOW_NAME  VARCHAR2(50 BYTE)                NOT NULL
)    