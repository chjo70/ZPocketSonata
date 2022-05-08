DROP TABLE if exists "LOBDATA";
DROP TABLE if exists "LOB_POSITION";
DROP TABLE if exists "ABTDATA";
DROP TABLE if exists "ABT_POSITION";
DROP TABLE if exists "AETDATA";
DROP TABLE if exists "RAWDATA";



CREATE TABLE "RAWDATA" (
	"PDWID"	integer NOT NULL,
	"PLOBID"	integer NOT NULL,
	"TASK_ID"	VARCHAR2(30),
	"CREATE_TIME"	datetime,
	"CREATE_TIME_MS"	tinyint,
	"COUNTOFDATA"	tinyint,
	"FILENAME"	char(100),
	"DATA_TYPE"	tinyint,
	"COL_BANK"	tinyint,
	PRIMARY KEY("PDWID","PLOBID")
);


CREATE TABLE "LOBDATA" (
	"PDWID"	INTEGER NOT NULL,	
	
	"PLOBID"	INTEGER NOT NULL,	
	
	"LOBID"	INTEGER NOT NULL,
	"ABTID"	int NOT NULL,
	"AETID"	int NOT NULL,
	
	"TASK_ID" VARCHAR2(30),	
	
	"CONTACT_TIME"	datetime,
	"CONTACT_TIME_MS"	int,

    "PRIMARY_ELNOT" VARCHAR2(12),
    "PRIMARY_MODECODE" VARCHAR2(12),
    "SECONDARY_ELNOT" VARCHAR2(12),
    "SECONDARY_MODECODE" VARCHAR2(12),
    "TERTIARY_ELNOT" VARCHAR2(12),
    "TERTIARY_MODECODE" VARCHAR2(12),
    "MODULATION_CODE" VARCHAR2(12),
    "RADARMODE_NAME" VARCHAR2(64),
    "NICK_NAME" VARCHAR2(64),
    "FUNC_CODE" VARCHAR2(12),
	"RADARMODE_INDEX"	smallint,
	"THREAT_INDEX"	smallint,    

    "POLIZATION" int,
    "RATIOOFPOL" int,

	"SIGNAL_TYPE"	tinyint,
    
	"DOA_MEAN"	float,
	"DOA_MIN"	float,
	"DOA_MAX"	float,
	"DOA_DEV"	float,
	"DOA_STD"	float,
	"DI_RATIO"	float,

	"FREQ_TYPE"	tinyint,
	"FREQ_PATTERN_TYPE"	tinyint,
	"FREQ_PATTERN_PERIOD"	float,
	"FREQ_MEAN"	float,
	"FREQ_MIN"	float,
	"FREQ_MAX"	float,
	"FREQ_DEV"	float,
	"FREQ_POSITION_COUNT"	tinyint,
	"FREQ_ELEMENT_COUNT"	tinyint,

	"PRI_TYPE"	tinyint,
	"PRI_PATTERN_TYPE"	tinyint,
	"PRI_PATTERN_PERIOD"	float,
	"PRI_MEAN"	float,
	"PRI_MIN"	float,
	"PRI_MAX"	float,
	"PRI_DEV"	float,
	"PRI_JITTER_RATIO"	float,
	"PRI_POSITION_COUNT"	tinyint,
	"PRI_ELEMENT_COUNT"	tinyint,

	"PW_MEAN"	float,
	"PW_MIN"	float,
	"PW_MAX"	float,
	"PW_DEV"	float,

	"PA_MEAN"	float,
	"PA_MIN"	float,
	"PA_MAX"	float,
	"PA_DEV"	float,

    "SCAN_TYPE" int,
    "SCAN_PRD" float,

    "INTRA_TYPE" integer,
    "INTRA_TYPE_DETAIL" integer,
    "INTRA_FRQ_MEAN" float,
    "INTRA_FRQ_MIN" float,
    "INTRA_FRQ_MAX" float,
    "INTRA_FRQ_DEVIATION" float,

    "LATITUDE" float,
    "LONGITUDE" float,
    "HEADING" float,	
    "ROLL" float,
    "PITCH" float,	
    "ALTITUDE" float,
	
	"COLLECTOR_ID"	smallint,
    
    "IS_VALIDITY" integer,

    "IS_FILTERED" integer,

	"NUM_PDW"	smallint,
    "NUM_IQ"	smallint,
	
	FOREIGN KEY("PLOBID") REFERENCES "AETDATA"("PLOBID"),
	FOREIGN KEY("LOBID") REFERENCES "AETDATA"("LOBID"),
	FOREIGN KEY("PDWID") REFERENCES "AETDATA"("PDWID"),
	PRIMARY KEY("PDWID","PLOBID","LOBID"),
	FOREIGN KEY("PDWID","PLOBID","LOBID") REFERENCES "AETDATA"		

);

