/****** Object: Table [dbo].[RAWDATA]   Script Date: 2022-01-10 ���� 5:35:26 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO
CREATE TABLE [dbo].[RAWDATA] (
[SEQ_NUM] int NOT NULL,
[SEQ_TYPE] tinyint NOT NULL,
[POSITION_COUNT] tinyint NULL,
[FILENAME] char(100) NULL)
ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[RAWDATA] SET (LOCK_ESCALATION = TABLE);
GO
