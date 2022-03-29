USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO
CREATE TABLE [dbo].[ABT_POSITION] (
[SEQ_NUM] int NOT NULL,
[SEQ_TYPE] tinyint NOT NULL,
[OP_INIT_ID] int NULL,
[ABTID] int NULL,
[AETID] int NULL,
[TASK_ID] varchar(30) NULL,
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
[SEQ_16] float NULL,
[SEQ_17] float NULL,
[SEQ_18] float NULL,
[SEQ_19] float NULL,
[SEQ_20] float NULL,
[SEQ_21] float NULL,
[SEQ_22] float NULL,
[SEQ_23] float NULL,
[SEQ_24] float NULL,
[SEQ_25] float NULL,
[SEQ_26] float NULL,
[SEQ_27] float NULL,
[SEQ_28] float NULL,
[SEQ_29] float NULL,
[SEQ_30] float NULL,
[SEQ_31] float NULL,
[SEQ_32] float NULL)
ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[ABT_POSITION] SET (LOCK_ESCALATION = TABLE);
GO

