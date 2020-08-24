DECLARE
    nCnt NUMBER;
BEGIN
    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'E_LOB_FILTER_LIST';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.E_LOB_FILTER_LIST';
    end if;
END;

CREATE TABLE EW701.E_LOB_FILTER_LIST
(
  LOB_FILTER_INDEX                INTEGER       NOT NULL,
  LOB_FILTER_NAME                 VARCHAR2(50 BYTE),
  FILTER_USED                     INTEGER,
  LINK                            INTEGER,
  SIGNAL_TYPE_USED                INTEGER,
  SIGNAL_TYPE                     INTEGER,
  RF_USED                         INTEGER,
  RF_MIN                          INTEGER,
  RF_MAX                          INTEGER,
  PRI_USED                        INTEGER,
  PRI_MIN                         INTEGER,
  PRI_MAX                         INTEGER,
  PW_USED                         INTEGER,
  PW_MIN                          INTEGER,
  PW_MAX                          INTEGER,
  PULSE_PER_GROUP_USED            INTEGER,
  PULSE_PER_GROUP_MIN             INTEGER,
  PULSE_PER_GROUP_MAX             INTEGER,
  PRIMARY KEY (LOB_FILTER_INDEX)
)