CREATE TABLE "LOB_POSITION" (
    "SEQ_TYPE"	tinyint NOT NULL,
	"PDWID"	INTEGER NOT NULL,	
	
	"PLOBID" INTEGER NOT NULL,	
	
	"LOBID"	INTEGER NOT NULL,
	"ABTID"	int NOT NULL,
	"AETID"	int NOT NULL,
	
	"POSITION_COUNT"	tinyint  NOT NULL,
	
	"SEQ_01"	float,
	"SEQ_02"	float,
	"SEQ_03"	float,
	"SEQ_04"	float,
	"SEQ_05"	float,
	"SEQ_06"	float,
	"SEQ_07"	float,
	"SEQ_08"	float,
	"SEQ_09"	float,
	"SEQ_10"	float,
	"SEQ_11"	float,
	"SEQ_12"	float,
	"SEQ_13"	float,
	"SEQ_14"	float,
	"SEQ_15"	float,
	"SEQ_16"	float,
	"SEQ_17"	float,
	"SEQ_18"	float,
	"SEQ_19"	float,
	"SEQ_20"	float,
	"SEQ_21"	float,
	"SEQ_22"	float,
	"SEQ_23"	float,
	"SEQ_24"	float,
	"SEQ_25"	float,
	"SEQ_26"	float,
	"SEQ_27"	float,
	"SEQ_28"	float,
	"SEQ_29"	float,
	"SEQ_30"	float,
	"SEQ_31"	float,
	"SEQ_32"	float,
	
	FOREIGN KEY("PLOBID") REFERENCES "LOBDATA"("PLOBID"),
	FOREIGN KEY("LOBID") REFERENCES "LOBDATA"("LOBID"),
	FOREIGN KEY("PDWID") REFERENCES "LOBDATA"("PDWID"),
	PRIMARY KEY("SEQ_TYPE","LOBID"),
	FOREIGN KEY("PDWID","PLOBID") REFERENCES "LOBDATA"	
);


