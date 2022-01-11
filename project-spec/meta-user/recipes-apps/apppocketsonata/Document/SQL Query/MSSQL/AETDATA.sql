/****** Object: Table [dbo].[AETDATA]   Script Date: 2022-01-10 ���� 5:30:59 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO
CREATE TABLE [dbo].[AETDATA] (
[SEQ_NUM] int NOT NULL,
[OP_INIT_ID] int NOT NULL,
[AETID] int NOT NULL,
[FIRST_TIME] datetime NULL,
[LAST_TIME] datetime NULL,
[PRIMARY_ELNOT] varchar(20) NULL,
[PRIMARY_MODECODE] varchar(20) NULL,
[RADARMODE_NAME] varchar(20) NULL,
[NICK_NAME] varchar(20) NULL,
[FUNC_CODE] varchar(20) NULL,
[PLATFORM_TYPE] varchar(20) NULL,
[RADARMODE_PRIORITY] varchar(20) NULL,
[RADAR_PRIORITY] varchar(20) NULL,
[PIN_NUM] int NULL,
[PLACENAME_KOR] varchar(20) NULL,
[THREAT_FUNC_CODE] varchar(20) NULL,
[THREAT_PRIORITY] varchar(20) NULL,
[RADARMODE_INDEX] int NULL,
[THREAT_INDEX] int NULL,
[VALIDITY] tinyint NULL,
[DOA_MEAN] float NULL,
[DOA_MIN] float NULL,
[DOA_MAX] float NULL,
[DOA_DEV] float NULL,
[FRQ_MEAN] float NULL,
[FRQ_MIN] float NULL,
[FRQ_MAX] float NULL,
[FRQ_DEV] float NULL,
[PRI_MEAN] float NULL,
[PRI_MIN] float NULL,
[PRI_MAX] float NULL,
[PRI_DEV] float NULL,
[PW_MEAN] float NULL,
[PW_MIN] float NULL,
[PW_MAX] float NULL,
[PW_DEV] float NULL,
[PA_MEAN] float NULL,
[PA_MIN] float NULL,
[PA_MAX] float NULL,
[PA_DEV] float NULL,
[PE_VALID] smallint NULL,
[PE_LATITUDE] float NULL,
[PE_LONGGITUDE] float NULL,
[PE_HEIGHT] float NULL,
[PE_CEP] float NULL,
[PE_MAJOR_AXIS] float NULL,
[PE_MINOR_AXIS] float NULL,
[PE_THETA] float NULL,
[PE_DISTANCE] float NULL,
[IDINFO] varchar(12) NULL,
[NUM_OF_LOBS] int NULL,
[NUM_OF_BEAMS] int NULL,
[FINAL_ALARM_TIME] datetime NULL,
[STAT] tinyint NULL)
ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[AETDATA] SET (LOCK_ESCALATION = TABLE);
GO

