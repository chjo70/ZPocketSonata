DECLARE
    nCnt NUMBER;
BEGIN

    SELECT COUNT(*) INTO nCnt FROM ALL_TABLES WHERE TABLE_NAME = 'E_AA_MSG_LOB_ELMT_LIST';
    if nCnt > 0 then execute immediate 'DROP TABLE EW701.E_AA_MSG_LOB_ELMT_LIST';
    end if;         
    
        
END;

CREATE TABLE EW701.E_AA_MSG_LOB_ELMT_LIST
(
  SEQ_NUM           NUMBER                     NOT NULL,

  LINK_NUM          NUMBER(2)                  NOT NULL,
  MISSION_ID        VARCHAR2(22 BYTE),
  TASK_ID           VARCHAR2(22 BYTE),
  
  LOB_ID               NUMBER                   NOT NULL,
  ABT_ID               NUMBER                   NOT NULL,
  AET_ID               NUMBER                   NOT NULL,  
  
  DATA_TYPE         NUMBER(2)                  NOT NULL,
  
  ELEMENTS          NUMBER(3)                   NOT NULL,
    
  SEQ_01    NUMBER,
  SEQ_02    NUMBER,
  SEQ_03    NUMBER,
  SEQ_04    NUMBER,
  SEQ_05    NUMBER,
  SEQ_06    NUMBER,
  SEQ_07    NUMBER,
  SEQ_08    NUMBER,
  SEQ_09    NUMBER,
  SEQ_10    NUMBER,
  SEQ_11    NUMBER,
  SEQ_12    NUMBER,
  SEQ_13    NUMBER,
  SEQ_14    NUMBER,
  SEQ_15    NUMBER,
  SEQ_16    NUMBER,
  SEQ_17    NUMBER,
  SEQ_18    NUMBER,
  SEQ_19    NUMBER,
  SEQ_20    NUMBER,
  SEQ_21    NUMBER,
  SEQ_22    NUMBER,
  SEQ_23    NUMBER,
  SEQ_24    NUMBER,
  SEQ_25    NUMBER,
  SEQ_26    NUMBER,
  SEQ_27    NUMBER,
  SEQ_28    NUMBER,
  SEQ_29    NUMBER,
  SEQ_30    NUMBER,
  SEQ_31    NUMBER,
  SEQ_32    NUMBER,
  SEQ_33    NUMBER,
  SEQ_34    NUMBER,
  SEQ_35    NUMBER,
  SEQ_36    NUMBER,
  SEQ_37    NUMBER,
  SEQ_38    NUMBER,
  SEQ_39    NUMBER,
  SEQ_40    NUMBER,
  SEQ_41    NUMBER,
  SEQ_42    NUMBER,
  SEQ_43    NUMBER,
  SEQ_44    NUMBER,
  SEQ_45    NUMBER,
  SEQ_46    NUMBER,
  SEQ_47    NUMBER,
  SEQ_48    NUMBER,
  SEQ_49    NUMBER,
  SEQ_50    NUMBER,
  SEQ_51    NUMBER,
  SEQ_52    NUMBER,
  SEQ_53    NUMBER,
  SEQ_54    NUMBER,
  SEQ_55    NUMBER,
  SEQ_56    NUMBER,
  SEQ_57    NUMBER,
  SEQ_58    NUMBER,
  SEQ_59    NUMBER,
  SEQ_60    NUMBER,
  SEQ_61    NUMBER,
  SEQ_62    NUMBER,
  SEQ_63    NUMBER,
  SEQ_64    NUMBER

)
