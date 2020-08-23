/****** Object: Table [dbo].[ABTDATA]   Script Date: 2019-04-18 오후 3:22:26 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO

DROP TABLE dbo.ABTDATA

CREATE TABLE [dbo].[ABTDATA] (
[SEQ_NUM] int IDENTITY(1, 1) NOT NULL,
[OP_INIT_ID] int NOT NULL,
[ABTID] int NOT NULL,
[AETID] int NOT NULL,
[FIRST_TIME] datetime NULL,
[LAST_TIME] datetime NULL,
[SIGNAL_TYPE] tinyint NULL,
[NUM_LOB] int NULL,
[BEAM_VALIDITY] int NULL,
[FREQ_TYPE] tinyint NULL,
[FREQ_PATTERN_TYPE] tinyint NULL,
[FREQ_PATTERN_PERIOD_MEAN] float NULL,
[FREQ_PATTERN_PERIOD_MIN] float NULL,
[FREQ_PATTERN_PERIOD_MAX] float NULL,
[FREQ_MEAN] float NULL,
[FREQ_MIN] float NULL,
[FREQ_MAX] float NULL,
[FREQ_POSITION_COUNT] tinyint NULL,
[PRI_TYPE] tinyint NULL,
[PRI_PATTERN_TYPE] tinyint NULL,
[PRI_PATTERN_PERIOD_MEAN] float NULL,
[PRI_PATTERN_PERIOD_MIN] float NULL,
[PRI_PATTERN_PERIOD_MAX] float NULL,
[PRI_MEAN] float NULL,
[PRI_MIN] float NULL,
[PRI_MAX] float NULL,
[PRI_JITTER_RATIO] float NULL,
[PRI_POSITION_COUNT] tinyint NULL,
[PW_MEAN] float NULL,
[PW_MIN] float NULL,
[PW_MAX] float NULL,
[PA_MEAN] float NULL,
[PA_MIN] float NULL,
[PA_MAX] float NULL,
[TOTAL_PDW] int NULL,
[RADAR_NAME] varchar(20) NULL,
[RADARMODE_INDEX] smallint NULL,
[THREAT_INDEX] smallint NULL,
[PE_VALID] smallint NULL,
[PE_LATITUDE] float NULL,
[PE_LONGGITUDE] float NULL,
[PE_CEP] float NULL,
[PE_MAJOR_AXIS] float NULL,
[PE_MINOR_AXIS] float NULL,
[PE_THETA] float NULL,
[PE_DISTANCE] float NULL,
[ALARM_TIME] datetime NULL,
[STAT] tinyint NULL)
ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[ABTDATA] SET (LOCK_ESCALATION = TABLE);
GO

