/****** Object: Table [dbo].[LOB_POSITION]   Script Date: 2019-04-18 오후 3:22:26 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO

DROP TABLE dbo.LOB_POSITION

CREATE TABLE [dbo].[LOB_POSITION] (
[SEQ_NUM] int IDENTITY(1, 1) NOT NULL,
[OP_INIT_ID] int NOT NULL,
[LOBID] int NOT NULL,
[ABTID] int NOT NULL,
[AETID] int NOT NULL,
[TASK_ID] varchar(30) NOT NULL,
[POSITION_COUNT] tinyint NULL,
[SEQ_01] float NULL,
[SEQ_02] float NULL,
[SEQ_03] float NULL,
[SEQ_04] float NULL,
[SEQ_05] float NULL,
[SEQ_06] float NULL,
[SEQ_07] float NULL,
[SEQ_08] float NULL,
[SEQ_09] float NULL,
[SEQ_10] float NULL,
[SEQ_11] float NULL,
[SEQ_12] float NULL,
[SEQ_13] float NULL,
[SEQ_14] float NULL,
[SEQ_15] float NULL,
[SEQ_16] float NULL)
ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[LOB_POSITION] SET (LOCK_ESCALATION = TABLE);
GO


