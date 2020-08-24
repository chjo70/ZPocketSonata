/* LOB					*/

DROP TRIGGER EW701.AUTO_TRG_E_AA_MSG_LOB_LINK2;

CREATE OR REPLACE TRIGGER EW701.AUTO_TRG_E_AA_MSG_LOB_LINK2  
BEFORE INSERT ON EW701.E_AA_MSG_LOB_LINK2
FOR EACH ROW
BEGIN
    SELECT AUTO_E_AA_MSG_LOB_LINK2.NEXTVAL
    INTO :NEW.SEQ_NUM
    FROM DUAL;
END;
/

/* LOB_ELEMENT					*/
DROP TRIGGER EW701.AUTO_TRG_E_LOB_ELMT_LIST_LINK2;

CREATE OR REPLACE TRIGGER EW701.AUTO_TRG_E_LOB_ELMT_LIST_LINK2  
BEFORE INSERT ON EW701.E_AA_MSG_LOB_ELMT_LIST_LINK2
FOR EACH ROW
BEGIN
    SELECT AUTO_E_AA_MSG_LOB_LINK2.CURRVAL
    INTO :NEW.SEQ_NUM
    FROM DUAL;
END;
/

/* BEAM					*/
/*
DROP TRIGGER EW701.AUTO_TRG_E_AA_GMI_BEAM;

CREATE OR REPLACE TRIGGER EW701.AUTO_TRG_E_AA_GMI_BEAM  
BEFORE INSERT ON EW701.E_AA_GMI_BEAM
FOR EACH ROW
BEGIN
    SELECT AUTO_E_AA_GMI_BEAM.NEXTVAL
    INTO :NEW.SEQ_NUM
    FROM DUAL;
END;
/
*/

/* BEAM_ELEMENT                    */
/*
DROP TRIGGER EW701.AUTO_TRG_E_AA_BEAM_ELMT_LIST;

CREATE OR REPLACE TRIGGER EW701.AUTO_TRG_E_AA_BEAM_ELMT_LIST  
BEFORE INSERT ON EW701.E_AA_GMI_BEAM_ELMT_LIST
FOR EACH ROW
BEGIN
    SELECT AUTO_E_AA_GMI_BEAM.CURRVAL
    INTO :NEW.SEQ_NUM
    FROM DUAL;
END;
/
*/

/* EMITTER	*/
/*
DROP TRIGGER EW701.AUTO_TRG_E_AA_GMI_EMITTER;

CREATE OR REPLACE TRIGGER EW701.AUTO_TRG_E_AA_GMI_EMITTER  
BEFORE INSERT ON EW701.E_AA_GMI_EMITTER
FOR EACH ROW
BEGIN
    SELECT AUTO_E_AA_GMI_EMITTER.NEXTVAL
    INTO :NEW.SEQ_NUM
    FROM DUAL;
END;
/

*/