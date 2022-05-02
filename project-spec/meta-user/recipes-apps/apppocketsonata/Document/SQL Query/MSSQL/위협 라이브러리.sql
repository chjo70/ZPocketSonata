/* ELINT */
USE [ELINT]
GO

/* THREAT */
CREATE TABLE [THREAT] (
	[THREAT_INDEX] [INT] NOT NULL,  /* 위협 인덱스 */
	[RADARMODE_NAME] [VARCHAR](10) NOT NULL,  /* 레이더모드명 */
	[THREAT_NAME] [VARCHAR](10),  /* 위협명 */
	[LATITUDE] [FLOAT],  /* 위도 */
	[LONGITUDE] [FLOAT],  /* 경도 */
	[SITE_NAME] [VARCHAR](10),  /* 싸이트명 */
	[THREAT_PLATFORM] [VARCHAR](10),  /* 플레폼 */
	[DATE_CREATED] [DATETIME],  /* 생성 날짜 */
	[DATE_FIRST_SEEN] [DATETIME],  /* 최초 접촉 날짜 */
	[DATE_LAST_SEEN] [DATETIME],  /* 최근 접촉 날짜 */
	[ID_RANGE] [FLOAT] /* 식별 반경 */
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

/* 위협 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* 레이더모드명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드명', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* 위협명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협명', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_NAME'
GO

/* 위도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위도', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LATITUDE'
GO

/* 경도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'경도', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LONGITUDE'
GO

/* 싸이트명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'싸이트명', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'SITE_NAME'
GO

/* 플레폼 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'플레폼', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PLATFORM'
GO

/* 생성 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'생성 날짜', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_CREATED'
GO

/* 최초 접촉 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최초 접촉 날짜', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* 최근 접촉 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최근 접촉 날짜', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* 식별 반경 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'식별 반경', 
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
	[RADARMODE_INDEX] [INT] NOT NULL,  /* 레이더모드 인덱스 */
	[RADARMODE_NAME] [VARCHAR](10) NOT NULL,  /* 레이더모드명 */
	[MODECODE] [VARCHAR](20),  /* 모드부호 */
	[DATE_CREATED] [DATETIME],  /* 생성 날짜 */
	[DATE_LAST_UPDATED] [DATETIME],  /* DATE_LAST_UPDATED */
	[DATE_FIRST_SEEN] [DATETIME],  /* 최초 접촉 날짜 */
	[DATE_LAST_SEEN] [DATETIME],  /* 최근 접촉 날짜 */
	[PLATFORM] [VARCHAR](10),  /* 플레폼 */
	[SIGNAL_TYPE] [TINYINT],  /* 신호 형태 */
	[RF_TYPE] [TINYINT] NOT NULL,  /* RF 형태 */
	[RF_TYPICAL_MIN] [FLOAT],  /* RF 대표 최소 */
	[RF_TYPICAL_MAX] [FLOAT],  /* RF 대표 최대 */
	[RF_PATTERN_TYPE] [TINYINT],  /* RF 패턴 형태 */
	[RF_NUM_POSITIONS] [TINYINT],  /* RF 값 개수 */
	[RF_PATTERN_PERIOD_MIN] [FLOAT],  /* RF 패턴 주기 최소 */
	[RF_PATTERN_PERIOD_MAX] [FLOAT],  /* RF 패턴 주기 최대 */
	[PRI_TYPE] [TINYINT] NOT NULL,  /* PRI 형태 */
	[PRI_TYPICAL_MIN] [FLOAT],  /* PRI 대표 최소 */
	[PRI_TYPICAL_MAX] [FLOAT],  /* PRI 대표 최대 */
	[PRI_PATTERN_TYPE] [TINYINT],  /* PRI 패턴 형태 */
	[PRI_NUM_POSITIONS] [TINYINT],  /* PRI_NUM_POSITIONS */
	[PRI_PATTERN_PERIOD_MIN] [FLOAT],  /* PRI 패턴 주기 최소 */
	[PRI_PATTERN_PERIOD_MAX] [FLOAT],  /* PRI 패턴 주기 최대 */
	[PW_TYPICAL_MIN] [FLOAT],  /* 펄스폭 대표 최소 */
	[PW_TYPICAL_MAX] [FLOAT],  /* 펄스폭 대표 최대 */
	[VALIDATION] [TINYINT],  /* 유효 */
	[PRIORITY] [INT] DEFAULT 0 /* 우선순위 */
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

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더 모드 입니다.', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* 레이더모드명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드명', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* 모드부호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'모드부호', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'MODECODE'
GO

/* 생성 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'생성 날짜', 
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

/* 최초 접촉 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최초 접촉 날짜', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_FIRST_SEEN'
GO

/* 최근 접촉 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최근 접촉 날짜', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'DATE_LAST_SEEN'
GO

/* 플레폼 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'플레폼', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM'
GO

/* 신호 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* RF 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPE'
GO

/* RF 대표 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 대표 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MIN'
GO

/* RF 대표 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 대표 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_TYPICAL_MAX'
GO

/* RF 패턴 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 패턴 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_TYPE'
GO

/* RF 값 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 값 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_NUM_POSITIONS'
GO

/* RF 패턴 주기 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 패턴 주기 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MIN'
GO

/* RF 패턴 주기 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 패턴 주기 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RF_PATTERN_PERIOD_MAX'
GO

/* PRI 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI 대표 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 대표 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MIN'
GO

/* PRI 대표 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 대표 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPICAL_MAX'
GO

/* PRI 패턴 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 형태', 
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

/* PRI 패턴 주기 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 주기 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MIN'
GO

/* PRI 패턴 주기 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 주기 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MAX'
GO

/* 펄스폭 대표 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 대표 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MIN'
GO

/* 펄스폭 대표 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 대표 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PW_TYPICAL_MAX'
GO

/* 유효 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'유효', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'VALIDATION'
GO

/* 우선순위 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'우선순위', 
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
	[RADARMODE_INDEX] [INT] NOT NULL,  /* 레이더모드 인덱스 */
	[RF_SEQ_ID] [INT] NOT NULL,  /* RF_SEQ_ID */
	[RF_SEQ_NAME] [VARCHAR](20),  /* RF 시퀀스명 */
	[RF_MIN] [FLOAT],  /* RF 최소 */
	[RF_MAX] [FLOAT] /* RF 최대 */
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

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 인덱스', 
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

/* RF 시퀀스명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 시퀀스명', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_SEQ_NAME'
GO

/* RF 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_MIN'
GO

/* RF 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 최대', 
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
	[RADARMODE_INDEX] [INT] NOT NULL,  /* 레이더모드 인덱스 */
	[PRI_SEQ_ID] [INT] NOT NULL,  /* PRI 시퀀스 ID */
	[PRI_SEQ_NAME] [VARCHAR](20),  /* PRI 시퀀스명 */
	[PRI_MIN] [FLOAT],  /* PRI 최소 */
	[PRI_MAX] [FLOAT] /* PRI 최대 */
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

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* PRI 시퀀스 ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 시퀀스 ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_ID'
GO

/* PRI 시퀀스명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 시퀀스명', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_SEQ_NAME'
GO

/* PRI 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최대', 
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