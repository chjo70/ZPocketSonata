/* ELINT */
USE [ELINT]
GO

/* ABT_POSITION */
DROP TABLE [dbo].[ABT_POSITION]
GO

/* ABTDATA */
DROP TABLE [dbo].[ABTDATA]
GO

/* LOB_POSITION */
DROP TABLE [dbo].[LOB_POSITION]
GO

/* RADARMODE */
DROP TABLE [dbo].[RADARMODE]
GO

/* RADARMODE_PRI_SEQUENCE */
DROP TABLE [dbo].[RADARMODE_PRI_SEQUENCE]
GO

/* RADARMODE_RF_SEQUENCE */
DROP TABLE [dbo].[RADARMODE_RF_SEQUENCE]
GO

/* THREAT */
DROP TABLE [dbo].[THREAT]
GO

/* AETDATA */
DROP TABLE [dbo].[AETDATA]
GO

/* RAWDATA */
DROP TABLE [dbo].[RAWDATA]
GO

/* LOBDATA */
DROP TABLE [dbo].[LOBDATA]
GO

/* ABT_POSITION */
CREATE TABLE [dbo].[ABT_POSITION] (
	[SEQ_TYPE] [TINYINT] NOT NULL,  /* SEQ_TYPE */
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[LOBID] [int] NOT NULL,  /* LOBID */
	[PDWID] [INT] NOT NULL,  /* PDWID */
	[PLOBID] [INT] NOT NULL,  /* PLOBID */
	[AETID] [int] NOT NULL,  /* AETID */
	[ABTID] [int] NOT NULL,  /* ABTID */
	[POSITION_COUNT] [tinyint],  /* POSITION_COUNT */
	[SEQ_01] [float],  /* SEQ_01 */
	[SEQ_02] [float],  /* SEQ_02 */
	[SEQ_03] [float],  /* SEQ_03 */
	[SEQ_04] [float],  /* SEQ_04 */
	[SEQ_05] [float],  /* SEQ_05 */
	[SEQ_06] [float],  /* SEQ_06 */
	[SEQ_07] [float],  /* SEQ_07 */
	[SEQ_08] [float],  /* SEQ_08 */
	[SEQ_09] [float],  /* SEQ_09 */
	[SEQ_10] [float],  /* SEQ_10 */
	[SEQ_11] [float],  /* SEQ_11 */
	[SEQ_12] [float],  /* SEQ_12 */
	[SEQ_13] [float],  /* SEQ_13 */
	[SEQ_14] [float],  /* SEQ_14 */
	[SEQ_15] [float],  /* SEQ_15 */
	[SEQ_16] [float],  /* SEQ_16 */
	[SEQ_17] [float],  /* SEQ_17 */
	[SEQ_18] [float],  /* SEQ_18 */
	[SEQ_19] [float],  /* SEQ_19 */
	[SEQ_20] [float],  /* SEQ_20 */
	[SEQ_21] [float],  /* SEQ_21 */
	[SEQ_22] [float],  /* SEQ_22 */
	[SEQ_23] [float],  /* SEQ_23 */
	[SEQ_24] [float],  /* SEQ_24 */
	[SEQ_25] [float],  /* SEQ_25 */
	[SEQ_26] [float],  /* SEQ_26 */
	[SEQ_27] [float],  /* SEQ_27 */
	[SEQ_28] [float],  /* SEQ_28 */
	[SEQ_29] [float],  /* SEQ_29 */
	[SEQ_30] [float],  /* SEQ_30 */
	[SEQ_31] [float],  /* SEQ_31 */
	[SEQ_32] [float] /* SEQ_32 */
)
	ON [PRIMARY]
GO

/* ABT_POSITION 기본키 */
ALTER TABLE [dbo].[ABT_POSITION]
	ADD
		CONSTRAINT [PK_ABT_POSITION]
		PRIMARY KEY NONCLUSTERED (
			[SEQ_TYPE] ASC, 
			[OP_INIT_ID] ASC, 
			[LOBID] ASC
		)
GO

/* ABT_POSITION */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABT_POSITION', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION'
GO

