/****** Object: Table [dbo].[ABT_POSITION]   Script Date: 2019-04-18 오후 3:22:26 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO

DROP TABLE dbo.ABT_POSITION

CREATE TABLE "ABT_POSITION" (
	"SEQ_NUM"	integer PRIMARY KEY AUTOINCREMENT,
	"LOBID"	int NOT NULL,
	"ABTID"	int NOT NULL,
	"AETID"	int NOT NULL,
	"TASK_ID"	varchar(30) NOT NULL,
	"POSITION_COUNT"	tinyint,
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
	"SEQ_32"	float	
);


ON [PRIMARY]
WITH (DATA_COMPRESSION = NONE);
GO
ALTER TABLE [dbo].[ABT_POSITION] SET (LOCK_ESCALATION = TABLE);
GO