CREATE TABLE "ABTDATA" (
	"PDWID"	INTEGER NOT NULL,	
	
	"PLOBID"	INTEGER NOT NULL,	
	
	"LOBID"	INTEGER NOT NULL,
	"ABTID"	INTEGER NOT NULL,
	"AETID"	INTEGER NOT NULL,
	
	"FIRST_TIME"	datetime,
	"LAST_TIME"	datetime,
	"PRIMARY_ELNOT"	VARCHAR2(12),
	"PRIMARY_MODECODE"	VARCHAR2(12),
	"MODULATION_CODE"	VARCHAR2(12),
	"RADARMODE_NAME"	VARCHAR2(64),
	"PLACENAME_KOR"	VARCHAR2(64),
	"NICK_NAME"	VARCHAR2(64),
	"FUNC_CODE"	VARCHAR2(12),
	"PLATFORM_TYPE"	VARCHAR2(25),
	"RADARMODE_PRIORITY"	NUMBER(5),
	"RADAR_PRIORITY"	NUMBER(5),
	"RADARMODE_INDEX"	smallint,
	"THREAT_INDEX"	smallint,
	"POLIZATION"	NUMBER(1),
	"SIGNAL_TYPE"	tinyint,
	"DOA_MEAN"	float,
	"DOA_MIN"	float,
	"DOA_MAX"	float,
	"DOA_DEV"	float,
	"FREQ_TYPE"	tinyint,
	"FREQ_PATTERN_TYPE"	tinyint,
	"FREQ_PATTERN_PERIOD_MEAN"	float,
	"FREQ_PATTERN_PERIOD_MIN"	float,
	"FREQ_PATTERN_PERIOD_MAX"	float,
	"FREQ_MEAN"	float,
	"FREQ_MIN"	float,
	"FREQ_MAX"	float,
	"FREQ_DEV"	float,
	"FREQ_POSITION_COUNT"	tinyint,
	"FREQ_ELEMENT_COUNT"	tinyint,
	"PRI_TYPE"	tinyint,
	"PRI_PATTERN_TYPE"	tinyint,
	"PRI_PATTERN_PERIOD_MEAN"	float,
	"PRI_PATTERN_PERIOD_MIN"	float,
	"PRI_PATTERN_PERIOD_MAX"	float,
	"PRI_MEAN"	float,
	"PRI_MIN"	float,
	"PRI_MAX"	float,
	"PRI_DEV"	float,
	"PRI_JITTER_RATIO"	float,
	"PRI_POSITION_COUNT"	tinyint,
	"PRI_ELEMENT_COUNT"	tinyint,
	"PW_MEAN"	float,
	"PW_MIN"	float,
	"PW_MAX"	float,
	"PW_DEV"	float,
	"PA_MEAN"	float,
	"PA_MIN"	float,
	"PA_MAX"	float,
	"PA_DEV"	float,
	"SCAN_TYPE"	NUMBER(1),
	"SCAN_PRD_MEAN_SEC"	float,
	"SCAN_PRD_MIN_SEC"	float,
	"SCAN_PRD_MAX_SEC"	float,
	"HAS_INTRA_MOD"	NUMBER(1),
	"INTRA_FRQ_CHNG_WID_MIN"	float,	
	"INTRA_FRQ_CHNG_WID_MAX"	float,
	"PE_VALID"	smallint,
	"PE_LATITUDE"	float,
	"PE_LONGITUDE"	float,
	"PE_CEP"	float,
	"PE_MAJOR_AXIS"	float,
	"PE_MINOR_AXIS"	float,
	"PE_THETA"	float,
	"PE_DISTANCE"	float,
	"TOTAL_PDW"	int,
	"NUM_LOB"	int,
	"ALARM_TIME"	datetime,
	"STAT"	tinyint,
	FOREIGN KEY("PLOBID") REFERENCES "RAWDATA"("PLOBID"),
	FOREIGN KEY("PDWID") REFERENCES "RAWDATA"("PDWID"),
	PRIMARY KEY("PDWID","PLOBID","LOBID"),
	FOREIGN KEY("PDWID","PLOBID") REFERENCES "RAWDATA"
);

CREATE TABLE "ABT_POSITION" (
    "SEQ_TYPE"	tinyint NOT NULL,
	"PDWID"	INTEGER NOT NULL,	
	
	"PLOBID" INTEGER NOT NULL,	
	
	"LOBID"	INTEGER NOT NULL,
	"ABTID"	int NOT NULL,
	"AETID"	int NOT NULL,
	
	"POSITION_COUNT"	tinyint  NOT NULL,
	
	"SEQ_01"	float,
	"SEQ_02"	float,
	"SEQ_03"	float,
	"SEQ_04"	float,
	"SEQ_05"	float,
	"SEQ_06"	float,
	"SEQ_07"	float,
	"SEQ_08"	float,
	"SEQ_09"	float,
	"SEQ_10"	float,
	"SEQ_11"	float,
	"SEQ_12"	float,
	"SEQ_13"	float,
	"SEQ_14"	float,
	"SEQ_15"	float,
	"SEQ_16"	float,
	"SEQ_17"	float,
	"SEQ_18"	float,
	"SEQ_19"	float,
	"SEQ_20"	float,
	"SEQ_21"	float,
	"SEQ_22"	float,
	"SEQ_23"	float,
	"SEQ_24"	float,
	"SEQ_25"	float,
	"SEQ_26"	float,
	"SEQ_27"	float,
	"SEQ_28"	float,
	"SEQ_29"	float,
	"SEQ_30"	float,
	"SEQ_31"	float,
	"SEQ_32"	float,

	FOREIGN KEY("PLOBID") REFERENCES "ABTDATA"("PLOBID"),
	FOREIGN KEY("LOBID") REFERENCES "ABTDATA"("LOBID"),
	FOREIGN KEY("PDWID") REFERENCES "ABTDATA"("PDWID"),
	PRIMARY KEY("SEQ_TYPE","LOBID"),
	FOREIGN KEY("PDWID","PLOBID") REFERENCES "ABTDATA"		
);