/* SEQ_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_TYPE'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* LOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* PDWID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDWID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* PLOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* AETID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AETID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* ABTID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* POSITION_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'POSITION_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'POSITION_COUNT'
GO

/* SEQ_01 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_01', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_01'
GO

/* SEQ_02 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_02', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_02'
GO

/* SEQ_03 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_03', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_03'
GO

/* SEQ_04 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_04', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_04'
GO

/* SEQ_05 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_05', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_05'
GO

/* SEQ_06 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_06', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_06'
GO

/* SEQ_07 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_07', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_07'
GO

/* SEQ_08 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_08', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_08'
GO

/* SEQ_09 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_09', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_09'
GO

/* SEQ_10 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_10', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_10'
GO

/* SEQ_11 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_11', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_11'
GO

/* SEQ_12 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_12', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_12'
GO

/* SEQ_13 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_13', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_13'
GO

/* SEQ_14 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_14', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_14'
GO

/* SEQ_15 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_15', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_15'
GO

/* SEQ_16 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_16', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_16'
GO

/* SEQ_17 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_17', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_17'
GO

/* SEQ_18 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_18', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_18'
GO

/* SEQ_19 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_19', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_19'
GO

/* SEQ_20 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_20', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_20'
GO

/* SEQ_21 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_21', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_21'
GO

/* SEQ_22 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_22', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_22'
GO

/* SEQ_23 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_23', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_23'
GO

/* SEQ_24 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_24', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_24'
GO

/* SEQ_25 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_25', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_25'
GO

/* SEQ_26 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_26', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_26'
GO

/* SEQ_27 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_27', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_27'
GO

/* SEQ_28 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_28', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_28'
GO

/* SEQ_29 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_29', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_29'
GO

/* SEQ_30 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_30', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_30'
GO

/* SEQ_31 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_31', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_31'
GO

/* SEQ_32 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_32', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_32'
GO

/* ABT_POSITION 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABT_POSITION 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_ABT_POSITION'
GO

/* ABT_POSITION 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABT_POSITION 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'INDEX', @level2name=N'PK_ABT_POSITION'
GO

/* ABTDATA */
CREATE TABLE [dbo].[ABTDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDWID */
	[PLOBID] [INT] NOT NULL,  /* PLOBID */
	[LOBID] [int] NOT NULL,  /* LOBID */
	[AETID] [int] NOT NULL,  /* AETID */
	[ABTID] [int] NOT NULL,  /* ABTID */
	[FIRST_TIME] [datetime],  /* FIRST_TIME */
	[LAST_TIME] [datetime],  /* LAST_TIME */
	[SIGNAL_TYPE] [tinyint],  /* SIGNAL_TYPE */
	[NUM_LOB] [int],  /* NUM_LOB */
	[BEAM_VALIDITY] [int],  /* BEAM_VALIDITY */
	[FREQ_TYPE] [tinyint],  /* FREQ_TYPE */
	[FREQ_PATTERN_TYPE] [tinyint],  /* FREQ_PATTERN_TYPE */
	[FREQ_PATTERN_PERIOD_MEAN] [float],  /* FREQ_PATTERN_PERIOD_MEAN */
	[FREQ_PATTERN_PERIOD_MIN] [float],  /* FREQ_PATTERN_PERIOD_MIN */
	[FREQ_PATTERN_PERIOD_MAX] [float],  /* FREQ_PATTERN_PERIOD_MAX */
	[FREQ_MEAN] [float],  /* FREQ_MEAN */
	[FREQ_MIN] [float],  /* FREQ_MIN */
	[FREQ_MAX] [float],  /* FREQ_MAX */
	[FREQ_POSITION_COUNT] [TINYINT],  /* FREQ_POSITION_COUNT */
	[FREQ_ELEMENT_COUNT] [TINYINT],  /* FREQ_ELEMENT_COUNT */
	[PRI_TYPE] [TINYINT],  /* PRI_TYPE */
	[PRI_PATTERN_TYPE] [TINYINT],  /* PRI_PATTERN_TYPE */
	[PRI_PATTERN_PERIOD_MEAN] [float],  /* PRI_PATTERN_PERIOD_MEAN */
	[PRI_PATTERN_PERIOD_MIN] [float],  /* PRI_PATTERN_PERIOD_MIN */
	[PRI_PATTERN_PERIOD_MAX] [float],  /* PRI_PATTERN_PERIOD_MAX */
	[PRI_MEAN] [float],  /* PRI_MEAN */
	[PRI_MIN] [float],  /* PRI_MIN */
	[PRI_MAX] [float],  /* PRI_MAX */
	[PRI_JITTER_RATIO] [float],  /* PRI_JITTER_RATIO */
	[PRI_POSITION_COUNT] [TINYINT],  /* PRI_POSITION_COUNT */
	[PRI_ELEMENT_COUNT] [TINYINT],  /* PRI_ELEMENT_COUNT */
	[PW_MEAN] [float],  /* PW_MEAN */
	[PW_MIN] [float],  /* PW_MIN */
	[PW_MAX] [float],  /* PW_MAX */
	[PA_MEAN] [float],  /* PA_MEAN */
	[PA_MIN] [float],  /* PA_MIN */
	[PA_MAX] [float],  /* PA_MAX */
	[TOTAL_PDW] [int],  /* TOTAL_PDW */
	[RADARMODE_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* RADARMODE_NAME */
	[RADARMODE_INDEX] [smallint],  /* RADARMODE_INDEX */
	[THREAT_INDEX] [smallint],  /* THREAT_INDEX */
	[PE_VALID] [TINYINT],  /* PE_VALID */
	[PE_LATITUDE] [float],  /* PE_LATITUDE */
	[PE_LONGITUDE] [float],  /* PE_LONGITUDE */
	[PE_CEP] [float],  /* PE_CEP */
	[PE_MAJOR_AXIS] [float],  /* PE_MAJOR_AXIS */
	[PE_MINOR_AXIS] [float],  /* PE_MINOR_AXIS */
	[PE_THETA] [float],  /* PE_THETA */
	[PE_DISTANCE] [float],  /* PE_DISTANCE */
	[ALARM_TIME] [datetime],  /* ALARM_TIME */
	[STAT] [TINYINT] /* STAT */
)
	ON [PRIMARY]
GO

/* ABTDATA 기본키 */
ALTER TABLE [dbo].[ABTDATA]
	ADD
		CONSTRAINT [PK_ABTDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC, 
			[LOBID] ASC
		)
GO

/* ABTDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABT 데이터 입니다.', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDWID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDWID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* PLOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* AETID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AETID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* ABTID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* FIRST_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FIRST_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FIRST_TIME'
GO

/* LAST_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LAST_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'LAST_TIME'
GO

/* SIGNAL_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SIGNAL_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* NUM_LOB */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'NUM_LOB', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_LOB'
GO

/* BEAM_VALIDITY */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'BEAM_VALIDITY', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'BEAM_VALIDITY'
GO

/* FREQ_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_TYPE'
GO

/* FREQ_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_TYPE'
GO

/* FREQ_PATTERN_PERIOD_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_PERIOD_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD_MEAN'
GO

/* FREQ_PATTERN_PERIOD_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_PERIOD_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD_MIN'
GO

/* FREQ_PATTERN_PERIOD_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_PERIOD_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD_MAX'
GO

/* FREQ_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* FREQ_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* FREQ_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* FREQ_POSITION_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_POSITION_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_POSITION_COUNT'
GO

/* FREQ_ELEMENT_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_ELEMENT_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_ELEMENT_COUNT'
GO

/* PRI_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI_PATTERN_PERIOD_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MEAN'
GO

/* PRI_PATTERN_PERIOD_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MIN'
GO

/* PRI_PATTERN_PERIOD_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MAX'
GO

/* PRI_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI_JITTER_RATIO */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_JITTER_RATIO', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_JITTER_RATIO'
GO

/* PRI_POSITION_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_POSITION_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_POSITION_COUNT'
GO

/* PRI_ELEMENT_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_ELEMENT_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_ELEMENT_COUNT'
GO

/* PW_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* PW_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* PW_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* PA_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* PA_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* PA_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* TOTAL_PDW */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'TOTAL_PDW', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'TOTAL_PDW'
GO

/* RADARMODE_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* RADARMODE_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* THREAT_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* PE_VALID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_VALID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_VALID'
GO

/* PE_LATITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_LATITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LATITUDE'
GO

/* PE_LONGITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_LONGITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LONGITUDE'
GO

/* PE_CEP */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_CEP', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_CEP'
GO

/* PE_MAJOR_AXIS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_MAJOR_AXIS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MAJOR_AXIS'
GO

/* PE_MINOR_AXIS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_MINOR_AXIS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MINOR_AXIS'
GO

/* PE_THETA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_THETA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_THETA'
GO

/* PE_DISTANCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_DISTANCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_DISTANCE'
GO

/* ALARM_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ALARM_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'ALARM_TIME'
GO

/* STAT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'STAT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'STAT'
GO

/* ABTDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_ABTDATA'
GO

/* ABTDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'INDEX', @level2name=N'PK_ABTDATA'
GO

/* LOB_POSITION */
CREATE TABLE [dbo].[LOB_POSITION] (
	[SEQ_TYPE] [TINYINT] NOT NULL,  /* SEQ_TYPE */
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[LOBID] [int] NOT NULL,  /* LOBID */
	[PDWID] [INT] NOT NULL,  /* PDWID */
	[PLOBID] [INT] NOT NULL,  /* PLOBID */
	[AETID] [int] NOT NULL,  /* AETID */
	[ABTID] [int] NOT NULL,  /* ABTID */
	[POSITION_COUNT] [tinyint],  /* POSITION_COUNT */
	[SEQ_01] [float],  /* SEQ_01 */
	[SEQ_02] [float],  /* SEQ_02 */
	[SEQ_03] [float],  /* SEQ_03 */
	[SEQ_04] [float],  /* SEQ_04 */
	[SEQ_05] [float],  /* SEQ_05 */
	[SEQ_06] [float],  /* SEQ_06 */
	[SEQ_07] [float],  /* SEQ_07 */
	[SEQ_08] [float],  /* SEQ_08 */
	[SEQ_09] [float],  /* SEQ_09 */
	[SEQ_10] [float],  /* SEQ_10 */
	[SEQ_11] [float],  /* SEQ_11 */
	[SEQ_12] [float],  /* SEQ_12 */
	[SEQ_13] [float],  /* SEQ_13 */
	[SEQ_14] [float],  /* SEQ_14 */
	[SEQ_15] [float],  /* SEQ_15 */
	[SEQ_16] [float],  /* SEQ_16 */
	[SEQ_17] [float],  /* SEQ_17 */
	[SEQ_18] [float],  /* SEQ_18 */
	[SEQ_19] [float],  /* SEQ_19 */
	[SEQ_20] [float],  /* SEQ_20 */
	[SEQ_21] [float],  /* SEQ_21 */
	[SEQ_22] [float],  /* SEQ_22 */
	[SEQ_23] [float],  /* SEQ_23 */
	[SEQ_24] [float],  /* SEQ_24 */
	[SEQ_25] [float],  /* SEQ_25 */
	[SEQ_26] [float],  /* SEQ_26 */
	[SEQ_27] [float],  /* SEQ_27 */
	[SEQ_28] [float],  /* SEQ_28 */
	[SEQ_29] [float],  /* SEQ_29 */
	[SEQ_30] [float],  /* SEQ_30 */
	[SEQ_31] [float],  /* SEQ_31 */
	[SEQ_32] [float] /* SEQ_32 */
)
	ON [PRIMARY]
GO

/* LOB_POSITION 기본키 */
ALTER TABLE [dbo].[LOB_POSITION]
	ADD
		CONSTRAINT [PK_LOB_POSITION]
		PRIMARY KEY NONCLUSTERED (
			[SEQ_TYPE] ASC, 
			[OP_INIT_ID] ASC, 
			[LOBID] ASC
		)
GO

/* LOB_POSITION */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB_POSITION', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION'
GO

/* SEQ_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_TYPE'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* LOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* PDWID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDWID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* PLOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* AETID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AETID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* ABTID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* POSITION_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'POSITION_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'POSITION_COUNT'
GO

/* SEQ_01 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_01', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_01'
GO

/* SEQ_02 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_02', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_02'
GO

/* SEQ_03 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_03', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_03'
GO

/* SEQ_04 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_04', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_04'
GO

/* SEQ_05 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_05', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_05'
GO

/* SEQ_06 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_06', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_06'
GO

/* SEQ_07 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_07', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_07'
GO

/* SEQ_08 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_08', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_08'
GO

/* SEQ_09 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_09', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_09'
GO

/* SEQ_10 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_10', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_10'
GO

/* SEQ_11 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_11', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_11'
GO

/* SEQ_12 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_12', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_12'
GO

/* SEQ_13 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_13', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_13'
GO

/* SEQ_14 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_14', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_14'
GO

/* SEQ_15 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_15', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_15'
GO

/* SEQ_16 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_16', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_16'
GO

/* SEQ_17 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_17', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_17'
GO

/* SEQ_18 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_18', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_18'
GO

/* SEQ_19 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_19', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_19'
GO

/* SEQ_20 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_20', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_20'
GO

/* SEQ_21 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_21', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_21'
GO

/* SEQ_22 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_22', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_22'
GO

/* SEQ_23 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_23', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_23'
GO

/* SEQ_24 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_24', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_24'
GO

/* SEQ_25 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_25', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_25'
GO

/* SEQ_26 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_26', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_26'
GO

/* SEQ_27 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_27', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_27'
GO

/* SEQ_28 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_28', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_28'
GO

/* SEQ_29 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_29', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_29'
GO

/* SEQ_30 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_30', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_30'
GO

/* SEQ_31 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_31', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_31'
GO

/* SEQ_32 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SEQ_32', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_32'
GO

/* LOB_POSITION 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB_POSITION 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_LOB_POSITION'
GO

/* LOB_POSITION 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB_POSITION 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'INDEX', @level2name=N'PK_LOB_POSITION'
GO

/* RADARMODE */
CREATE TABLE [dbo].[RADARMODE] (
	[RADAR_MODE_INDEX] [int] NOT NULL,  /* RADAR_MODE_INDEX */
	[RADAR_MODE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS NOT NULL,  /* RADAR_MODE_NAME */
	[DATE_CREATED] [datetime],  /* DATE_CREATED */
	[DATE_LAST_UPDATED] [datetime],  /* DATE_LAST_UPDATED */
	[DATE_FIRST_SEEN] [datetime],  /* DATE_FIRST_SEEN */
	[DATE_LAST_SEEN] [datetime],  /* DATE_LAST_SEEN */
	[PLATFORM] [tinyint],  /* PLATFORM */
	[SIGNAL_TYPE] [tinyint],  /* SIGNAL_TYPE */
	[RF_TYPE] [tinyint] NOT NULL,  /* RF_TYPE */
	[RF_TYPICAL_MIN] [float],  /* RF_TYPICAL_MIN */
	[RF_TYPICAL_MAX] [float],  /* RF_TYPICAL_MAX */
	[RF_PATTERN_TYPE] [tinyint],  /* RF_PATTERN_TYPE */
	[RF_NUM_POSITIONS] [tinyint],  /* RF_NUM_POSITIONS */
	[RF_PATTERN_PERIOD_MIN] [float],  /* RF_PATTERN_PERIOD_MIN */
	[RF_PATTERN_PERIOD_MAX] [float],  /* RF_PATTERN_PERIOD_MAX */
	[PRI_TYPE] [tinyint] NOT NULL,  /* PRI_TYPE */
	[PRI_TYPICAL_MIN] [float],  /* PRI_TYPICAL_MIN */
	[PRI_TYPICAL_MAX] [float],  /* PRI_TYPICAL_MAX */
	[PRI_PATTERN_TYPE] [tinyint],  /* PRI_PATTERN_TYPE */
	[PRI_NUM_POSITIONS] [tinyint],  /* PRI_NUM_POSITIONS */
	[PRI_PATTERN_PERIOD_MIN] [float],  /* PRI_PATTERN_PERIOD_MIN */
	[PRI_PATTERN_PERIOD_MAX] [float],  /* PRI_PATTERN_PERIOD_MAX */
	[PW_TYPICAL_MIN] [float],  /* PW_TYPICAL_MIN */
	[PW_TYPICAL_MAX] [float],  /* PW_TYPICAL_MAX */
	[VALIDATION] [tinyint] /* VALIDATION */
)
	ON [PRIMARY]
GO

/* PK__RADARMOD__5D8D6E820428B272 */
ALTER TABLE [dbo].[RADARMODE]
	ADD
		CONSTRAINT [PK__RADARMOD__5D8D6E820428B272]
		PRIMARY KEY CLUSTERED (
			[RADAR_MODE_INDEX] ASC, 
			[RADAR_MODE_NAME] ASC
		)
		WITH (
			PAD_INDEX = OFF, 
			FILLFACTOR = 100, 
			IGNORE_DUP_KEY = OFF, 
			ALLOW_ROW_LOCKS = ON, 
			ALLOW_PAGE_LOCKS = ON
		)
		ON [PRIMARY]
GO

/* RADARMODE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE'
GO

/* RADAR_MODE_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_MODE_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADAR_MODE_INDEX'
GO

/* RADAR_MODE_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_MODE_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADAR_MODE_NAME'
GO

/* DATE_CREATED */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_CREATED', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_CREATED'
GO

/* DATE_LAST_UPDATED */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_LAST_UPDATED', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_UPDATED'
GO

/* DATE_FIRST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_FIRST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* DATE_LAST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_LAST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* PLATFORM */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLATFORM', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM'
GO

/* SIGNAL_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SIGNAL_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* RF_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPE'
GO

/* RF_TYPICAL_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_TYPICAL_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MIN'
GO

/* RF_TYPICAL_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_TYPICAL_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MAX'
GO

/* RF_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_TYPE'
GO

/* RF_NUM_POSITIONS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_NUM_POSITIONS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_NUM_POSITIONS'
GO

/* RF_PATTERN_PERIOD_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_PATTERN_PERIOD_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MIN'
GO

/* RF_PATTERN_PERIOD_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_PATTERN_PERIOD_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MAX'
GO

/* PRI_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI_TYPICAL_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_TYPICAL_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MIN'
GO

/* PRI_TYPICAL_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_TYPICAL_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MAX'
GO

/* PRI_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI_NUM_POSITIONS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_NUM_POSITIONS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_NUM_POSITIONS'
GO

/* PRI_PATTERN_PERIOD_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MIN'
GO

/* PRI_PATTERN_PERIOD_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MAX'
GO

/* PW_TYPICAL_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_TYPICAL_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MIN'
GO

/* PW_TYPICAL_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_TYPICAL_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MAX'
GO

/* VALIDATION */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'VALIDATION', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'VALIDATION'
GO

/* PK__RADARMOD__5D8D6E820428B272 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__5D8D6E820428B272', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__RADARMOD__5D8D6E820428B272'
GO

/* PK__RADARMOD__5D8D6E820428B272 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__5D8D6E820428B272', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'INDEX', @level2name=N'PK__RADARMOD__5D8D6E820428B272'
GO

/* RADARMODE_PRI_SEQUENCE */
CREATE TABLE [dbo].[RADARMODE_PRI_SEQUENCE] (
	[RADAR_MODE_INDEX] [int] NOT NULL,  /* RADAR_MODE_INDEX */
	[PRI_SEQ_ID] [int] NOT NULL,  /* PRI_SEQ_ID */
	[PRI_SEQ_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* PRI_SEQ_NAME */
	[PRI_MIN] [float],  /* PRI_MIN */
	[PRI_MAX] [float] /* PRI_MAX */
)
	ON [PRIMARY]
GO

/* PK__RADARMOD__F56ABC074ADECD96 */
ALTER TABLE [dbo].[RADARMODE_PRI_SEQUENCE]
	ADD
		CONSTRAINT [PK__RADARMOD__F56ABC074ADECD96]
		PRIMARY KEY CLUSTERED (
			[RADAR_MODE_INDEX] ASC, 
			[PRI_SEQ_ID] ASC
		)
		WITH (
			PAD_INDEX = OFF, 
			FILLFACTOR = 100, 
			IGNORE_DUP_KEY = OFF, 
			ALLOW_ROW_LOCKS = ON, 
			ALLOW_PAGE_LOCKS = ON
		)
		ON [PRIMARY]
GO

/* RADARMODE_PRI_SEQUENCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_PRI_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE'
GO

/* RADAR_MODE_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_MODE_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RADAR_MODE_INDEX'
GO

/* PRI_SEQ_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_SEQ_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_ID'
GO

/* PRI_SEQ_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_SEQ_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_NAME'
GO

/* PRI_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PK__RADARMOD__F56ABC074ADECD96 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F56ABC074ADECD96', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__RADARMOD__F56ABC074ADECD96'
GO

/* PK__RADARMOD__F56ABC074ADECD96 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F56ABC074ADECD96', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'INDEX', @level2name=N'PK__RADARMOD__F56ABC074ADECD96'
GO

/* RADARMODE_RF_SEQUENCE */
CREATE TABLE [dbo].[RADARMODE_RF_SEQUENCE] (
	[RADAR_MODE_INDEX] [int] NOT NULL,  /* RADAR_MODE_INDEX */
	[RF_SEQ_ID] [int] NOT NULL,  /* RF_SEQ_ID */
	[RF_SEQ_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* RF_SEQ_NAME */
	[RF_MIN] [float],  /* RF_MIN */
	[RF_MAX] [float] /* RF_MAX */
)
	ON [PRIMARY]
GO

/* PK__RADARMOD__F4541D42173876EA */
ALTER TABLE [dbo].[RADARMODE_RF_SEQUENCE]
	ADD
		CONSTRAINT [PK__RADARMOD__F4541D42173876EA]
		PRIMARY KEY CLUSTERED (
			[RADAR_MODE_INDEX] ASC, 
			[RF_SEQ_ID] ASC
		)
		WITH (
			PAD_INDEX = OFF, 
			FILLFACTOR = 100, 
			IGNORE_DUP_KEY = OFF, 
			ALLOW_ROW_LOCKS = ON, 
			ALLOW_PAGE_LOCKS = ON
		)
		ON [PRIMARY]
GO

/* RADARMODE_RF_SEQUENCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_RF_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE'
GO

/* RADAR_MODE_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_MODE_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RADAR_MODE_INDEX'
GO

/* RF_SEQ_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_SEQ_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_SEQ_ID'
GO

/* RF_SEQ_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_SEQ_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_SEQ_NAME'
GO

/* RF_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_MIN'
GO

/* RF_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_MAX'
GO

/* PK__RADARMOD__F4541D42173876EA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F4541D42173876EA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__RADARMOD__F4541D42173876EA'
GO

/* PK__RADARMOD__F4541D42173876EA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F4541D42173876EA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'INDEX', @level2name=N'PK__RADARMOD__F4541D42173876EA'
GO

/* THREAT */
CREATE TABLE [dbo].[THREAT] (
	[THREAT_INDEX] [int] NOT NULL,  /* THREAT_INDEX */
	[RADAR_MODE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS NOT NULL,  /* RADAR_MODE_NAME */
	[THREAT_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS,  /* THREAT_NAME */
	[LATITUDE] [float],  /* LATITUDE */
	[LONGITUDE] [float],  /* LONGITUDE */
	[SITE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS,  /* SITE_NAME */
	[THREAT_PLATFORM] [tinyint],  /* THREAT_PLATFORM */
	[DATE_CREATED] [datetime],  /* DATE_CREATED */
	[DATE_FIRST_SEEN] [datetime],  /* DATE_FIRST_SEEN */
	[DATE_LAST_SEEN] [datetime],  /* DATE_LAST_SEEN */
	[ID_RANGE] [float] /* ID_RANGE */
)
	ON [PRIMARY]
GO

/* PK__THREAT__DD4AC47457A20A5B */
ALTER TABLE [dbo].[THREAT]
	ADD
		CONSTRAINT [PK__THREAT__DD4AC47457A20A5B]
		PRIMARY KEY CLUSTERED (
			[THREAT_INDEX] ASC, 
			[RADAR_MODE_NAME] ASC
		)
		WITH (
			PAD_INDEX = OFF, 
			FILLFACTOR = 100, 
			IGNORE_DUP_KEY = OFF, 
			ALLOW_ROW_LOCKS = ON, 
			ALLOW_PAGE_LOCKS = ON
		)
		ON [PRIMARY]
GO

/* THREAT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT'
GO

/* THREAT_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* RADAR_MODE_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_MODE_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'RADAR_MODE_NAME'
GO

/* THREAT_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_NAME'
GO

/* LATITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LATITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LATITUDE'
GO

/* LONGITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LONGITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LONGITUDE'
GO

/* SITE_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SITE_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'SITE_NAME'
GO

/* THREAT_PLATFORM */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT_PLATFORM', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PLATFORM'
GO

/* DATE_CREATED */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_CREATED', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_CREATED'
GO

/* DATE_FIRST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_FIRST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* DATE_LAST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_LAST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* ID_RANGE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ID_RANGE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'ID_RANGE'
GO

/* PK__THREAT__DD4AC47457A20A5B */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__THREAT__DD4AC47457A20A5B', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__THREAT__DD4AC47457A20A5B'
GO

/* PK__THREAT__DD4AC47457A20A5B */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__THREAT__DD4AC47457A20A5B', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'INDEX', @level2name=N'PK__THREAT__DD4AC47457A20A5B'
GO

/* AETDATA */
CREATE TABLE [dbo].[AETDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDWID */
	[PLOBID] [INT] NOT NULL,  /* PLOBID */
	[LOBID] [int] NOT NULL,  /* LOBID */
	[AETID] [int] NOT NULL,  /* AETID */
	[ABTID] [int] NOT NULL,  /* ABTID */
	[FIRST_TIME] [datetime],  /* FIRST_TIME */
	[LAST_TIME] [datetime],  /* LAST_TIME */
	[PRIMARY_ELNOT] [varchar](20),  /* PRIMARY_ELNOT */
	[PRIMARY_MODECODE] [varchar](20),  /* PRIMARY_MODECODE */
	[RADARMODE_NAME] [varchar](20),  /* RADARMODE_NAME */
	[NICK_NAME] [varchar](20),  /* NICK_NAME */
	[FUNC_CODE] [varchar](20),  /* FUNC_CODE */
	[PLATFORM_TYPE] [varchar](20),  /* PLATFORM_TYPE */
	[RADARMODE_PRIORITY] [varchar](20),  /* RADARMODE_PRIORITY */
	[RADAR_PRIORITY] [varchar](20),  /* RADAR_PRIORITY */
	[PIN_NUM] [INT],  /* PIN_NUM */
	[PLACENAME_KOR] [varchar](20),  /* PLACENAME_KOR */
	[THREAT_FUNC_CODE] [varchar](20),  /* THREAT_FUNC_CODE */
	[THREAT_PRIORITY] [varchar](20),  /* THREAT_PRIORITY */
	[RADARMODE_INDEX] [int],  /* RADARMODE_INDEX */
	[THREAT_INDEX] [int],  /* THREAT_INDEX */
	[VALIDITY] [tinyint],  /* VALIDITY */
	[DOA_MEAN] [float],  /* DOA_MEAN */
	[DOA_MIN] [float],  /* DOA_MIN */
	[DOA_MAX] [float],  /* DOA_MAX */
	[DOA_DEV] [float],  /* DOA_DEV */
	[FRQ_MEAN] [float],  /* FRQ_MEAN */
	[FRQ_MIN] [float],  /* FRQ_MIN */
	[FRQ_MAX] [float],  /* FRQ_MAX */
	[FRQ_DEV] [float],  /* FRQ_DEV */
	[PRI_MEAN] [float],  /* PRI_MEAN */
	[PRI_MIN] [float],  /* PRI_MIN */
	[PRI_MAX] [float],  /* PRI_MAX */
	[PRI_DEV] [float],  /* PRI_DEV */
	[PW_MEAN] [float],  /* PW_MEAN */
	[PW_MIN] [float],  /* PW_MIN */
	[PW_MAX] [float],  /* PW_MAX */
	[PW_DEV] [float],  /* PW_DEV */
	[PA_MEAN] [float],  /* PA_MEAN */
	[PA_MIN] [float],  /* PA_MIN */
	[PA_MAX] [float],  /* PA_MAX */
	[PA_DEV] [float],  /* PA_DEV */
	[PE_VALID] [smallint],  /* PE_VALID */
	[PE_LATITUDE] [float],  /* PE_LATITUDE */
	[PE_LONGITUDE] [float],  /* PE_LONGITUDE */
	[PE_HEIGHT] [float],  /* PE_HEIGHT */
	[PE_CEP] [float],  /* PE_CEP */
	[PE_MAJOR_AXIS] [float],  /* PE_MAJOR_AXIS */
	[PE_MINOR_AXIS] [float],  /* PE_MINOR_AXIS */
	[PE_THETA] [float],  /* PE_THETA */
	[PE_DISTANCE] [float],  /* PE_DISTANCE */
	[STAT] [tinyint],  /* STAT */
	[NUM_OF_BEAMS] [int],  /* NUM_OF_BEAMS */
	[NUM_OF_LOBS] [int],  /* NUM_OF_LOBS */
	[IDINFO] [varchar](12),  /* IDINFO */
	[FINAL_ALARM_TIME] [datetime] /* FINAL_ALARM_TIME */
)
GO

/* AETDATA 기본키 */
ALTER TABLE [dbo].[AETDATA]
	ADD
		CONSTRAINT [PK_AETDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC, 
			[LOBID] ASC
		)
GO

/* AETDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AET 데이터 입니다.', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDWID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDWID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* PLOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* AETID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AETID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* ABTID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* FIRST_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FIRST_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FIRST_TIME'
GO

/* LAST_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LAST_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'LAST_TIME'
GO

/* PRIMARY_ELNOT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRIMARY_ELNOT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRIMARY_ELNOT'
GO

/* PRIMARY_MODECODE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRIMARY_MODECODE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRIMARY_MODECODE'
GO

/* RADARMODE_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* NICK_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'NICK_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NICK_NAME'
GO

/* FUNC_CODE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FUNC_CODE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FUNC_CODE'
GO

/* PLATFORM_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLATFORM_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM_TYPE'
GO

/* RADARMODE_PRIORITY */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_PRIORITY', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_PRIORITY'
GO

/* RADAR_PRIORITY */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_PRIORITY', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADAR_PRIORITY'
GO

/* PIN_NUM */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PIN_NUM', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PIN_NUM'
GO

/* PLACENAME_KOR */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLACENAME_KOR', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLACENAME_KOR'
GO

/* THREAT_FUNC_CODE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT_FUNC_CODE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_FUNC_CODE'
GO

/* THREAT_PRIORITY */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT_PRIORITY', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PRIORITY'
GO

/* RADARMODE_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* THREAT_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* VALIDITY */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'VALIDITY', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'VALIDITY'
GO

/* DOA_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DOA_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MEAN'
GO

/* DOA_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DOA_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MIN'
GO

/* DOA_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DOA_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MAX'
GO

/* DOA_DEV */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DOA_DEV', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_DEV'
GO

/* FRQ_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FRQ_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FRQ_MEAN'
GO

/* FRQ_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FRQ_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FRQ_MIN'
GO

/* FRQ_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FRQ_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FRQ_MAX'
GO

/* FRQ_DEV */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FRQ_DEV', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FRQ_DEV'
GO

/* PRI_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI_DEV */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_DEV', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_DEV'
GO

/* PW_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* PW_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* PW_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* PW_DEV */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_DEV', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_DEV'
GO

/* PA_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* PA_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* PA_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* PA_DEV */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_DEV', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_DEV'
GO

/* PE_VALID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_VALID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_VALID'
GO

/* PE_LATITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_LATITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LATITUDE'
GO

/* PE_LONGITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_LONGITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LONGITUDE'
GO

/* PE_HEIGHT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_HEIGHT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_HEIGHT'
GO

/* PE_CEP */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_CEP', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_CEP'
GO

/* PE_MAJOR_AXIS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_MAJOR_AXIS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MAJOR_AXIS'
GO

/* PE_MINOR_AXIS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_MINOR_AXIS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MINOR_AXIS'
GO

/* PE_THETA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_THETA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_THETA'
GO

/* PE_DISTANCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_DISTANCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_DISTANCE'
GO

/* STAT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'STAT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'STAT'
GO

/* NUM_OF_BEAMS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'NUM_OF_BEAMS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_OF_BEAMS'
GO

/* NUM_OF_LOBS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'NUM_OF_LOBS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_OF_LOBS'
GO

/* IDINFO */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'IDINFO', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'IDINFO'
GO

/* FINAL_ALARM_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FINAL_ALARM_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FINAL_ALARM_TIME'
GO

/* AETDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AETDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_AETDATA'
GO

/* AETDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AETDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'INDEX', @level2name=N'PK_AETDATA'
GO

/* RAWDATA */
CREATE TABLE [dbo].[RAWDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDWID */
	[PLOBID] [INT] NOT NULL,  /* PLOBID */
	[TASK_ID] [CHAR](30),  /* TASK_ID */
	[CREATE_TIME] [DATETIME],  /* CREATE_TIME */
	[CREATE_TIME_MS] [TINYINT],  /* CREATE_TIME_MS */
	[COUNTOFDATA] [TINYINT],  /* COUNTOFDATA */
	[FILENAME] [char](100),  /* FILENAME */
	[DATA_TYPE] [TINYINT] /* DATA_TYPE */
)
GO

/* RAWDATA 기본키 */
ALTER TABLE [dbo].[RAWDATA]
	ADD
		CONSTRAINT [PK_RAWDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC
		)
GO

/* RAWDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집 데이터 입니다.', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDWID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDWID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* PLOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* TASK_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'TASK_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'TASK_ID'
GO

/* CREATE_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'CREATE_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'CREATE_TIME'
GO

/* CREATE_TIME_MS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'CREATE_TIME_MS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'CREATE_TIME_MS'
GO

/* COUNTOFDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'COUNTOFDATA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'COUNTOFDATA'
GO

/* FILENAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FILENAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'FILENAME'
GO

/* DATA_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATA_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'DATA_TYPE'
GO

/* RAWDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RAWDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_RAWDATA'
GO

/* RAWDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RAWDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'INDEX', @level2name=N'PK_RAWDATA'
GO

/* LOBDATA */
CREATE TABLE [dbo].[LOBDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDWID */
	[PLOBID] [INT] NOT NULL,  /* PLOBID */
	[LOBID] [int] NOT NULL,  /* LOBID */
	[AETID] [int] NOT NULL,  /* AETID */
	[ABTID] [int] NOT NULL,  /* ABTID */
	[TASK_ID] [varchar](30) NOT NULL,  /* TASK_ID */
	[CONTACT_TIME] [datetime],  /* CONTACT_TIME */
	[CONTACT_TIME_MS] [int],  /* CONTACT_TIME_MS */
	[SIGNAL_TYPE] [tinyint],  /* SIGNAL_TYPE */
	[DOA_MEAN] [float],  /* DOA_MEAN */
	[DOA_MIN] [float],  /* DOA_MIN */
	[DOA_MAX] [float],  /* DOA_MAX */
	[DI_RATIO] [int],  /* DI_RATIO */
	[FREQ_TYPE] [tinyint],  /* FREQ_TYPE */
	[FREQ_PATTERN_TYPE] [tinyint],  /* FREQ_PATTERN_TYPE */
	[FREQ_PATTERN_PERIOD] [float],  /* FREQ_PATTERN_PERIOD */
	[FREQ_MEAN] [float],  /* FREQ_MEAN */
	[FREQ_MIN] [float],  /* FREQ_MIN */
	[FREQ_MAX] [float],  /* FREQ_MAX */
	[FREQ_POSITION_COUNT] [tinyint],  /* FREQ_POSITION_COUNT */
	[PRI_TYPE] [tinyint],  /* PRI_TYPE */
	[PRI_PATTERN_TYPE] [tinyint],  /* PRI_PATTERN_TYPE */
	[PRI_PATTERN_PERIOD] [float],  /* PRI_PATTERN_PERIOD */
	[PRI_MEAN] [float],  /* PRI_MEAN */
	[PRI_MIN] [float],  /* PRI_MIN */
	[PRI_MAX] [float],  /* PRI_MAX */
	[PRI_JITTER_RATIO] [float],  /* PRI_JITTER_RATIO */
	[PRI_POSITION_COUNT] [tinyint],  /* PRI_POSITION_COUNT */
	[PW_MEAN] [float],  /* PW_MEAN */
	[PW_MIN] [float],  /* PW_MIN */
	[PW_MAX] [float],  /* PW_MAX */
	[PA_MEAN] [float],  /* PA_MEAN */
	[PA_MIN] [float],  /* PA_MIN */
	[PA_MAX] [float],  /* PA_MAX */
	[IS_STORED_PDW] [tinyint],  /* IS_STORED_PDW */
	[NUM_PDW] [smallint],  /* NUM_PDW */
	[COLLECTOR_ID] [tinyint],  /* COLLECTOR_ID */
	[RADAR_LATITUDE] [float],  /* RADAR_LATITUDE */
	[RADAR_LONGITUDE] [float],  /* RADAR_LONGITUDE */
	[RADARMODE_NAME] [varchar](20),  /* RADARMODE_NAME */
	[RADARMODE_INDEX] [smallint] /* RADARMODE_INDEX */
)
GO

/* LOBDATA 기본키 */
ALTER TABLE [dbo].[LOBDATA]
	ADD
		CONSTRAINT [PK_LOBDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC, 
			[LOBID] ASC
		)
GO

/* LOBDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 데이터 입니다.', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDWID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDWID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* PLOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PLOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOBID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* AETID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AETID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* ABTID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* TASK_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'TASK_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'TASK_ID'
GO

/* CONTACT_TIME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'CONTACT_TIME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'CONTACT_TIME'
GO

/* CONTACT_TIME_MS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'CONTACT_TIME_MS', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'CONTACT_TIME_MS'
GO

/* SIGNAL_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'SIGNAL_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* DOA_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DOA_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MEAN'
GO

/* DOA_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DOA_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MIN'
GO

/* DOA_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DOA_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MAX'
GO

/* DI_RATIO */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DI_RATIO', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DI_RATIO'
GO

/* FREQ_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_TYPE'
GO

/* FREQ_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_TYPE'
GO

/* FREQ_PATTERN_PERIOD */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_PERIOD', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD'
GO

/* FREQ_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* FREQ_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* FREQ_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* FREQ_POSITION_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_POSITION_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_POSITION_COUNT'
GO

/* PRI_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI_PATTERN_PERIOD */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD'
GO

/* PRI_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI_JITTER_RATIO */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_JITTER_RATIO', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_JITTER_RATIO'
GO

/* PRI_POSITION_COUNT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_POSITION_COUNT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_POSITION_COUNT'
GO

/* PW_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* PW_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* PW_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* PA_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* PA_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* PA_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PA_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* IS_STORED_PDW */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'IS_STORED_PDW', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'IS_STORED_PDW'
GO

/* NUM_PDW */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'NUM_PDW', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_PDW'
GO

/* COLLECTOR_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'COLLECTOR_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'COLLECTOR_ID'
GO

/* RADAR_LATITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_LATITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADAR_LATITUDE'
GO

/* RADAR_LONGITUDE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADAR_LONGITUDE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADAR_LONGITUDE'
GO

/* RADARMODE_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* RADARMODE_INDEX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_INDEX', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* LOBDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_LOBDATA'
GO

/* LOBDATA 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBDATA 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'INDEX', @level2name=N'PK_LOBDATA'
GO

/* ABTDATA -> ABT_POSITION */
ALTER TABLE [dbo].[ABT_POSITION]
	ADD
		CONSTRAINT [FK_ABTDATA_TO_ABT_POSITION]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [dbo].[ABTDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* RAWDATA -> ABTDATA */
ALTER TABLE [dbo].[ABTDATA]
	ADD
		CONSTRAINT [FK_RAWDATA_TO_ABTDATA]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID]
		)
		REFERENCES [dbo].[RAWDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* LOBDATA -> LOB_POSITION */
ALTER TABLE [dbo].[LOB_POSITION]
	ADD
		CONSTRAINT [FK_LOBDATA_TO_LOB_POSITION]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [dbo].[LOBDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* ABTDATA -> AETDATA */
ALTER TABLE [dbo].[AETDATA]
	ADD
		CONSTRAINT [FK_ABTDATA_TO_AETDATA]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [dbo].[ABTDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* ABTDATA -> LOBDATA */
ALTER TABLE [dbo].[LOBDATA]
	ADD
		CONSTRAINT [FK_ABTDATA_TO_LOBDATA]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [dbo].[ABTDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* ABTDATA -> ABT_POSITION */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTDATA -> ABT_POSITION', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_ABT_POSITION'
GO

/* RAWDATA -> ABTDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RAWDATA -> ABTDATA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_RAWDATA_TO_ABTDATA'
GO

/* LOBDATA -> LOB_POSITION */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOBDATA -> LOB_POSITION', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_LOBDATA_TO_LOB_POSITION'
GO

/* ABTDATA -> AETDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTDATA -> AETDATA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_AETDATA'
GO

/* ABTDATA -> LOBDATA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABTDATA -> LOBDATA', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_LOBDATA'
GO