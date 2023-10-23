DROP TABLE if exists "RAWDATA";
DROP TABLE if exists "LOBDATA";
DROP TABLE if exists "ABTDATA";
DROP TABLE if exists "POSITION";
DROP TABLE if exists "ELEMENT";
DROP TABLE if exists "AETDATA";


CREATE TABLE "RAWDATA" (
	"OP_INIT_ID" 				INTEGER NOT NULL,	
	"PDWID"						INTEGER NOT NULL,
	"PLOBID"					INTEGER NOT NULL,	
			
	"LOBID"						INTEGER NOT NULL,
			
	"TASK_ID"					VARCHAR(20),
	"CREATE_TIME"				datetime,
	"CREATE_TIME_MS"			tinyint,
	"COUNTOFDATA"				tinyint,
	"FILENAME"					char(100),
	"DATA_TYPE"					tinyint,
	"COL_BANK"					tinyint
	
	/*
	PRIMARY KEY("OP_INIT_ID","PDWID","PLOBID","LOBID")
	*/

);


CREATE TABLE "LOBDATA" (
	"OP_INIT_ID" 				INTEGER NOT NULL,	
	"PDWID"						INTEGER NOT NULL,
	"PLOBID"					INTEGER NOT NULL,	
		
	"LOBID"						INTEGER NOT NULL,
	"ABTID"						INTEGER NOT NULL,
	"AETID"						INTEGER NOT NULL,
	
	"TASK_ID" 					VARCHAR(20),	
	
	"CONTACT_TIME"				datetime,
	"CONTACT_TIME_MS"			INTEGER,
	
    "PRIMARY_ELNOT" 			VARCHAR(12),
    "PRIMARY_MODECODE" 			VARCHAR(12),
    "SECONDARY_ELNOT" 			VARCHAR(12),
    "SECONDARY_MODECODE" 		VARCHAR(12),
    "TERTIARY_ELNOT" 			VARCHAR(12),
    "TERTIARY_MODECODE" 		VARCHAR(12),
    "MODULATION_CODE" 			VARCHAR(12),
    "RADARMODE_NAME" 			VARCHAR(12),
    "NICK_NAME" 				VARCHAR(12),
    "FUNC_CODE" 				VARCHAR(12),
	"RADARMODE_INDEX"			smallint,
	
    "POLIZATION" 				tinyint,
    "RATIOOFPOL" 				tinyint,
	
	"SIGNAL_TYPE"				tinyint,
		
	"DOA_MEAN"					float,
	"DOA_MIN"					float,
	"DOA_MAX"					float,
	"DOA_DEV"					float,
	"DOA_STD"					float,
	"DI_RATIO"					float,

	"FREQ_TYPE"					tinyint,
	"FREQ_PATTERN_TYPE"			tinyint,
	"FREQ_PATTERN_PERIOD"		float,
	"FREQ_MEAN"					float,
	"FREQ_MIN"					float,
	"FREQ_MAX"					float,
	"FREQ_DEV"					float,
	"FREQ_STD"					float,
	"FREQ_POSITION_COUNT"		tinyint,
	"FREQ_ELEMENT_COUNT"		tinyint,
	
	"PRI_TYPE"					tinyint,
	"PRI_PATTERN_TYPE"			tinyint,
	"PRI_PATTERN_PERIOD"		float,
	"PRI_MEAN"					float,
	"PRI_MIN"					float,
	"PRI_MAX"					float,
	"PRI_DEV"					float,
	"PRI_STD"					float,
	"PRI_JITTER_RATIO"			float,
	"PRI_POSITION_COUNT"		tinyint,
	"PRI_ELEMENT_COUNT"			tinyint,
	
	"PW_MEAN"					float,
	"PW_MIN"					float,
	"PW_MAX"					float,
	"PW_DEV"					float,
	"PW_STD"					float,
	
	"PA_MEAN"					float,
	"PA_MIN"					float,
	"PA_MAX"					float,
	"PA_DEV"					float,
	"PA_STD"					float,
	
    "SCAN_TYPE" 				int,
    "SCAN_PRD" 					float,

    "INTRA_TYPE" 				integer,
    "INTRA_TYPE_DETAIL" 		integer,
    "INTRA_FRQ_MEAN" 			float,
    "INTRA_FRQ_MIN" 			float,
    "INTRA_FRQ_MAX" 			float,
    "INTRA_FRQ_DEVIATION" 		float,
	
    "LATITUDE" 					float,
    "LONGITUDE" 				float,
    "HEADING" 					float,
    "ROLL" 						float,
    "PITCH" 					float,	
    "ALTITUDE" 					float,
		
	"COLLECTOR_ID"				smallint,
		
    "IS_VALIDITY" 				integer,
	
    "IS_FILTERED" 				integer,

	"NUM_PDW"					smallint,
    "NUM_IQ"					smallint
	
	/*
	PRIMARY KEY("OP_INIT_ID","PDWID","PLOBID","LOBID")

	FOREIGN KEY("OP_INIT_ID") REFERENCES "RAWDATA"("OP_INIT_ID"),
	FOREIGN KEY("PDWID") REFERENCES "RAWDATA"("PDWID"),
	FOREIGN KEY("PLOBID") REFERENCES "RAWDATA"("PLOBID")
	
	*/

	
);

