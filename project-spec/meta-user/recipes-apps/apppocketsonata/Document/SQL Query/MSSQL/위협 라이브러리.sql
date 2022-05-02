/* ELINT */
USE [ELINT]
GO

/* THREAT */
CREATE TABLE [THREAT] (
	[THREAT_INDEX] [INT] NOT NULL,  /* ���� �ε��� */
	[RADARMODE_NAME] [VARCHAR](10) NOT NULL,  /* ���̴����� */
	[THREAT_NAME] [VARCHAR](10),  /* ������ */
	[LATITUDE] [FLOAT],  /* ���� */
	[LONGITUDE] [FLOAT],  /* �浵 */
	[SITE_NAME] [VARCHAR](10),  /* ����Ʈ�� */
	[THREAT_PLATFORM] [VARCHAR](10),  /* �÷��� */
	[DATE_CREATED] [DATETIME],  /* ���� ��¥ */
	[DATE_FIRST_SEEN] [DATETIME],  /* ���� ���� ��¥ */
	[DATE_LAST_SEEN] [DATETIME],  /* �ֱ� ���� ��¥ */
	[ID_RANGE] [FLOAT] /* �ĺ� �ݰ� */
)
GO

/* PK__THREAT__DD4AC47457A20A5B */
ALTER TABLE [THREAT]
	ADD
		CONSTRAINT [PK__THREAT__DD4AC47457A20A5B]
		PRIMARY KEY NONCLUSTERED (
			[THREAT_INDEX] ASC, 
			[RADARMODE_NAME] ASC
		)
GO

/* THREAT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'THREAT', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT'
GO

/* ���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* ���̴����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* ������ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'������', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_NAME'
GO

/* ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LATITUDE'
GO

/* �浵 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�浵', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LONGITUDE'
GO

/* ����Ʈ�� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����Ʈ��', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'SITE_NAME'
GO

/* �÷��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�÷���', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PLATFORM'
GO

/* ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ��¥', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_CREATED'
GO

/* ���� ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ���� ��¥', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* �ֱ� ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ֱ� ���� ��¥', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* �ĺ� �ݰ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ĺ� �ݰ�', 
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

/* RADARMODE */
CREATE TABLE [RADARMODE] (
	[RADARMODE_INDEX] [INT] NOT NULL,  /* ���̴���� �ε��� */
	[RADARMODE_NAME] [VARCHAR](10) NOT NULL,  /* ���̴����� */
	[MODECODE] [VARCHAR](20),  /* ����ȣ */
	[DATE_CREATED] [DATETIME],  /* ���� ��¥ */
	[DATE_LAST_UPDATED] [DATETIME],  /* DATE_LAST_UPDATED */
	[DATE_FIRST_SEEN] [DATETIME],  /* ���� ���� ��¥ */
	[DATE_LAST_SEEN] [DATETIME],  /* �ֱ� ���� ��¥ */
	[PLATFORM] [VARCHAR](10),  /* �÷��� */
	[SIGNAL_TYPE] [TINYINT],  /* ��ȣ ���� */
	[RF_TYPE] [TINYINT] NOT NULL,  /* RF ���� */
	[RF_TYPICAL_MIN] [FLOAT],  /* RF ��ǥ �ּ� */
	[RF_TYPICAL_MAX] [FLOAT],  /* RF ��ǥ �ִ� */
	[RF_PATTERN_TYPE] [TINYINT],  /* RF ���� ���� */
	[RF_NUM_POSITIONS] [TINYINT],  /* RF �� ���� */
	[RF_PATTERN_PERIOD_MIN] [FLOAT],  /* RF ���� �ֱ� �ּ� */
	[RF_PATTERN_PERIOD_MAX] [FLOAT],  /* RF ���� �ֱ� �ִ� */
	[PRI_TYPE] [TINYINT] NOT NULL,  /* PRI ���� */
	[PRI_TYPICAL_MIN] [FLOAT],  /* PRI ��ǥ �ּ� */
	[PRI_TYPICAL_MAX] [FLOAT],  /* PRI ��ǥ �ִ� */
	[PRI_PATTERN_TYPE] [TINYINT],  /* PRI ���� ���� */
	[PRI_NUM_POSITIONS] [TINYINT],  /* PRI_NUM_POSITIONS */
	[PRI_PATTERN_PERIOD_MIN] [FLOAT],  /* PRI ���� �ֱ� �ּ� */
	[PRI_PATTERN_PERIOD_MAX] [FLOAT],  /* PRI ���� �ֱ� �ִ� */
	[PW_TYPICAL_MIN] [FLOAT],  /* �޽��� ��ǥ �ּ� */
	[PW_TYPICAL_MAX] [FLOAT],  /* �޽��� ��ǥ �ִ� */
	[VALIDATION] [TINYINT],  /* ��ȿ */
	[PRIORITY] [INT] DEFAULT 0 /* �켱���� */
)
GO

