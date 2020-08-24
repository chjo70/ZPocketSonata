/****** Object: Table [dbo].[ABTDATA]   Script Date: 2019-04-18 오후 3:22:26 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO

DROP TABLE dbo.ABTDATA

CREATE TABLE "ABTDATA" (
	"SEQ_NUM"	integer PRIMARY KEY AUTOINCREMENT,
	"ABTID"	int NOT NULL,
	"AETID"	int NOT NULL,
	"FIRST_TIME"	datetime,
	"LAST_TIME"	datetime,
	"SIGNAL_TYPE"	tinyint,
	"NUM_LOB"	int,
	"BEAM_VALIDITY"	int,
	"FREQ_TYPE"	tinyint,
	"FREQ_PATTERN_TYPE"	tinyint,
	"FREQ_PATTERN_PERIOD_MEAN"	float,
	"FREQ_PATTERN_PERIOD_MIN"	float,
	"FREQ_PATTERN_PERIOD_MAX"	float,
	"FREQ_MEAN"	float,
	"FREQ_MIN"	float,
	"FREQ_MAX"	float,
	"FREQ_POSITION_COUNT"	tinyint,
	"PRI_TYPE"	tinyint,
	"PRI_PATTERN_TYPE"	tinyint,
	"PRI_PATTERN_PERIOD_MEAN"	float,
	"PRI_PATTERN_PERIOD_MIN"	float,
	"PRI_PATTERN_PERIOD_MAX"	float,
	"PRI_MEAN"	float,
	"PRI_MIN"	float,
	"PRI_MAX"	float,
	"PRI_JITTER_RATIO"	float,
	"PRI_POSITION_COUNT"	tinyint,
	"PW_MEAN"	float,
	"PW_MIN"	float,
	"PW_MAX"	float,
	"PA_MEAN"	float,
	"PA_MIN"	float,
	"PA_MAX"	float,
	"TOTAL_PDW"	int,
	"RADAR_NAME"	varchar(20),
	"RADARMODE_INDEX"	smallint,
	"THREAT_INDEX"	smallint,
	"PE_VALID"	smallint,
	"PE_LATITUDE"	float,
	"PE_LONGGITUDE"	float,
	"PE_CEP"	float,
	"PE_MAJOR_AXIS"	float,
	"PE_MINOR_AXIS"	float,
	"PE_THETA"	float,
	"PE_DISTANCE"	float,
	"ALARM_TIME"	datetime,
	"STAT"	tinyint
);


ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[ABTDATA] SET (LOCK_ESCALATION = TABLE);
GO