CREATE TABLE "ABTDATA" (
	"OP_INIT_ID" 				INTEGER NOT NULL,	
	"PDWID"						INTEGER NOT NULL,
	"PLOBID"					INTEGER NOT NULL,	

	"LOBID"						INTEGER NOT NULL,
	"ABTID"						INTEGER NOT NULL,
	"AETID"						INTEGER NOT NULL,
	
	"FIRST_TIME"				datetime,
	"LAST_TIME"					datetime,
	"PRIMARY_ELNOT"				VARCHAR(12),
	"PRIMARY_MODECODE"			VARCHAR(12),
	"MODULATION_CODE"			VARCHAR(12),
	"PLACENAME_KOR"				VARCHAR(12),
	"NICK_NAME"					VARCHAR(12),
	"FUNC_CODE"					VARCHAR(12),
	"PLATFORM_TYPE"				VARCHAR(12),
	"RADARMODE_NAME" 			VARCHAR(20),
	"RADARMODE_PRIORITY"		tinyint,
	"RADAR_PRIORITY"			tinyint,
	"RADARMODE_INDEX"			integer,
	"THREAT_INDEX"				integer,
	"POLIZATION"				tinyint,
	"SIGNAL_TYPE"				tinyint,
	"DOA_MEAN"					float,
	"DOA_MIN"					float,
	"DOA_MAX"					float,
	"DOA_DEV"					float,
	"FREQ_TYPE"					tinyint,
	"FREQ_PATTERN_TYPE"			tinyint,
	"FREQ_PATTERN_PERIOD_MEAN"	float,
	"FREQ_PATTERN_PERIOD_MIN"	float,
	"FREQ_PATTERN_PERIOD_MAX"	float,
	"FREQ_MEAN"					float,
	"FREQ_MIN"					float,
	"FREQ_MAX"					float,
	"FREQ_DEV"					float,
	"FREQ_POSITION_COUNT"		tinyint,
	"FREQ_ELEMENT_COUNT"		tinyint,
	"PRI_TYPE"					tinyint,
	"PRI_PATTERN_TYPE"			tinyint,
	"PRI_PATTERN_PERIOD_MEAN"	float,
	"PRI_PATTERN_PERIOD_MIN"	float,
	"PRI_PATTERN_PERIOD_MAX"	float,
	"PRI_MEAN"					float,
	"PRI_MIN"					float,
	"PRI_MAX"					float,
	"PRI_DEV"					float,
	"PRI_JITTER_RATIO"			float,
	"PRI_POSITION_COUNT"		tinyint,
	"PRI_ELEMENT_COUNT"			tinyint,
	"PW_MEAN"					float,
	"PW_MIN"					float,
	"PW_MAX"					float,
	"PW_DEV"					float,
	"PA_MEAN"					float,
	"PA_MIN"					float,
	"PA_MAX"					float,
	"PA_DEV"					float,
	"SCAN_TYPE"					tinyint,
	"SCAN_PRD_MEAN_SEC"			float,
	"SCAN_PRD_MIN_SEC"			float,
	"SCAN_PRD_MAX_SEC"			float,
	"HAS_INTRA_MOD"				tinyint,
	"INTRA_FRQ_CHNG_WID_MIN"	float,	
	"INTRA_FRQ_CHNG_WID_MAX"	float,
	"PE_VALID"					tinyint,
	"PE_LATITUDE"				float,
	"PE_LONGITUDE"				float,
	"BEAM_VALIDITY"				float,
	"PE_CEP"					float,
	"PE_MAJOR_AXIS"				float,
	"PE_MINOR_AXIS"				float,
	"PE_THETA"					float,
	"PE_DISTANCE"				float,
	"TOTAL_PDW"					int,
	"NUM_LOB"					int,
	"ALARM_TIME"				datetime,
	"STAT"						tinyint
	
	/*
	PRIMARY KEY("OP_INIT_ID","LOBID","ABTID","AETID" ),
	
	FOREIGN KEY("OP_INIT_ID") REFERENCES "LOBDATA"("OP_INIT_ID"),
	FOREIGN KEY("PDWID") REFERENCES "LOBDATA"("PDWID"),
	FOREIGN KEY("PLOBID") REFERENCES "LOBDATA"("PLOBID"),
	FOREIGN KEY("LOBID") REFERENCES "LOBDATA"("LOBID"),
	FOREIGN KEY("ABTID") REFERENCES "LOBDATA"("ABTID"),
	FOREIGN KEY("AETID") REFERENCES "LOBDATA"("AETID")
	*/

);