/* PK__RADARMOD__5D8D6E820428B272 */
ALTER TABLE [RADARMODE]
	ADD
		CONSTRAINT [PK__RADARMOD__5D8D6E820428B272]
		PRIMARY KEY NONCLUSTERED (
			[RADARMODE_INDEX] ASC
		)
GO

/* RADARMODE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴� ��� �Դϴ�.', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* ���̴����� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴�����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* ����ȣ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'����ȣ', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'MODECODE'
GO

/* ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ��¥', 
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

/* ���� ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���� ���� ��¥', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* �ֱ� ���� ��¥ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�ֱ� ���� ��¥', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* �÷��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�÷���', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM'
GO

/* ��ȣ ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȣ ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* RF ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPE'
GO

/* RF ��ǥ �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ��ǥ �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MIN'
GO

/* RF ��ǥ �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ��ǥ �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MAX'
GO

/* RF ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ���� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_TYPE'
GO

/* RF �� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF �� ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_NUM_POSITIONS'
GO

/* RF ���� �ֱ� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ���� �ֱ� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MIN'
GO

/* RF ���� �ֱ� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ���� �ֱ� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MAX'
GO

/* PRI ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI ��ǥ �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ��ǥ �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MIN'
GO

/* PRI ��ǥ �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ��ǥ �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MAX'
GO

/* PRI ���� ���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� ����', 
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

/* PRI ���� �ֱ� �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� �ֱ� �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MIN'
GO

/* PRI ���� �ֱ� �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ���� �ֱ� �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MAX'
GO

/* �޽��� ��ǥ �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� ��ǥ �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MIN'
GO

/* �޽��� ��ǥ �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�޽��� ��ǥ �ִ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MAX'
GO

/* ��ȿ */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'��ȿ', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'VALIDATION'
GO

/* �켱���� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'�켱����', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRIORITY'
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

/* RADARMODE_RF_SEQUENCE */
CREATE TABLE [RADARMODE_RF_SEQUENCE] (
	[RADARMODE_INDEX] [INT] NOT NULL,  /* ���̴���� �ε��� */
	[RF_SEQ_ID] [INT] NOT NULL,  /* RF_SEQ_ID */
	[RF_SEQ_NAME] [VARCHAR](20),  /* RF �������� */
	[RF_MIN] [FLOAT],  /* RF �ּ� */
	[RF_MAX] [FLOAT] /* RF �ִ� */
)
GO

/* PK__RADARMOD__F4541D42173876EA */
ALTER TABLE [RADARMODE_RF_SEQUENCE]
	ADD
		CONSTRAINT [PK__RADARMOD__F4541D42173876EA]
		PRIMARY KEY NONCLUSTERED (
			[RADARMODE_INDEX] ASC, 
			[RF_SEQ_ID] ASC
		)
GO

/* RADARMODE_RF_SEQUENCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_RF_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* RF_SEQ_ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF_SEQ_ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_SEQ_ID'
GO

/* RF �������� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF ��������', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_SEQ_NAME'
GO

/* RF �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_MIN'
GO

/* RF �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF �ִ�', 
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

/* RADARMODE_PRI_SEQUENCE */
CREATE TABLE [RADARMODE_PRI_SEQUENCE] (
	[RADARMODE_INDEX] [INT] NOT NULL,  /* ���̴���� �ε��� */
	[PRI_SEQ_ID] [INT] NOT NULL,  /* PRI ������ ID */
	[PRI_SEQ_NAME] [VARCHAR](20),  /* PRI �������� */
	[PRI_MIN] [FLOAT],  /* PRI �ּ� */
	[PRI_MAX] [FLOAT] /* PRI �ִ� */
)
GO

/* PK__RADARMOD__F56ABC074ADECD96 */
ALTER TABLE [RADARMODE_PRI_SEQUENCE]
	ADD
		CONSTRAINT [PK__RADARMOD__F56ABC074ADECD96]
		PRIMARY KEY NONCLUSTERED (
			[RADARMODE_INDEX] ASC, 
			[PRI_SEQ_ID] ASC
		)
GO

/* RADARMODE_PRI_SEQUENCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE_PRI_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE'
GO

/* ���̴���� �ε��� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'���̴���� �ε���', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* PRI ������ ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ������ ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_ID'
GO

/* PRI �������� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI ��������', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_NAME'
GO

/* PRI �ּ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ּ�', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI �ִ� */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI �ִ�', 
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
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE -> RADARMODE_RF_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_RADARMODE_TO_RADARMODE_RF_SEQUENCE'
GO

/* RADARMODE -> RADARMODE_PRI_SEQUENCE */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RADARMODE -> RADARMODE_PRI_SEQUENCE', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_RADARMODE_TO_RADARMODE_PRI_SEQUENCE'
GO