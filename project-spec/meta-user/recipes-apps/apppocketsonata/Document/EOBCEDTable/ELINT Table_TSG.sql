DECLARE
    nCnt NUMBER;
BEGIN

    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'E_TSG';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.E_TSG';
    end if;         
    
        
END;

CREATE TABLE EW701.E_TSG
(
  LINK_NO           NUMBER(3),
  TYPE_OF_RECEIVER  NUMBER(1),
  TYPE_OF_SIGNAL    NUMBER(1),
  FREQ              NUMBER(11,3),
  PRI               NUMBER(5),
  PW                NUMBER(4),
  PA                NUMBER(4),
  START_OR_STOP     NUMBER(1),
  BAND              NUMBER(1),
  RESULT            NUMBER(1)
)