CREATE TABLE "POSITION" (
    "SEQ_TYPE"					tinyint NOT NULL,
	
	"OP_INIT_ID" 				INTEGER NOT NULL,	
	"PDWID"						INTEGER NOT NULL,
	"PLOBID"					INTEGER NOT NULL,	

	"LOBID"						INTEGER NOT NULL,
	"ABTID"						INTEGER NOT NULL,
	"AETID"						INTEGER NOT NULL,

	"POSITION_COUNT"			tinyint  NOT NULL,
	
	"SEQ_01"					float,
	"SEQ_02"					float,
	"SEQ_03"					float,
	"SEQ_04"					float,
	"SEQ_05"					float,
	"SEQ_06"					float,
	"SEQ_07"					float,
	"SEQ_08"					float,
	"SEQ_09"					float,
	"SEQ_10"					float,
	"SEQ_11"					float,
	"SEQ_12"					float,
	"SEQ_13"					float,
	"SEQ_14"					float,
	"SEQ_15"					float,
	"SEQ_16"					float,
	"SEQ_17"					float,
	"SEQ_18"					float,
	"SEQ_19"					float,
	"SEQ_20"					float,
	"SEQ_21"					float,
	"SEQ_22"					float,
	"SEQ_23"					float,
	"SEQ_24"					float,
	"SEQ_25"					float,
	"SEQ_26"					float,
	"SEQ_27"					float,
	"SEQ_28"					float,
	"SEQ_29"					float,
	"SEQ_30"					float,
	"SEQ_31"					float,
	"SEQ_32"					float
	
	/*
	PRIMARY KEY("SEQ_TYPE","OP_INIT_ID","LOBID","ABTID","AETID" )	
	
	FOREIGN KEY("OP_INIT_ID") REFERENCES "LOBDATA"("OP_INIT_ID"),
	FOREIGN KEY("PDWID") REFERENCES "LOBDATA"("PDWID"),
	FOREIGN KEY("PLOBID") REFERENCES "LOBDATA"("PLOBID"),
	FOREIGN KEY("LOBID") REFERENCES "LOBDATA"("LOBID"),
	FOREIGN KEY("ABTID") REFERENCES "LOBDATA"("ABTID"),
	FOREIGN KEY("AETID") REFERENCES "LOBDATA"("AETID")
	*/

);


