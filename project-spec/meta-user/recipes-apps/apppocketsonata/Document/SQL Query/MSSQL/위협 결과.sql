/* ELINT */
USE [ELINT]
GO

/* �� ������ */
CREATE TABLE [ABT_POSITION] (
	[SEQ_TYPE] [TINYINT] NOT NULL,  /* ������ ���� */
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[LOBID] [int] NOT NULL,  /* LOB ��ȣ */
	[PDWID] [INT] NOT NULL,  /* PDW ��ȣ */
	[PLOBID] [INT] NOT NULL,  /* ���� LOB ��ȣ */
	[AETID] [int] NOT NULL,  /* ���ü ��ȣ */
	[ABTID] [int] NOT NULL,  /* �� ��ȣ */
	[POSITION_COUNT] [tinyint],  /* �� ���� */
	[SEQ_01] [float],  /* �� #1 */
	[SEQ_02] [float],  /* �� #2 */
	[SEQ_03] [float],  /* �� #3 */
	[SEQ_04] [float],  /* �� #4 */
	[SEQ_05] [float],  /* �� #5 */
	[SEQ_06] [float],  /* �� #6 */
	[SEQ_07] [float],  /* �� #7 */
	[SEQ_08] [float],  /* �� #8 */
	[SEQ_09] [float],  /* �� #9 */
	[SEQ_10] [float],  /* �� #10 */
	[SEQ_11] [float],  /* �� #11 */
	[SEQ_12] [float],  /* �� #12 */
	[SEQ_13] [float],  /* �� #13 */
	[SEQ_14] [float],  /* �� #14 */
	[SEQ_15] [float],  /* �� #15 */
	[SEQ_16] [float],  /* �� #16 */
	[SEQ_17] [float],  /* �� #17 */
	[SEQ_18] [float],  /* �� #18 */
	[SEQ_19] [float],  /* �� #19 */
	[SEQ_20] [float],  /* �� #20 */
	[SEQ_21] [float],  /* �� #21 */
	[SEQ_22] [float],  /* �� #22 */
	[SEQ_23] [float],  /* �� #23 */
	[SEQ_24] [float],  /* �� #24 */
	[SEQ_25] [float],  /* �� #25 */
	[SEQ_26] [float],  /* �� #26 */
	[SEQ_27] [float],  /* �� #27 */
	[SEQ_28] [float],  /* �� #28 */
	[SEQ_29] [float],  /* �� #29 */
	[SEQ_30] [float],  /* �� #30 */
	[SEQ_31] [float],  /* �� #31 */
	[SEQ_32] [float] /* �� #32 */
)
	ON [PRIMARY]
GO

/* �� ������ �⺻Ű */
ALTER TABLE [ABT_POSITION]
	ADD
		CONSTRAINT [PK_ABT_POSITION]
		PRIMARY KEY NONCLUSTERED (
			[SEQ_TYPE] ASC, 
			[OP_INIT_ID] ASC, 
			[LOBID] ASC
		)
GO

/* �� ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION'
GO

/* ������ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_TYPE'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* PDW ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* ���� LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* ���ü ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ü ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* �� ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'POSITION_COUNT'
GO

/* �� #1 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #1', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_01'
GO

/* �� #2 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #2', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_02'
GO

/* �� #3 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #3', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_03'
GO

/* �� #4 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #4', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_04'
GO

/* �� #5 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #5', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_05'
GO

/* �� #6 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #6', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_06'
GO

/* �� #7 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #7', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_07'
GO

/* �� #8 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #8', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_08'
GO

/* �� #9 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #9', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_09'
GO

/* �� #10 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #10', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_10'
GO

/* �� #11 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #11', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_11'
GO

/* �� #12 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #12', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_12'
GO

/* �� #13 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #13', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_13'
GO

/* �� #14 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #14', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_14'
GO

/* �� #15 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #15', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_15'
GO

/* �� #16 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #16', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_16'
GO

/* �� #17 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #17', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_17'
GO

/* �� #18 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #18', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_18'
GO

/* �� #19 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #19', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_19'
GO

/* �� #20 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #20', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_20'
GO

/* �� #21 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #21', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_21'
GO

/* �� #22 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #22', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_22'
GO

/* �� #23 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #23', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_23'
GO

/* �� #24 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #24', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_24'
GO

/* �� #25 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #25', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_25'
GO

/* �� #26 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #26', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_26'
GO

/* �� #27 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #27', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_27'
GO

/* �� #28 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #28', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_28'
GO

/* �� #29 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #29', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_29'
GO

/* �� #30 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #30', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_30'
GO

/* �� #31 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #31', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_31'
GO

/* �� #32 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #32', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_32'
GO

/* �� ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_ABT_POSITION'
GO

/* �� ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'INDEX', @level2name=N'PK_ABT_POSITION'
GO

/* �� ������ */
CREATE TABLE [ABTDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW ��ȣ */
	[PLOBID] [INT] NOT NULL,  /* ���� LOB ��ȣ */
	[LOBID] [int] NOT NULL,  /* LOB ��ȣ */
	[AETID] [int] NOT NULL,  /* ���ü ��ȣ */
	[ABTID] [int] NOT NULL,  /* �� ��ȣ */
	[FIRST_TIME] [datetime],  /* ���� �ð� */
	[LAST_TIME] [datetime],  /* �ֱ� �ð� */
	[SIGNAL_TYPE] [tinyint],  /* ��ȣ ���� */
	[NUM_LOB] [int],  /* LOB ���� */
	[BEAM_VALIDITY] [int],  /* �� ��ȿ�� */
	[FREQ_TYPE] [tinyint],  /* ������ ���� */
	[FREQ_PATTERN_TYPE] [tinyint],  /* ���ļ� ���� ���� */
	[FREQ_PATTERN_PERIOD_MEAN] [float],  /* FREQ_PATTERN_PERIOD_MEAN */
	[FREQ_PATTERN_PERIOD_MIN] [float],  /* FREQ_PATTERN_PERIOD_MIN */
	[FREQ_PATTERN_PERIOD_MAX] [float],  /* FREQ_PATTERN_PERIOD_MAX */
	[FREQ_MEAN] [float],  /* ���ļ� ��� */
	[FREQ_MIN] [float],  /* ���ļ� �ּ� */
	[FREQ_MAX] [float],  /* ���ļ� �ִ� */
	[FREQ_POSITION_COUNT] [TINYINT],  /* ���ļ� �� ���� */
	[FREQ_ELEMENT_COUNT] [TINYINT],  /* ���ļ� ��� ���� */
	[PRI_TYPE] [TINYINT],  /* PRI ���� */
	[PRI_PATTERN_TYPE] [TINYINT],  /* PRI ���� ���� */
	[PRI_PATTERN_PERIOD_MEAN] [float],  /* PRI ���� �ֱ� ��� */
	[PRI_PATTERN_PERIOD_MIN] [float],  /* PRI ���� �ֱ� �ּ� */
	[PRI_PATTERN_PERIOD_MAX] [float],  /* PRI ���� �ֱ� �ִ� */
	[PRI_MEAN] [float],  /* PRI ��� */
	[PRI_MIN] [float],  /* PRI �ּ� */
	[PRI_MAX] [float],  /* PRI �ִ� */
	[PRI_JITTER_RATIO] [float],  /* PRI ������ */
	[PRI_POSITION_COUNT] [TINYINT],  /* PRI �� ���� */
	[PRI_ELEMENT_COUNT] [TINYINT],  /* PRI ��� ���� */
	[PW_MEAN] [float],  /* �޽��� ��� */
	[PW_MIN] [float],  /* �޽��� �ּ� */
	[PW_MAX] [float],  /* �޽��� �ִ� */
	[PA_MEAN] [float],  /* ��ȣ���� ��� */
	[PA_MIN] [float],  /* ��ȣ���� �ּ� */
	[PA_MAX] [float],  /* ��ȣ���� �ִ� */
	[TOTAL_PDW] [int],  /* PDW �Ѱ��� */
	[RADARMODE_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* ���̴����� */
	[RADARMODE_INDEX] [smallint],  /* ���̴���� �ε��� */
	[THREAT_INDEX] [smallint],  /* ���� �ε��� */
	[PE_VALID] [TINYINT],  /* ��ġ ��ȿ�� */
	[PE_LATITUDE] [float],  /* ��ġ ���� */
	[PE_LONGITUDE] [float],  /* ��ġ �浵 */
	[PE_CEP] [float],  /* ��ġ CEP */
	[PE_MAJOR_AXIS] [float],  /* ��ġ ���� */
	[PE_MINOR_AXIS] [float],  /* ��ġ ���� */
	[PE_THETA] [float],  /* ��ġ ���� */
	[PE_DISTANCE] [float],  /* ��ġ �Ÿ����� */
	[ALARM_TIME] [datetime],  /* �溸 �ð� */
	[STAT] [TINYINT] /* ���� */
)
	ON [PRIMARY]
GO

/* �� ������ �⺻Ű */
ALTER TABLE [ABTDATA]
	ADD
		CONSTRAINT [PK_ABTDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC, 
			[LOBID] ASC
		)
GO

/* �� ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABT ������ �Դϴ�.', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDW ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* ���� LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* ���ü ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ü ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* �� ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* ���� �ð� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ð�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FIRST_TIME'
GO

/* �ֱ� �ð� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ֱ� �ð�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'LAST_TIME'
GO

/* ��ȣ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* LOB ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_LOB'
GO

/* �� ��ȿ�� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ��ȿ��', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'BEAM_VALIDITY'
GO

/* ������ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_TYPE'
GO

/* ���ļ� ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_TYPE'
GO

/* FREQ_PATTERN_PERIOD_MEAN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_PERIOD_MEAN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD_MEAN'
GO

/* FREQ_PATTERN_PERIOD_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_PERIOD_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD_MIN'
GO

/* FREQ_PATTERN_PERIOD_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'FREQ_PATTERN_PERIOD_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD_MAX'
GO

/* ���ļ� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* ���ļ� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* ���ļ� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* ���ļ� �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_POSITION_COUNT'
GO

/* ���ļ� ��� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ��� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_ELEMENT_COUNT'
GO

/* PRI ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI ���� �ֱ� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� �ֱ� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MEAN'
GO

/* PRI ���� �ֱ� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� �ֱ� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MIN'
GO

/* PRI ���� �ֱ� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� �ֱ� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MAX'
GO

/* PRI ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_JITTER_RATIO'
GO

/* PRI �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_POSITION_COUNT'
GO

/* PRI ��� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ��� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_ELEMENT_COUNT'
GO

/* �޽��� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* �޽��� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* �޽��� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* ��ȣ���� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* ��ȣ���� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* ��ȣ���� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* PDW �Ѱ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW �Ѱ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'TOTAL_PDW'
GO

/* ���̴����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* ���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* ��ġ ��ȿ�� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ��ȿ��', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_VALID'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LATITUDE'
GO

/* ��ġ �浵 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ �浵', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LONGITUDE'
GO

/* ��ġ CEP */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ CEP', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_CEP'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MAJOR_AXIS'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MINOR_AXIS'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_THETA'
GO

/* ��ġ �Ÿ����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ �Ÿ�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_DISTANCE'
GO

/* �溸 �ð� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�溸 �ð�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'ALARM_TIME'
GO

/* ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'STAT'
GO

/* �� ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_ABTDATA'
GO

/* �� ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'INDEX', @level2name=N'PK_ABTDATA'
GO

/* LOB ������ */
CREATE TABLE [LOB_POSITION] (
	[SEQ_TYPE] [TINYINT] NOT NULL,  /* ������ ���� */
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[LOBID] [int] NOT NULL,  /* LOB ��ȣ */
	[PDWID] [INT] NOT NULL,  /* PDW ��ȣ */
	[PLOBID] [INT] NOT NULL,  /* ���� LOB ��ȣ */
	[AETID] [int] NOT NULL,  /* ���ü ��ȣ */
	[ABTID] [int] NOT NULL,  /* �� ��ȣ */
	[POSITION_COUNT] [tinyint],  /* �� ���� */
	[SEQ_01] [float],  /* �� #1 */
	[SEQ_02] [float],  /* �� #2 */
	[SEQ_03] [float],  /* �� #3 */
	[SEQ_04] [float],  /* �� #4 */
	[SEQ_05] [float],  /* �� #5 */
	[SEQ_06] [float],  /* �� #6 */
	[SEQ_07] [float],  /* �� #7 */
	[SEQ_08] [float],  /* �� #8 */
	[SEQ_09] [float],  /* �� #9 */
	[SEQ_10] [float],  /* �� #10 */
	[SEQ_11] [float],  /* �� #11 */
	[SEQ_12] [float],  /* �� #12 */
	[SEQ_13] [float],  /* �� #13 */
	[SEQ_14] [float],  /* �� #14 */
	[SEQ_15] [float],  /* �� #15 */
	[SEQ_16] [float],  /* �� #16 */
	[SEQ_17] [float],  /* �� #17 */
	[SEQ_18] [float],  /* �� #18 */
	[SEQ_19] [float],  /* �� #19 */
	[SEQ_20] [float],  /* �� #20 */
	[SEQ_21] [float],  /* �� #21 */
	[SEQ_22] [float],  /* �� #22 */
	[SEQ_23] [float],  /* �� #23 */
	[SEQ_24] [float],  /* �� #24 */
	[SEQ_25] [float],  /* �� #25 */
	[SEQ_26] [float],  /* �� #26 */
	[SEQ_27] [float],  /* �� #27 */
	[SEQ_28] [float],  /* �� #28 */
	[SEQ_29] [float],  /* �� #29 */
	[SEQ_30] [float],  /* �� #30 */
	[SEQ_31] [float],  /* �� #31 */
	[SEQ_32] [float] /* �� #32 */
)
	ON [PRIMARY]
GO

/* LOB ������ �⺻Ű */
ALTER TABLE [LOB_POSITION]
	ADD
		CONSTRAINT [PK_LOB_POSITION]
		PRIMARY KEY NONCLUSTERED (
			[SEQ_TYPE] ASC, 
			[OP_INIT_ID] ASC, 
			[LOBID] ASC
		)
GO

/* LOB ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION'
GO

/* ������ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_TYPE'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* PDW ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* ���� LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* ���ü ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ü ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* �� ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'POSITION_COUNT'
GO

/* �� #1 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #1', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_01'
GO

/* �� #2 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #2', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_02'
GO

/* �� #3 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #3', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_03'
GO

/* �� #4 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #4', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_04'
GO

/* �� #5 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #5', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_05'
GO

/* �� #6 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #6', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_06'
GO

/* �� #7 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #7', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_07'
GO

/* �� #8 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #8', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_08'
GO

/* �� #9 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #9', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_09'
GO

/* �� #10 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #10', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_10'
GO

/* �� #11 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #11', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_11'
GO

/* �� #12 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #12', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_12'
GO

/* �� #13 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #13', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_13'
GO

/* �� #14 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #14', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_14'
GO

/* �� #15 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #15', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_15'
GO

/* �� #16 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #16', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_16'
GO

/* �� #17 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #17', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_17'
GO

/* �� #18 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #18', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_18'
GO

/* �� #19 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #19', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_19'
GO

/* �� #20 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #20', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_20'
GO

/* �� #21 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #21', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_21'
GO

/* �� #22 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #22', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_22'
GO

/* �� #23 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #23', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_23'
GO

/* �� #24 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #24', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_24'
GO

/* �� #25 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #25', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_25'
GO

/* �� #26 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #26', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_26'
GO

/* �� #27 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #27', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_27'
GO

/* �� #28 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #28', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_28'
GO

/* �� #29 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #29', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_29'
GO

/* �� #30 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #30', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_30'
GO

/* �� #31 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #31', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_31'
GO

/* �� #32 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� #32', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_32'
GO

/* LOB ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_LOB_POSITION'
GO

/* LOB ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'INDEX', @level2name=N'PK_LOB_POSITION'
GO

/* RADARMODE */
CREATE TABLE [RADARMODE] (
	[RADARMODE_INDEX] [int] NOT NULL,  /* ���̴���� �ε��� */
	[RADARMODE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS NOT NULL,  /* ���̴����� */
	[MODECODE] [VARCHAR](20),  /* ����ȣ */
	[DATE_CREATED] [datetime],  /* ���� ��¥ */
	[DATE_LAST_UPDATED] [datetime],  /* DATE_LAST_UPDATED */
	[DATE_FIRST_SEEN] [datetime],  /* DATE_FIRST_SEEN */
	[DATE_LAST_SEEN] [datetime],  /* DATE_LAST_SEEN */
	[PLATFORM] [tinyint],  /* �÷��� */
	[SIGNAL_TYPE] [tinyint],  /* ��ȣ ���� */
	[RF_TYPE] [tinyint] NOT NULL,  /* RF ���� */
	[RF_TYPICAL_MIN] [float],  /* RF_TYPICAL_MIN */
	[RF_TYPICAL_MAX] [float],  /* RF_TYPICAL_MAX */
	[RF_PATTERN_TYPE] [tinyint],  /* RF_PATTERN_TYPE */
	[RF_NUM_POSITIONS] [tinyint],  /* RF_NUM_POSITIONS */
	[RF_PATTERN_PERIOD_MIN] [float],  /* RF_PATTERN_PERIOD_MIN */
	[RF_PATTERN_PERIOD_MAX] [float],  /* RF_PATTERN_PERIOD_MAX */
	[PRI_TYPE] [tinyint] NOT NULL,  /* PRI ���� */
	[PRI_TYPICAL_MIN] [float],  /* PRI_TYPICAL_MIN */
	[PRI_TYPICAL_MAX] [float],  /* PRI_TYPICAL_MAX */
	[PRI_PATTERN_TYPE] [tinyint],  /* PRI_PATTERN_TYPE */
	[PRI_NUM_POSITIONS] [tinyint],  /* PRI_NUM_POSITIONS */
	[PRI_PATTERN_PERIOD_MIN] [float],  /* PRI_PATTERN_PERIOD_MIN */
	[PRI_PATTERN_PERIOD_MAX] [float],  /* PRI_PATTERN_PERIOD_MAX */
	[PW_TYPICAL_MIN] [float],  /* PW_TYPICAL_MIN */
	[PW_TYPICAL_MAX] [float],  /* PW_TYPICAL_MAX */
	[VALIDATION] [tinyint],  /* VALIDATION */
	[PRIORITY] [INT] DEFAULT 0 /* �켱���� */
)
	ON [PRIMARY]
GO

/* PK__RADARMOD__5D8D6E820428B272 */
ALTER TABLE [RADARMODE]
	ADD
		CONSTRAINT [PK__RADARMOD__5D8D6E820428B272]
		PRIMARY KEY CLUSTERED (
			[RADARMODE_INDEX] ASC
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
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴� ��� �Դϴ�.', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* ���̴����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* ����ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'MODECODE'
GO

/* ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ��¥', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_CREATED'
GO

/* DATE_LAST_UPDATED */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_LAST_UPDATED', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_UPDATED'
GO

/* DATE_FIRST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_FIRST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* DATE_LAST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_LAST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* �÷��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�÷���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM'
GO

/* ��ȣ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* RF ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPE'
GO

/* RF_TYPICAL_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_TYPICAL_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MIN'
GO

/* RF_TYPICAL_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_TYPICAL_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MAX'
GO

/* RF_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_TYPE'
GO

/* RF_NUM_POSITIONS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_NUM_POSITIONS', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_NUM_POSITIONS'
GO

/* RF_PATTERN_PERIOD_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_PATTERN_PERIOD_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MIN'
GO

/* RF_PATTERN_PERIOD_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_PATTERN_PERIOD_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MAX'
GO

/* PRI ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI_TYPICAL_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_TYPICAL_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MIN'
GO

/* PRI_TYPICAL_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_TYPICAL_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MAX'
GO

/* PRI_PATTERN_TYPE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_TYPE', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI_NUM_POSITIONS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_NUM_POSITIONS', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_NUM_POSITIONS'
GO

/* PRI_PATTERN_PERIOD_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MIN'
GO

/* PRI_PATTERN_PERIOD_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_PATTERN_PERIOD_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MAX'
GO

/* PW_TYPICAL_MIN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_TYPICAL_MIN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MIN'
GO

/* PW_TYPICAL_MAX */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PW_TYPICAL_MAX', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MAX'
GO

/* VALIDATION */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'VALIDATION', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'VALIDATION'
GO

/* �켱���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�켱����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRIORITY'
GO

/* PK__RADARMOD__5D8D6E820428B272 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__5D8D6E820428B272', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__RADARMOD__5D8D6E820428B272'
GO

/* PK__RADARMOD__5D8D6E820428B272 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__5D8D6E820428B272', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'INDEX', @level2name=N'PK__RADARMOD__5D8D6E820428B272'
GO

/* RADARMODE_PRI_SEQUENCE */
CREATE TABLE [RADARMODE_PRI_SEQUENCE] (
	[RADARMODE_INDEX] [int] NOT NULL,  /* ���̴���� �ε��� */
	[PRI_SEQ_ID] [int] NOT NULL,  /* PRI_SEQ_ID */
	[PRI_SEQ_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* PRI_SEQ_NAME */
	[PRI_MIN] [float],  /* PRI �ּ� */
	[PRI_MAX] [float] /* PRI �ִ� */
)
	ON [PRIMARY]
GO

/* PK__RADARMOD__F56ABC074ADECD96 */
ALTER TABLE [RADARMODE_PRI_SEQUENCE]
	ADD
		CONSTRAINT [PK__RADARMOD__F56ABC074ADECD96]
		PRIMARY KEY CLUSTERED (
			[RADARMODE_INDEX] ASC, 
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
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* PRI_SEQ_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_SEQ_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_ID'
GO

/* PRI_SEQ_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI_SEQ_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_NAME'
GO

/* PRI �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PK__RADARMOD__F56ABC074ADECD96 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F56ABC074ADECD96', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__RADARMOD__F56ABC074ADECD96'
GO

/* PK__RADARMOD__F56ABC074ADECD96 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F56ABC074ADECD96', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'INDEX', @level2name=N'PK__RADARMOD__F56ABC074ADECD96'
GO

/* RADARMODE_RF_SEQUENCE */
CREATE TABLE [RADARMODE_RF_SEQUENCE] (
	[RADARMODE_INDEX] [int] NOT NULL,  /* ���̴���� �ε��� */
	[RF_SEQ_ID] [int] NOT NULL,  /* RF_SEQ_ID */
	[RF_SEQ_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* RF_SEQ_NAME */
	[RF_MIN] [float],  /* RF �ּ� */
	[RF_MAX] [float] /* RF �ִ� */
)
	ON [PRIMARY]
GO

/* PK__RADARMOD__F4541D42173876EA */
ALTER TABLE [RADARMODE_RF_SEQUENCE]
	ADD
		CONSTRAINT [PK__RADARMOD__F4541D42173876EA]
		PRIMARY KEY CLUSTERED (
			[RADARMODE_INDEX] ASC, 
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
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* RF_SEQ_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_SEQ_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_SEQ_ID'
GO

/* RF_SEQ_NAME */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_SEQ_NAME', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_SEQ_NAME'
GO

/* RF �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_MIN'
GO

/* RF �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_MAX'
GO

/* PK__RADARMOD__F4541D42173876EA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F4541D42173876EA', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__RADARMOD__F4541D42173876EA'
GO

/* PK__RADARMOD__F4541D42173876EA */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__RADARMOD__F4541D42173876EA', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'INDEX', @level2name=N'PK__RADARMOD__F4541D42173876EA'
GO

/* THREAT */
CREATE TABLE [THREAT] (
	[THREAT_INDEX] [int] NOT NULL,  /* ���� �ε��� */
	[RADARMODE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS NOT NULL,  /* ���̴����� */
	[THREAT_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS,  /* ������ */
	[LATITUDE] [float],  /* ���� */
	[LONGITUDE] [float],  /* �浵 */
	[SITE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS,  /* ����Ʈ�� */
	[THREAT_PLATFORM] [tinyint],  /* �÷��� */
	[DATE_CREATED] [datetime],  /* ���� ��¥ */
	[DATE_FIRST_SEEN] [datetime],  /* DATE_FIRST_SEEN */
	[DATE_LAST_SEEN] [datetime],  /* DATE_LAST_SEEN */
	[ID_RANGE] [float] /* �ĺ� �ݰ� */
)
	ON [PRIMARY]
GO

/* PK__THREAT__DD4AC47457A20A5B */
ALTER TABLE [THREAT]
	ADD
		CONSTRAINT [PK__THREAT__DD4AC47457A20A5B]
		PRIMARY KEY CLUSTERED (
			[THREAT_INDEX] ASC, 
			[RADARMODE_NAME] ASC
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
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT'
GO

/* ���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* ���̴����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_NAME'
GO

/* ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LATITUDE'
GO

/* �浵 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�浵', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LONGITUDE'
GO

/* ����Ʈ�� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����Ʈ��', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'SITE_NAME'
GO

/* �÷��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�÷���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PLATFORM'
GO

/* ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ��¥', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_CREATED'
GO

/* DATE_FIRST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_FIRST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* DATE_LAST_SEEN */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'DATE_LAST_SEEN', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* �ĺ� �ݰ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ĺ� �ݰ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'ID_RANGE'
GO

/* PK__THREAT__DD4AC47457A20A5B */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__THREAT__DD4AC47457A20A5B', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'CONSTRAINT', @level2name=N'PK__THREAT__DD4AC47457A20A5B'
GO

/* PK__THREAT__DD4AC47457A20A5B */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PK__THREAT__DD4AC47457A20A5B', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'INDEX', @level2name=N'PK__THREAT__DD4AC47457A20A5B'
GO

/* ���ü ������ */
CREATE TABLE [AETDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW ��ȣ */
	[PLOBID] [INT] NOT NULL,  /* ���� LOB ��ȣ */
	[LOBID] [int] NOT NULL,  /* LOB ��ȣ */
	[AETID] [int] NOT NULL,  /* ���ü ��ȣ */
	[ABTID] [int] NOT NULL,  /* �� ��ȣ */
	[FIRST_TIME] [datetime],  /* ���� �ð� */
	[LAST_TIME] [datetime],  /* �ֱ� �ð� */
	[PRIMARY_ELNOT] [varchar](20),  /* 1�� ELNOT */
	[PRIMARY_MODECODE] [varchar](20),  /* 1�� ��� ��ȣ */
	[RADARMODE_NAME] [varchar](20),  /* ���̴����� */
	[NICK_NAME] [varchar](20),  /* ���� */
	[FUNC_CODE] [varchar](20),  /* ��� �ڵ� */
	[PLATFORM_TYPE] [varchar](20),  /* �÷��� ���� */
	[RADARMODE_PRIORITY] [varchar](20),  /* ���̴���� �켱���� */
	[RADAR_PRIORITY] [varchar](20),  /* ���̴� �켱���� */
	[PIN_NUM] [INT],  /* �� ��ȣ */
	[PLACENAME_KOR] [varchar](20),  /* ��ġ �ѱ۸� */
	[THREAT_FUNC_CODE] [varchar](20),  /* ���� ��� �ڵ� */
	[THREAT_PRIORITY] [varchar](20),  /* ���� �켱���� */
	[RADARMODE_INDEX] [int],  /* ���̴���� �ε��� */
	[THREAT_INDEX] [int],  /* ���� �ε��� */
	[VALIDITY] [tinyint],  /* ��ȿ�� */
	[DOA_MEAN] [float],  /* ���� ��� */
	[DOA_MIN] [float],  /* �ּ� ���� */
	[DOA_MAX] [float],  /* ���� �ִ� */
	[DOA_DEV] [float],  /* ���� ���� */
	[FREQ_MEAN] [float],  /* ���ļ� ��� */
	[FREQ_MIN] [float],  /* ���ļ� �ּ� */
	[FREQ_MAX] [float],  /* ���ļ� �ִ� */
	[FREQ_DEV] [float],  /* ���ļ� ���� */
	[PRI_MEAN] [float],  /* PRI ��� */
	[PRI_MIN] [float],  /* PRI �ּ� */
	[PRI_MAX] [float],  /* PRI �ִ� */
	[PRI_DEV] [float],  /* PRI ���� */
	[PW_MEAN] [float],  /* �޽��� ��� */
	[PW_MIN] [float],  /* �޽��� �ּ� */
	[PW_MAX] [float],  /* �޽��� �ִ� */
	[PW_DEV] [float],  /* �޽��� ���� */
	[PA_MEAN] [float],  /* ��ȣ���� ��� */
	[PA_MIN] [float],  /* ��ȣ���� �ּ� */
	[PA_MAX] [float],  /* ��ȣ���� �ִ� */
	[PA_DEV] [float],  /* ��ȣ���� ���� */
	[PE_VALID] [tinyint],  /* ��ġ ��ȿ�� */
	[PE_LATITUDE] [float],  /* ��ġ ���� */
	[PE_LONGITUDE] [float],  /* ��ġ �浵 */
	[PE_HEIGHT] [float],  /* PE_HEIGHT */
	[PE_CEP] [float],  /* ��ġ CEP */
	[PE_MAJOR_AXIS] [float],  /* ��ġ ���� */
	[PE_MINOR_AXIS] [float],  /* ��ġ ���� */
	[PE_THETA] [float],  /* ��ġ ���� */
	[PE_DISTANCE] [float],  /* ��ġ �Ÿ����� */
	[STAT] [tinyint],  /* ���� */
	[NUM_OF_BEAMS] [int],  /* �� ���� */
	[NUM_OF_LOBS] [int],  /* LOB ���� */
	[IDINFO] [varchar](12),  /* �ĺ� ���� */
	[FINAL_ALARM_TIME] [datetime] /* ���� �溸 �ð� */
)
GO

/* ���ü ������ �⺻Ű */
ALTER TABLE [AETDATA]
	ADD
		CONSTRAINT [PK_AETDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC, 
			[LOBID] ASC
		)
GO

/* ���ü ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AET ������ �Դϴ�.', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDW ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* ���� LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* ���ü ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ü ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* �� ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* ���� �ð� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ð�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FIRST_TIME'
GO

/* �ֱ� �ð� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ֱ� �ð�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'LAST_TIME'
GO

/* 1�� ELNOT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'1�� ELNOT', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRIMARY_ELNOT'
GO

/* 1�� ��� ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'1�� ��� ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRIMARY_MODECODE'
GO

/* ���̴����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NICK_NAME'
GO

/* ��� �ڵ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��� �ڵ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FUNC_CODE'
GO

/* �÷��� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�÷��� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM_TYPE'
GO

/* ���̴���� �켱���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �켱����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_PRIORITY'
GO

/* ���̴� �켱���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴� �켱����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADAR_PRIORITY'
GO

/* �� ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PIN_NUM'
GO

/* ��ġ �ѱ۸� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ �ѱ۸�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLACENAME_KOR'
GO

/* ���� ��� �ڵ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ��� �ڵ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_FUNC_CODE'
GO

/* ���� �켱���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �켱����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PRIORITY'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* ���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* ��ȿ�� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȿ��', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'VALIDITY'
GO

/* ���� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MEAN'
GO

/* �ּ� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ּ� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MIN'
GO

/* ���� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MAX'
GO

/* ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_DEV'
GO

/* ���ļ� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* ���ļ� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* ���ļ� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* ���ļ� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_DEV'
GO

/* PRI ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_DEV'
GO

/* �޽��� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* �޽��� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* �޽��� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* �޽��� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_DEV'
GO

/* ��ȣ���� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* ��ȣ���� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* ��ȣ���� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* ��ȣ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_DEV'
GO

/* ��ġ ��ȿ�� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ��ȿ��', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_VALID'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LATITUDE'
GO

/* ��ġ �浵 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ �浵', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LONGITUDE'
GO

/* PE_HEIGHT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PE_HEIGHT', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_HEIGHT'
GO

/* ��ġ CEP */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ CEP', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_CEP'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MAJOR_AXIS'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MINOR_AXIS'
GO

/* ��ġ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_THETA'
GO

/* ��ġ �Ÿ����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ġ �Ÿ�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_DISTANCE'
GO

/* ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'STAT'
GO

/* �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_OF_BEAMS'
GO

/* LOB ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_OF_LOBS'
GO

/* �ĺ� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ĺ� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'IDINFO'
GO

/* ���� �溸 �ð� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �溸 �ð�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FINAL_ALARM_TIME'
GO

/* ���ü ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ü ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_AETDATA'
GO

/* ���ü ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ü ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'INDEX', @level2name=N'PK_AETDATA'
GO

/* ���� ������ */
CREATE TABLE [RAWDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW ��ȣ */
	[PLOBID] [INT] NOT NULL,  /* ���� LOB ��ȣ */
	[TASK_ID] [CHAR](30),  /* ���� ID */
	[CREATE_TIME] [DATETIME],  /* ���� �ð�(�ú���) */
	[CREATE_TIME_MS] [TINYINT],  /* CREATE_TIME_MS */
	[COUNTOFDATA] [SMALLINT],  /* �������� */
	[FILENAME] [char](100),  /* ���ϸ� */
	[DATA_TYPE] [TINYINT] /* ������ ���� */
)
GO

/* ���� ������ �⺻Ű */
ALTER TABLE [RAWDATA]
	ADD
		CONSTRAINT [PK_RAWDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC
		)
GO

/* ���� ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ������ �Դϴ�.', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDW ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* ���� LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* ���� ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'TASK_ID'
GO

/* ���� �ð�(�ú���) */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ð�(�ú���)', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'CREATE_TIME'
GO

/* CREATE_TIME_MS */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'CREATE_TIME_MS', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'CREATE_TIME_MS'
GO

/* �������� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'COUNTOFDATA'
GO

/* ���ϸ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ϸ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'FILENAME'
GO

/* ������ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'DATA_TYPE'
GO

/* ���� ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_RAWDATA'
GO

/* ���� ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'INDEX', @level2name=N'PK_RAWDATA'
GO

/* LOB ������ */
CREATE TABLE [LOBDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW ��ȣ */
	[PLOBID] [INT] NOT NULL,  /* ���� LOB ��ȣ */
	[LOBID] [int] NOT NULL,  /* LOB ��ȣ */
	[AETID] [int] NOT NULL,  /* ���ü ��ȣ */
	[ABTID] [int] NOT NULL,  /* �� ��ȣ */
	[TASK_ID] [varchar](30) NOT NULL,  /* ���� ID */
	[CONTACT_TIME] [datetime],  /* ���� �ð�(�ú���) */
	[CONTACT_TIME_MS] [int],  /* ���� �ð�(ms) */
	[SIGNAL_TYPE] [tinyint],  /* ��ȣ ���� */
	[DOA_MEAN] [float],  /* ���� ��� */
	[DOA_MIN] [float],  /* �ּ� ���� */
	[DOA_MAX] [float],  /* ���� �ִ� */
	[DI_RATIO] [int],  /* ��Ž ��ȿ�� */
	[FREQ_TYPE] [tinyint],  /* ������ ���� */
	[FREQ_PATTERN_TYPE] [tinyint],  /* ���ļ� ���� ���� */
	[FREQ_PATTERN_PERIOD] [float],  /* ���ļ� ���� �ֱ� */
	[FREQ_MEAN] [float],  /* ���ļ� ��� */
	[FREQ_MIN] [float],  /* ���ļ� �ּ� */
	[FREQ_MAX] [float],  /* ���ļ� �ִ� */
	[FREQ_POSITION_COUNT] [tinyint],  /* ���ļ� �� ���� */
	[PRI_TYPE] [tinyint],  /* PRI ���� */
	[PRI_PATTERN_TYPE] [tinyint],  /* PRI ���� ���� */
	[PRI_PATTERN_PERIOD] [float],  /* PRI ���� �ֱ� */
	[PRI_MEAN] [float],  /* PRI ��� */
	[PRI_MIN] [float],  /* PRI �ּ� */
	[PRI_MAX] [float],  /* PRI �ִ� */
	[PRI_JITTER_RATIO] [float],  /* PRI ������ */
	[PRI_POSITION_COUNT] [tinyint],  /* PRI �� ���� */
	[PW_MEAN] [float],  /* �޽��� ��� */
	[PW_MIN] [float],  /* �޽��� �ּ� */
	[PW_MAX] [float],  /* �޽��� �ִ� */
	[PA_MEAN] [float],  /* ��ȣ���� ��� */
	[PA_MIN] [float],  /* ��ȣ���� �ּ� */
	[PA_MAX] [float],  /* ��ȣ���� �ִ� */
	[IS_STORED_PDW] [tinyint],  /* ���� ���� */
	[NUM_PDW] [smallint],  /* PDW ���� */
	[COLLECTOR_ID] [tinyint],  /* ������ */
	[LATITUDE] [float],  /* ���� */
	[LONGITUDE] [float],  /* �浵 */
	[RADARMODE_NAME] [varchar](20),  /* ���̴����� */
	[RADARMODE_INDEX] [smallint] /* ���̴���� �ε��� */
)
GO

/* LOB ������ �⺻Ű */
ALTER TABLE [LOBDATA]
	ADD
		CONSTRAINT [PK_LOBDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC, 
			[LOBID] ASC
		)
GO

/* LOB ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ������ �Դϴ�.', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA'
GO

/* OP_INIT_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'OP_INIT_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'OP_INIT_ID'
GO

/* PDW ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* ���� LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOB ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* ���ü ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ü ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* �� ��ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ��ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* ���� ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'TASK_ID'
GO

/* ���� �ð�(�ú���) */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ð�(�ú���)', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'CONTACT_TIME'
GO

/* ���� �ð�(ms) */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ð�(ms)', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'CONTACT_TIME_MS'
GO

/* ��ȣ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* ���� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MEAN'
GO

/* �ּ� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ּ� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MIN'
GO

/* ���� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MAX'
GO

/* ��Ž ��ȿ�� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��Ž ��ȿ��', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DI_RATIO'
GO

/* ������ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_TYPE'
GO

/* ���ļ� ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_TYPE'
GO

/* ���ļ� ���� �ֱ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ���� �ֱ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD'
GO

/* ���ļ� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* ���ļ� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* ���ļ� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* ���ļ� �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���ļ� �� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_POSITION_COUNT'
GO

/* PRI ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI ���� �ֱ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� �ֱ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD'
GO

/* PRI ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_JITTER_RATIO'
GO

/* PRI �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_POSITION_COUNT'
GO

/* �޽��� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* �޽��� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* �޽��� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* ��ȣ���� ��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� ���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* ��ȣ���� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* ��ȣ���� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ���� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'IS_STORED_PDW'
GO

/* PDW ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_PDW'
GO

/* ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'COLLECTOR_ID'
GO

/* ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'LATITUDE'
GO

/* �浵 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�浵', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'LONGITUDE'
GO

/* ���̴����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* LOB ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_LOBDATA'
GO

/* LOB ������ �⺻Ű */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ������ �⺻Ű', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'INDEX', @level2name=N'PK_LOBDATA'
GO

/* �� ������ -> �� ������ */
ALTER TABLE [ABT_POSITION]
	ADD
		CONSTRAINT [FK_ABTDATA_TO_ABT_POSITION]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [ABTDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* ���� ������ -> �� ������ */
ALTER TABLE [ABTDATA]
	ADD
		CONSTRAINT [FK_RAWDATA_TO_ABTDATA]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID]
		)
		REFERENCES [RAWDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* LOB ������ -> LOB ������ */
ALTER TABLE [LOB_POSITION]
	ADD
		CONSTRAINT [FK_LOBDATA_TO_LOB_POSITION]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [LOBDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* RADARMODE -> RADARMODE_PRI_SEQUENCE */
ALTER TABLE [RADARMODE_PRI_SEQUENCE]
	ADD
		CONSTRAINT [FK_RADARMODE_TO_RADARMODE_PRI_SEQUENCE]
		FOREIGN KEY (
			[RADARMODE_INDEX]
		)
		REFERENCES [RADARMODE] (
			[RADARMODE_INDEX]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* RADARMODE -> RADARMODE_RF_SEQUENCE */
ALTER TABLE [RADARMODE_RF_SEQUENCE]
	ADD
		CONSTRAINT [FK_RADARMODE_TO_RADARMODE_RF_SEQUENCE]
		FOREIGN KEY (
			[RADARMODE_INDEX]
		)
		REFERENCES [RADARMODE] (
			[RADARMODE_INDEX]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* �� ������ -> ���ü ������ */
ALTER TABLE [AETDATA]
	ADD
		CONSTRAINT [FK_ABTDATA_TO_AETDATA]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [ABTDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* �� ������ -> LOB ������ */
ALTER TABLE [LOBDATA]
	ADD
		CONSTRAINT [FK_ABTDATA_TO_LOBDATA]
		FOREIGN KEY (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		REFERENCES [ABTDATA] (
			[OP_INIT_ID], 
			[PDWID], 
			[PLOBID], 
			[LOBID]
		)
		ON DELETE NO ACTION
		ON UPDATE NO ACTION
GO

/* �� ������ -> �� ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������ -> �� ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_ABT_POSITION'
GO

/* ���� ������ -> �� ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ������ -> �� ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_RAWDATA_TO_ABTDATA'
GO

/* LOB ������ -> LOB ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB ������ -> LOB ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_LOBDATA_TO_LOB_POSITION'
GO

/* RADARMODE -> RADARMODE_PRI_SEQUENCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE -> RADARMODE_PRI_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_RADARMODE_TO_RADARMODE_PRI_SEQUENCE'
GO

/* RADARMODE -> RADARMODE_RF_SEQUENCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE -> RADARMODE_RF_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_RADARMODE_TO_RADARMODE_RF_SEQUENCE'
GO

/* �� ������ -> ���ü ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������ -> ���ü ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_AETDATA'
GO

/* �� ������ -> LOB ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�� ������ -> LOB ������', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_LOBDATA'
GO