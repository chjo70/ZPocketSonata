/****** Object: Table [dbo].[LOBDATA]   Script Date: 2019-04-18 오후 3:22:26 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO

DROP TABLE dbo.LOBDATA

CREATE TABLE "LOBDATA" (
	"SEQ_NUM"	integer PRIMARY KEY AUTOINCREMENT,
	"LOBID"	INTEGER NOT NULL,
	"ABTID"	int NOT NULL,
	"AETID"	int NOT NULL,
	"CONTACT_TIME"	datetime,
	"CONTACT_TIME_MS"	int,
	"SIGNAL_TYPE"	tinyint,
	"DOA_MEAN"	float,
	"DOA_MIN"	float,
	"DOA_MAX"	float,
	"DI_RATIO"	int,
	"FREQ_TYPE"	tinyint,
	"FREQ_PATTERN_TYPE"	tinyint,
	"FREQ_PATTERN_PERIOD"	float,
	"FREQ_MEAN"	float,
	"FREQ_MIN"	float,
	"FREQ_MAX"	float,
	"FREQ_POSITION_COUNT"	tinyint,
	"PRI_TYPE"	tinyint,
	"PRI_PATTERN_TYPE"	tinyint,
	"PRI_PATTERN_PERIOD"	float,
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
	"IS_STORED_PDW"	tinyint,
	"NUM_PDW"	smallint,
	"COLLECTOR_ID"	tinyint,
	"RADAR_LATITUDE"	float,
	"RADAR_LONGGITUDE"	float,
	"RADAR_NAME"	varchar(20),
	"RADARMODE_INDEX"	smallint,
	"THREAT_INDEX"	smallint
);

ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[LOBDATA] SET (LOCK_ESCALATION = TABLE);
GO