CREATE TABLE "AETDATA" (
	"OP_INIT_ID" 				INTEGER NOT NULL,	
	"PDWID"						INTEGER NOT NULL,
	"PLOBID"					INTEGER NOT NULL,	

	"LOBID"						INTEGER NOT NULL,
	"ABTID"						INTEGER NOT NULL,
	"AETID"						INTEGER NOT NULL,
	
	"FIRST_TIME" 				datetime,
	"LAST_TIME"					datetime,		

	"PRIMARY_ELNOT" 			VARCHAR(20),
    "PRIMARY_MODECODE" 			VARCHAR(20),
    "RADARMODE_NAME" 			VARCHAR(20),
	"NICK_NAME" 				VARCHAR(20),
    "FUNC_CODE" 				VARCHAR(20),
    "PLATFORM_TYPE" 			VARCHAR(20),
    "RADARMODE_PRIORITY" 		tinyint,
    "RADAR_PRIORITY" 			tinyint,  
	"PIN_NUM"					integer,
    "PLACENAME_KOR" 			VARCHAR(20),
	"THREAT_FUNC_CODE"			tinyint,
	"THREAT_PRIORITY"			tinyint,
    
	"RADARMODE_INDEX"			smallint,
	"THREAT_INDEX"				smallint,   

	"VALIDITY"					tinyint,

	"DOA_MEAN"					float,
	"DOA_MIN"					float,
	"DOA_MAX"					float,
	"DOA_DEV"					float,

	"FRQ_MEAN"					float,
	"FRQ_MIN"					float,
	"FRQ_MAX"					float,
	"FRQ_DEV"					float,

	"PRI_MEAN"					float,
	"PRI_MIN"					float,
	"PRI_MAX"					float,
	"PRI_DEV"					float,

	"PW_MEAN"					float,
	"PW_MIN"					float,
	"PW_MAX"					float,
	"PW_DEV"					float,

	"PA_MEAN"					float,
	"PA_MIN"					float,
	"PA_MAX"					float,
	"PA_DEV"					float,
	
	"PE_VALID"					smallint,
	"PE_LATITUDE"				float,
	"PE_LONGITUDE"				float,
    "PE_HEIGHT"					float,
	"PE_CEP"					float,
	"PE_MAJOR_AXIS"				float,
	"PE_MINOR_AXIS"				float,
	"PE_THETA"					float,
	"PE_DISTANCE"				float,	
	
	"STAT"						tinyint,
	
	"NUM_OF_BEAMS"				tinyint,
	"NUM_OF_LOBS"				integer,
	
	"IDINFO"					VARCHAR(12),
	
	"FINAL_ALARM_TIME"			datetime,
	
	PRIMARY KEY("OP_INIT_ID","LOBID","ABTID","AETID" ),
	
	FOREIGN KEY("OP_INIT_ID") REFERENCES "ABTDATA"("OP_INIT_ID"),
	FOREIGN KEY("PDWID") REFERENCES "ABTDATA"("PDWID"),
	FOREIGN KEY("PLOBID") REFERENCES "ABTDATA"("PLOBID"),
	FOREIGN KEY("LOBID") REFERENCES "ABTDATA"("LOBID"),
	FOREIGN KEY("ABTID") REFERENCES "ABTDATA"("ABTID"),
	FOREIGN KEY("AETID") REFERENCES "ABTDATA"("AETID")

);