CREATE TABLE "AETDATA" (
	"PDWID"	INTEGER NOT NULL,	
	
	"PLOBID"	INTEGER NOT NULL,	
	
	"LOBID"	INTEGER NOT NULL,
	"ABTID"	int NOT NULL,
	"AETID"	int NOT NULL,
	
	"FIRST_TIME" datetime,
	"LAST_TIME"	datetime,		

	"PRIMARY_ELNOT" VARCHAR2(12),
    "PRIMARY_MODECODE" VARCHAR2(12),
    "RADARMODE_NAME" VARCHAR2(64),
	"NICK_NAME" VARCHAR2(64),
    "FUNC_CODE" VARCHAR2(12),
    "PLATFORM_TYPE" VARCHAR2(25),
    "RADARMODE_PRIORITY" NUMBER(5),
    "RADAR_PRIORITY" NUMBER(5),    
	"PIN_NUM"	NUMBER,
    "PLACENAME_KOR" VARCHAR2(64),
	"THREAT_FUNC_CODE"	VARCHAR2(64),
	"THREAT_PRIORITY"	NUMBER,
    
	"RADARMODE_INDEX"	smallint,
	"THREAT_INDEX"	smallint,   

	"VALIDITY"	NUMBER(1) NOT NULL,
	
	"DOA_MEAN"	float,
	"DOA_MIN"	float,
	"DOA_MAX"	float,
	"DOA_DEV"	float,
	
	"FRQ_MEAN"	float,
	"FRQ_MIN"	float,
	"FRQ_MAX"	float,
	"FRQ_DEV"	float,
	
	"PRI_MEAN"	float,
	"PRI_MIN"	float,
	"PRI_MAX"	float,
	"PRI_DEV"	float,
	
	"PW_MEAN"	float,
	"PW_MIN"	float,
	"PW_MAX"	float,
	"PW_DEV"	float,
	
	"PA_MEAN"	float,
	"PA_MIN"	float,
	"PA_MAX"	float,
	"PA_DEV"	float,
	
	"PE_VALID"	smallint,
	"PE_LATITUDE"	float,
	"PE_LONGITUDE"	float,
    "PE_HEIGHT"	float,
	"PE_CEP"	float,
	"PE_MAJOR_AXIS"	float,
	"PE_MINOR_AXIS"	float,
	"PE_THETA"	float,
	"PE_DISTANCE"	float,	
	
	"STAT"	NUMBER,
	
	"NUM_OF_BEAMS"	NUMBER NOT NULL,
	"NUM_OF_LOBS"	NUMBER NOT NULL,
	
	"IDINFO"	VARCHAR2(12),
	
	"FINAL_ALARM_TIME"	TIMESTAMP(9),
	
	FOREIGN KEY("PLOBID") REFERENCES "ABTDATA"("PLOBID"),
	FOREIGN KEY("LOBID") REFERENCES "ABTDATA"("LOBID"),
	FOREIGN KEY("PDWID") REFERENCES "ABTDATA"("PDWID"),
	PRIMARY KEY("PDWID","PLOBID","LOBID"),
	FOREIGN KEY("PDWID","PLOBID","LOBID") REFERENCES "ABTDATA"	
);
