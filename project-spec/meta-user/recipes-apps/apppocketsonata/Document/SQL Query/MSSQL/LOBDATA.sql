/****** Object: Table [dbo].[LOBDATA]   Script Date: 2022-01-10 ���� 5:31:49 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO
CREATE TABLE [dbo].[LOBDATA] (
[SEQ_NUM] int NOT NULL,
[OP_INIT_ID] int NOT NULL,
[LOBID] int NOT NULL,
[ABTID] int NOT NULL,
[AETID] int NOT NULL,
[TASK_ID] varchar(30) NOT NULL,
[CONTACT_TIME] datetime NULL,
[CONTACT_TIME_MS] int NULL,
[SIGNAL_TYPE] tinyint NULL,
[DOA_MEAN] float NULL,
[DOA_MIN] float NULL,
[DOA_MAX] float NULL,
[DI_RATIO] int NULL,
[FREQ_TYPE] tinyint NULL,
[FREQ_PATTERN_TYPE] tinyint NULL,
[FREQ_PATTERN_PERIOD] float NULL,
[FREQ_MEAN] float NULL,
[FREQ_MIN] float NULL,
[FREQ_MAX] float NULL,
[FREQ_POSITION_COUNT] tinyint NULL,
[PRI_TYPE] tinyint NULL,
[PRI_PATTERN_TYPE] tinyint NULL,
[PRI_PATTERN_PERIOD] float NULL,
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
[IS_STORED_PDW] tinyint NULL,
[NUM_PDW] smallint NULL,
[COLLECTOR_ID] tinyint NULL,
[RADAR_LATITUDE] float NULL,
[RADAR_LONGGITUDE] float NULL,
[RADAR_NAME] varchar(20) NULL,
[RADARMODE_INDEX] smallint NULL)
ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[LOBDATA] SET (LOCK_ESCALATION = TABLE);
GO

