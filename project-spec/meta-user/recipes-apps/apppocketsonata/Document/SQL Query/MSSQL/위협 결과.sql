/* ELINT */
USE [ELINT]
GO

/* 빔 포지션 */
CREATE TABLE [ABT_POSITION] (
	[SEQ_TYPE] [TINYINT] NOT NULL,  /* 시퀀스 형태 */
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[LOBID] [int] NOT NULL,  /* LOB 번호 */
	[PDWID] [INT] NOT NULL,  /* PDW 번호 */
	[PLOBID] [INT] NOT NULL,  /* 가상 LOB 번호 */
	[AETID] [int] NOT NULL,  /* 방사체 번호 */
	[ABTID] [int] NOT NULL,  /* 빔 번호 */
	[POSITION_COUNT] [tinyint],  /* 값 개수 */
	[SEQ_01] [float],  /* 값 #1 */
	[SEQ_02] [float],  /* 값 #2 */
	[SEQ_03] [float],  /* 값 #3 */
	[SEQ_04] [float],  /* 값 #4 */
	[SEQ_05] [float],  /* 값 #5 */
	[SEQ_06] [float],  /* 값 #6 */
	[SEQ_07] [float],  /* 값 #7 */
	[SEQ_08] [float],  /* 값 #8 */
	[SEQ_09] [float],  /* 값 #9 */
	[SEQ_10] [float],  /* 값 #10 */
	[SEQ_11] [float],  /* 값 #11 */
	[SEQ_12] [float],  /* 값 #12 */
	[SEQ_13] [float],  /* 값 #13 */
	[SEQ_14] [float],  /* 값 #14 */
	[SEQ_15] [float],  /* 값 #15 */
	[SEQ_16] [float],  /* 값 #16 */
	[SEQ_17] [float],  /* 값 #17 */
	[SEQ_18] [float],  /* 값 #18 */
	[SEQ_19] [float],  /* 값 #19 */
	[SEQ_20] [float],  /* 값 #20 */
	[SEQ_21] [float],  /* 값 #21 */
	[SEQ_22] [float],  /* 값 #22 */
	[SEQ_23] [float],  /* 값 #23 */
	[SEQ_24] [float],  /* 값 #24 */
	[SEQ_25] [float],  /* 값 #25 */
	[SEQ_26] [float],  /* 값 #26 */
	[SEQ_27] [float],  /* 값 #27 */
	[SEQ_28] [float],  /* 값 #28 */
	[SEQ_29] [float],  /* 값 #29 */
	[SEQ_30] [float],  /* 값 #30 */
	[SEQ_31] [float],  /* 값 #31 */
	[SEQ_32] [float] /* 값 #32 */
)
	ON [PRIMARY]
GO

/* 빔 포지션 기본키 */
ALTER TABLE [ABT_POSITION]
	ADD
		CONSTRAINT [PK_ABT_POSITION]
		PRIMARY KEY NONCLUSTERED (
			[SEQ_TYPE] ASC, 
			[OP_INIT_ID] ASC, 
			[LOBID] ASC
		)
GO

/* 빔 포지션 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 포지션', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION'
GO

/* 시퀀스 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'시퀀스 형태', 
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

/* LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* PDW 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* 가상 LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'가상 LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* 방사체 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방사체 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* 빔 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* 값 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'POSITION_COUNT'
GO

/* 값 #1 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #1', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_01'
GO

/* 값 #2 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #2', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_02'
GO

/* 값 #3 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #3', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_03'
GO

/* 값 #4 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #4', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_04'
GO

/* 값 #5 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #5', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_05'
GO

/* 값 #6 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #6', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_06'
GO

/* 값 #7 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #7', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_07'
GO

/* 값 #8 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #8', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_08'
GO

/* 값 #9 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #9', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_09'
GO

/* 값 #10 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #10', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_10'
GO

/* 값 #11 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #11', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_11'
GO

/* 값 #12 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #12', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_12'
GO

/* 값 #13 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #13', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_13'
GO

/* 값 #14 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #14', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_14'
GO

/* 값 #15 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #15', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_15'
GO

/* 값 #16 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #16', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_16'
GO

/* 값 #17 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #17', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_17'
GO

/* 값 #18 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #18', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_18'
GO

/* 값 #19 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #19', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_19'
GO

/* 값 #20 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #20', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_20'
GO

/* 값 #21 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #21', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_21'
GO

/* 값 #22 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #22', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_22'
GO

/* 값 #23 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #23', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_23'
GO

/* 값 #24 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #24', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_24'
GO

/* 값 #25 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #25', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_25'
GO

/* 값 #26 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #26', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_26'
GO

/* 값 #27 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #27', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_27'
GO

/* 값 #28 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #28', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_28'
GO

/* 값 #29 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #29', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_29'
GO

/* 값 #30 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #30', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_30'
GO

/* 값 #31 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #31', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_31'
GO

/* 값 #32 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #32', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_32'
GO

/* 빔 포지션 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 포지션 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_ABT_POSITION'
GO

/* 빔 포지션 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 포지션 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'INDEX', @level2name=N'PK_ABT_POSITION'
GO

/* 빔 데이터 */
CREATE TABLE [ABTDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW 번호 */
	[PLOBID] [INT] NOT NULL,  /* 가상 LOB 번호 */
	[LOBID] [int] NOT NULL,  /* LOB 번호 */
	[AETID] [int] NOT NULL,  /* 방사체 번호 */
	[ABTID] [int] NOT NULL,  /* 빔 번호 */
	[FIRST_TIME] [datetime],  /* 최초 시간 */
	[LAST_TIME] [datetime],  /* 최근 시간 */
	[SIGNAL_TYPE] [tinyint],  /* 신호 형태 */
	[NUM_LOB] [int],  /* LOB 개수 */
	[BEAM_VALIDITY] [int],  /* 빔 유효성 */
	[FREQ_TYPE] [tinyint],  /* 주차수 형태 */
	[FREQ_PATTERN_TYPE] [tinyint],  /* 주파수 패턴 형태 */
	[FREQ_PATTERN_PERIOD_MEAN] [float],  /* FREQ_PATTERN_PERIOD_MEAN */
	[FREQ_PATTERN_PERIOD_MIN] [float],  /* FREQ_PATTERN_PERIOD_MIN */
	[FREQ_PATTERN_PERIOD_MAX] [float],  /* FREQ_PATTERN_PERIOD_MAX */
	[FREQ_MEAN] [float],  /* 주파수 평균 */
	[FREQ_MIN] [float],  /* 주파수 최소 */
	[FREQ_MAX] [float],  /* 주파수 최대 */
	[FREQ_POSITION_COUNT] [TINYINT],  /* 주파수 값 개수 */
	[FREQ_ELEMENT_COUNT] [TINYINT],  /* 주파수 요소 개수 */
	[PRI_TYPE] [TINYINT],  /* PRI 형태 */
	[PRI_PATTERN_TYPE] [TINYINT],  /* PRI 패턴 형태 */
	[PRI_PATTERN_PERIOD_MEAN] [float],  /* PRI 패턴 주기 평균 */
	[PRI_PATTERN_PERIOD_MIN] [float],  /* PRI 패턴 주기 최소 */
	[PRI_PATTERN_PERIOD_MAX] [float],  /* PRI 패턴 주기 최대 */
	[PRI_MEAN] [float],  /* PRI 평균 */
	[PRI_MIN] [float],  /* PRI 최소 */
	[PRI_MAX] [float],  /* PRI 최대 */
	[PRI_JITTER_RATIO] [float],  /* PRI 지터율 */
	[PRI_POSITION_COUNT] [TINYINT],  /* PRI 값 개수 */
	[PRI_ELEMENT_COUNT] [TINYINT],  /* PRI 요소 개수 */
	[PW_MEAN] [float],  /* 펄스폭 평균 */
	[PW_MIN] [float],  /* 펄스폭 최소 */
	[PW_MAX] [float],  /* 펄스폭 최대 */
	[PA_MEAN] [float],  /* 신호세기 평균 */
	[PA_MIN] [float],  /* 신호세기 최소 */
	[PA_MAX] [float],  /* 신호세기 최대 */
	[TOTAL_PDW] [int],  /* PDW 총개수 */
	[RADARMODE_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* 레이더모드명 */
	[RADARMODE_INDEX] [smallint],  /* 레이더모드 인덱스 */
	[THREAT_INDEX] [smallint],  /* 위협 인덱스 */
	[PE_VALID] [TINYINT],  /* 위치 유효성 */
	[PE_LATITUDE] [float],  /* 위치 위도 */
	[PE_LONGITUDE] [float],  /* 위치 경도 */
	[PE_CEP] [float],  /* 위치 CEP */
	[PE_MAJOR_AXIS] [float],  /* 위치 장축 */
	[PE_MINOR_AXIS] [float],  /* 위치 단축 */
	[PE_THETA] [float],  /* 위치 기울기 */
	[PE_DISTANCE] [float],  /* 위치 거리오차 */
	[ALARM_TIME] [datetime],  /* 경보 시간 */
	[STAT] [TINYINT] /* 상태 */
)
	ON [PRIMARY]
GO

/* 빔 데이터 기본키 */
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

/* 빔 데이터 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'ABT 데이터 입니다.', 
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

/* PDW 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* 가상 LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'가상 LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* 방사체 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방사체 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* 빔 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* 최초 시간 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최초 시간', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FIRST_TIME'
GO

/* 최근 시간 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최근 시간', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'LAST_TIME'
GO

/* 신호 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* LOB 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_LOB'
GO

/* 빔 유효성 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 유효성', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'BEAM_VALIDITY'
GO

/* 주차수 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주차수 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_TYPE'
GO

/* 주파수 패턴 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 패턴 형태', 
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

/* 주파수 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* 주파수 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* 주파수 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* 주파수 값 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 값 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_POSITION_COUNT'
GO

/* 주파수 요소 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 요소 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_ELEMENT_COUNT'
GO

/* PRI 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI 패턴 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI 패턴 주기 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 주기 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MEAN'
GO

/* PRI 패턴 주기 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 주기 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MIN'
GO

/* PRI 패턴 주기 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 주기 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD_MAX'
GO

/* PRI 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI 지터율 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 지터율', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_JITTER_RATIO'
GO

/* PRI 값 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 값 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_POSITION_COUNT'
GO

/* PRI 요소 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 요소 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_ELEMENT_COUNT'
GO

/* 펄스폭 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* 펄스폭 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* 펄스폭 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* 신호세기 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* 신호세기 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* 신호세기 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* PDW 총개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 총개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'TOTAL_PDW'
GO

/* 레이더모드명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* 위협 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* 위치 유효성 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 유효성', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_VALID'
GO

/* 위치 위도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 위도', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LATITUDE'
GO

/* 위치 경도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 경도', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LONGITUDE'
GO

/* 위치 CEP */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 CEP', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_CEP'
GO

/* 위치 장축 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 장축', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MAJOR_AXIS'
GO

/* 위치 단축 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 단축', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MINOR_AXIS'
GO

/* 위치 기울기 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 기울기', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_THETA'
GO

/* 위치 거리오차 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 거리오차', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_DISTANCE'
GO

/* 경보 시간 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'경보 시간', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'ALARM_TIME'
GO

/* 상태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'상태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'COLUMN', @level2name=N'STAT'
GO

/* 빔 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_ABTDATA'
GO

/* 빔 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'INDEX', @level2name=N'PK_ABTDATA'
GO

/* LOB 포지션 */
CREATE TABLE [LOB_POSITION] (
	[SEQ_TYPE] [TINYINT] NOT NULL,  /* 시퀀스 형태 */
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[LOBID] [int] NOT NULL,  /* LOB 번호 */
	[PDWID] [INT] NOT NULL,  /* PDW 번호 */
	[PLOBID] [INT] NOT NULL,  /* 가상 LOB 번호 */
	[AETID] [int] NOT NULL,  /* 방사체 번호 */
	[ABTID] [int] NOT NULL,  /* 빔 번호 */
	[POSITION_COUNT] [tinyint],  /* 값 개수 */
	[SEQ_01] [float],  /* 값 #1 */
	[SEQ_02] [float],  /* 값 #2 */
	[SEQ_03] [float],  /* 값 #3 */
	[SEQ_04] [float],  /* 값 #4 */
	[SEQ_05] [float],  /* 값 #5 */
	[SEQ_06] [float],  /* 값 #6 */
	[SEQ_07] [float],  /* 값 #7 */
	[SEQ_08] [float],  /* 값 #8 */
	[SEQ_09] [float],  /* 값 #9 */
	[SEQ_10] [float],  /* 값 #10 */
	[SEQ_11] [float],  /* 값 #11 */
	[SEQ_12] [float],  /* 값 #12 */
	[SEQ_13] [float],  /* 값 #13 */
	[SEQ_14] [float],  /* 값 #14 */
	[SEQ_15] [float],  /* 값 #15 */
	[SEQ_16] [float],  /* 값 #16 */
	[SEQ_17] [float],  /* 값 #17 */
	[SEQ_18] [float],  /* 값 #18 */
	[SEQ_19] [float],  /* 값 #19 */
	[SEQ_20] [float],  /* 값 #20 */
	[SEQ_21] [float],  /* 값 #21 */
	[SEQ_22] [float],  /* 값 #22 */
	[SEQ_23] [float],  /* 값 #23 */
	[SEQ_24] [float],  /* 값 #24 */
	[SEQ_25] [float],  /* 값 #25 */
	[SEQ_26] [float],  /* 값 #26 */
	[SEQ_27] [float],  /* 값 #27 */
	[SEQ_28] [float],  /* 값 #28 */
	[SEQ_29] [float],  /* 값 #29 */
	[SEQ_30] [float],  /* 값 #30 */
	[SEQ_31] [float],  /* 값 #31 */
	[SEQ_32] [float] /* 값 #32 */
)
	ON [PRIMARY]
GO

/* LOB 포지션 기본키 */
ALTER TABLE [LOB_POSITION]
	ADD
		CONSTRAINT [PK_LOB_POSITION]
		PRIMARY KEY NONCLUSTERED (
			[SEQ_TYPE] ASC, 
			[OP_INIT_ID] ASC, 
			[LOBID] ASC
		)
GO

/* LOB 포지션 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 포지션', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION'
GO

/* 시퀀스 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'시퀀스 형태', 
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

/* LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* PDW 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* 가상 LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'가상 LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* 방사체 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방사체 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* 빔 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* 값 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'POSITION_COUNT'
GO

/* 값 #1 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #1', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_01'
GO

/* 값 #2 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #2', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_02'
GO

/* 값 #3 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #3', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_03'
GO

/* 값 #4 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #4', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_04'
GO

/* 값 #5 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #5', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_05'
GO

/* 값 #6 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #6', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_06'
GO

/* 값 #7 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #7', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_07'
GO

/* 값 #8 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #8', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_08'
GO

/* 값 #9 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #9', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_09'
GO

/* 값 #10 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #10', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_10'
GO

/* 값 #11 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #11', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_11'
GO

/* 값 #12 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #12', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_12'
GO

/* 값 #13 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #13', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_13'
GO

/* 값 #14 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #14', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_14'
GO

/* 값 #15 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #15', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_15'
GO

/* 값 #16 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #16', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_16'
GO

/* 값 #17 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #17', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_17'
GO

/* 값 #18 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #18', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_18'
GO

/* 값 #19 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #19', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_19'
GO

/* 값 #20 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #20', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_20'
GO

/* 값 #21 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #21', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_21'
GO

/* 값 #22 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #22', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_22'
GO

/* 값 #23 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #23', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_23'
GO

/* 값 #24 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #24', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_24'
GO

/* 값 #25 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #25', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_25'
GO

/* 값 #26 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #26', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_26'
GO

/* 값 #27 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #27', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_27'
GO

/* 값 #28 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #28', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_28'
GO

/* 값 #29 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #29', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_29'
GO

/* 값 #30 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #30', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_30'
GO

/* 값 #31 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #31', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_31'
GO

/* 값 #32 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'값 #32', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'COLUMN', @level2name=N'SEQ_32'
GO

/* LOB 포지션 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 포지션 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_LOB_POSITION'
GO

/* LOB 포지션 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 포지션 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOB_POSITION', 
	@level2type=N'INDEX', @level2name=N'PK_LOB_POSITION'
GO

/* RADARMODE */
CREATE TABLE [RADARMODE] (
	[RADARMODE_INDEX] [int] NOT NULL,  /* 레이더모드 인덱스 */
	[RADARMODE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS NOT NULL,  /* 레이더모드명 */
	[MODECODE] [VARCHAR](20),  /* 모드부호 */
	[DATE_CREATED] [datetime],  /* 생성 날짜 */
	[DATE_LAST_UPDATED] [datetime],  /* DATE_LAST_UPDATED */
	[DATE_FIRST_SEEN] [datetime],  /* DATE_FIRST_SEEN */
	[DATE_LAST_SEEN] [datetime],  /* DATE_LAST_SEEN */
	[PLATFORM] [tinyint],  /* 플레폼 */
	[SIGNAL_TYPE] [tinyint],  /* 신호 형태 */
	[RF_TYPE] [tinyint] NOT NULL,  /* RF 형태 */
	[RF_TYPICAL_MIN] [float],  /* RF_TYPICAL_MIN */
	[RF_TYPICAL_MAX] [float],  /* RF_TYPICAL_MAX */
	[RF_PATTERN_TYPE] [tinyint],  /* RF_PATTERN_TYPE */
	[RF_NUM_POSITIONS] [tinyint],  /* RF_NUM_POSITIONS */
	[RF_PATTERN_PERIOD_MIN] [float],  /* RF_PATTERN_PERIOD_MIN */
	[RF_PATTERN_PERIOD_MAX] [float],  /* RF_PATTERN_PERIOD_MAX */
	[PRI_TYPE] [tinyint] NOT NULL,  /* PRI 형태 */
	[PRI_TYPICAL_MIN] [float],  /* PRI_TYPICAL_MIN */
	[PRI_TYPICAL_MAX] [float],  /* PRI_TYPICAL_MAX */
	[PRI_PATTERN_TYPE] [tinyint],  /* PRI_PATTERN_TYPE */
	[PRI_NUM_POSITIONS] [tinyint],  /* PRI_NUM_POSITIONS */
	[PRI_PATTERN_PERIOD_MIN] [float],  /* PRI_PATTERN_PERIOD_MIN */
	[PRI_PATTERN_PERIOD_MAX] [float],  /* PRI_PATTERN_PERIOD_MAX */
	[PW_TYPICAL_MIN] [float],  /* PW_TYPICAL_MIN */
	[PW_TYPICAL_MAX] [float],  /* PW_TYPICAL_MAX */
	[VALIDATION] [tinyint],  /* VALIDATION */
	[PRIORITY] [INT] DEFAULT 0 /* 우선순위 */
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

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더 모드 입니다.', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* 레이더모드명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* 모드부호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'모드부호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'MODECODE'
GO

/* 생성 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'생성 날짜', 
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

/* 플레폼 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'플레폼', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM'
GO

/* 신호 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* RF 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 형태', 
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

/* PRI 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 형태', 
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

/* 우선순위 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'우선순위', 
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
	[RADARMODE_INDEX] [int] NOT NULL,  /* 레이더모드 인덱스 */
	[PRI_SEQ_ID] [int] NOT NULL,  /* PRI_SEQ_ID */
	[PRI_SEQ_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* PRI_SEQ_NAME */
	[PRI_MIN] [float],  /* PRI 최소 */
	[PRI_MAX] [float] /* PRI 최대 */
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

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 인덱스', 
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

/* PRI 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_PRI_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최대', 
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
	[RADARMODE_INDEX] [int] NOT NULL,  /* 레이더모드 인덱스 */
	[RF_SEQ_ID] [int] NOT NULL,  /* RF_SEQ_ID */
	[RF_SEQ_NAME] [varchar](20) COLLATE Korean_Wansung_CI_AS,  /* RF_SEQ_NAME */
	[RF_MIN] [float],  /* RF 최소 */
	[RF_MAX] [float] /* RF 최대 */
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

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 인덱스', 
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

/* RF 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RADARMODE_RF_SEQUENCE', 
	@level2type=N'COLUMN', @level2name=N'RF_MIN'
GO

/* RF 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'RF 최대', 
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
	[THREAT_INDEX] [int] NOT NULL,  /* 위협 인덱스 */
	[RADARMODE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS NOT NULL,  /* 레이더모드명 */
	[THREAT_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS,  /* 위협명 */
	[LATITUDE] [float],  /* 위도 */
	[LONGITUDE] [float],  /* 경도 */
	[SITE_NAME] [varchar](10) COLLATE Korean_Wansung_CI_AS,  /* 싸이트명 */
	[THREAT_PLATFORM] [tinyint],  /* 플레폼 */
	[DATE_CREATED] [datetime],  /* 생성 날짜 */
	[DATE_FIRST_SEEN] [datetime],  /* DATE_FIRST_SEEN */
	[DATE_LAST_SEEN] [datetime],  /* DATE_LAST_SEEN */
	[ID_RANGE] [float] /* 식별 반경 */
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

/* 위협 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* 레이더모드명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* 위협명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_NAME'
GO

/* 위도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위도', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LATITUDE'
GO

/* 경도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'경도', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'LONGITUDE'
GO

/* 싸이트명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'싸이트명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'SITE_NAME'
GO

/* 플레폼 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'플레폼', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'THREAT', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PLATFORM'
GO

/* 생성 날짜 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'생성 날짜', 
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

/* 식별 반경 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'식별 반경', 
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

/* 방사체 데이터 */
CREATE TABLE [AETDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW 번호 */
	[PLOBID] [INT] NOT NULL,  /* 가상 LOB 번호 */
	[LOBID] [int] NOT NULL,  /* LOB 번호 */
	[AETID] [int] NOT NULL,  /* 방사체 번호 */
	[ABTID] [int] NOT NULL,  /* 빔 번호 */
	[FIRST_TIME] [datetime],  /* 최초 시간 */
	[LAST_TIME] [datetime],  /* 최근 시간 */
	[PRIMARY_ELNOT] [varchar](20),  /* 1차 ELNOT */
	[PRIMARY_MODECODE] [varchar](20),  /* 1차 모드 부호 */
	[RADARMODE_NAME] [varchar](20),  /* 레이더모드명 */
	[NICK_NAME] [varchar](20),  /* 별명 */
	[FUNC_CODE] [varchar](20),  /* 기능 코드 */
	[PLATFORM_TYPE] [varchar](20),  /* 플랫폼 형태 */
	[RADARMODE_PRIORITY] [varchar](20),  /* 레이더모드 우선순위 */
	[RADAR_PRIORITY] [varchar](20),  /* 레이더 우선순위 */
	[PIN_NUM] [INT],  /* 핀 번호 */
	[PLACENAME_KOR] [varchar](20),  /* 위치 한글명 */
	[THREAT_FUNC_CODE] [varchar](20),  /* 위협 기능 코드 */
	[THREAT_PRIORITY] [varchar](20),  /* 위협 우선순위 */
	[RADARMODE_INDEX] [int],  /* 레이더모드 인덱스 */
	[THREAT_INDEX] [int],  /* 위협 인덱스 */
	[VALIDITY] [tinyint],  /* 유효성 */
	[DOA_MEAN] [float],  /* 방위 평균 */
	[DOA_MIN] [float],  /* 최소 방위 */
	[DOA_MAX] [float],  /* 방위 최대 */
	[DOA_DEV] [float],  /* 방위 편차 */
	[FREQ_MEAN] [float],  /* 주파수 평균 */
	[FREQ_MIN] [float],  /* 주파수 최소 */
	[FREQ_MAX] [float],  /* 주파수 최대 */
	[FREQ_DEV] [float],  /* 주파수 편차 */
	[PRI_MEAN] [float],  /* PRI 평균 */
	[PRI_MIN] [float],  /* PRI 최소 */
	[PRI_MAX] [float],  /* PRI 최대 */
	[PRI_DEV] [float],  /* PRI 편차 */
	[PW_MEAN] [float],  /* 펄스폭 평균 */
	[PW_MIN] [float],  /* 펄스폭 최소 */
	[PW_MAX] [float],  /* 펄스폭 최대 */
	[PW_DEV] [float],  /* 펄스폭 편차 */
	[PA_MEAN] [float],  /* 신호세기 평균 */
	[PA_MIN] [float],  /* 신호세기 최소 */
	[PA_MAX] [float],  /* 신호세기 최대 */
	[PA_DEV] [float],  /* 신호세기 편차 */
	[PE_VALID] [tinyint],  /* 위치 유효성 */
	[PE_LATITUDE] [float],  /* 위치 위도 */
	[PE_LONGITUDE] [float],  /* 위치 경도 */
	[PE_HEIGHT] [float],  /* PE_HEIGHT */
	[PE_CEP] [float],  /* 위치 CEP */
	[PE_MAJOR_AXIS] [float],  /* 위치 장축 */
	[PE_MINOR_AXIS] [float],  /* 위치 단축 */
	[PE_THETA] [float],  /* 위치 기울기 */
	[PE_DISTANCE] [float],  /* 위치 거리오차 */
	[STAT] [tinyint],  /* 상태 */
	[NUM_OF_BEAMS] [int],  /* 빔 개수 */
	[NUM_OF_LOBS] [int],  /* LOB 개수 */
	[IDINFO] [varchar](12),  /* 식별 정보 */
	[FINAL_ALARM_TIME] [datetime] /* 최종 경보 시간 */
)
GO

/* 방사체 데이터 기본키 */
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

/* 방사체 데이터 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'AET 데이터 입니다.', 
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

/* PDW 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* 가상 LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'가상 LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* 방사체 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방사체 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* 빔 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* 최초 시간 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최초 시간', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FIRST_TIME'
GO

/* 최근 시간 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최근 시간', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'LAST_TIME'
GO

/* 1차 ELNOT */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'1차 ELNOT', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRIMARY_ELNOT'
GO

/* 1차 모드 부호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'1차 모드 부호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRIMARY_MODECODE'
GO

/* 레이더모드명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* 별명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'별명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NICK_NAME'
GO

/* 기능 코드 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'기능 코드', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FUNC_CODE'
GO

/* 플랫폼 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'플랫폼 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLATFORM_TYPE'
GO

/* 레이더모드 우선순위 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 우선순위', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_PRIORITY'
GO

/* 레이더 우선순위 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더 우선순위', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADAR_PRIORITY'
GO

/* 핀 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'핀 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PIN_NUM'
GO

/* 위치 한글명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 한글명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PLACENAME_KOR'
GO

/* 위협 기능 코드 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협 기능 코드', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_FUNC_CODE'
GO

/* 위협 우선순위 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협 우선순위', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_PRIORITY'
GO

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* 위협 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위협 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'THREAT_INDEX'
GO

/* 유효성 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'유효성', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'VALIDITY'
GO

/* 방위 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방위 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MEAN'
GO

/* 최소 방위 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최소 방위', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MIN'
GO

/* 방위 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방위 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MAX'
GO

/* 방위 편차 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방위 편차', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_DEV'
GO

/* 주파수 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* 주파수 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* 주파수 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* 주파수 편차 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 편차', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_DEV'
GO

/* PRI 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI 편차 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 편차', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_DEV'
GO

/* 펄스폭 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* 펄스폭 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* 펄스폭 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* 펄스폭 편차 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 편차', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_DEV'
GO

/* 신호세기 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* 신호세기 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* 신호세기 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* 신호세기 편차 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 편차', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_DEV'
GO

/* 위치 유효성 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 유효성', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_VALID'
GO

/* 위치 위도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 위도', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_LATITUDE'
GO

/* 위치 경도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 경도', 
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

/* 위치 CEP */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 CEP', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_CEP'
GO

/* 위치 장축 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 장축', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MAJOR_AXIS'
GO

/* 위치 단축 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 단축', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_MINOR_AXIS'
GO

/* 위치 기울기 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 기울기', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_THETA'
GO

/* 위치 거리오차 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위치 거리오차', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'PE_DISTANCE'
GO

/* 상태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'상태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'STAT'
GO

/* 빔 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_OF_BEAMS'
GO

/* LOB 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_OF_LOBS'
GO

/* 식별 정보 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'식별 정보', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'IDINFO'
GO

/* 최종 경보 시간 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최종 경보 시간', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'COLUMN', @level2name=N'FINAL_ALARM_TIME'
GO

/* 방사체 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방사체 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_AETDATA'
GO

/* 방사체 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방사체 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'INDEX', @level2name=N'PK_AETDATA'
GO

/* 수집 데이터 */
CREATE TABLE [RAWDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW 번호 */
	[PLOBID] [INT] NOT NULL,  /* 가상 LOB 번호 */
	[TASK_ID] [CHAR](30),  /* 과제 ID */
	[CREATE_TIME] [DATETIME],  /* 수집 시간(시분초) */
	[CREATE_TIME_MS] [TINYINT],  /* CREATE_TIME_MS */
	[COUNTOFDATA] [SMALLINT],  /* 수집개수 */
	[FILENAME] [char](100),  /* 파일명 */
	[DATA_TYPE] [TINYINT] /* 데이터 형태 */
)
GO

/* 수집 데이터 기본키 */
ALTER TABLE [RAWDATA]
	ADD
		CONSTRAINT [PK_RAWDATA]
		PRIMARY KEY NONCLUSTERED (
			[OP_INIT_ID] ASC, 
			[PDWID] ASC, 
			[PLOBID] ASC
		)
GO

/* 수집 데이터 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집 데이터 입니다.', 
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

/* PDW 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* 가상 LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'가상 LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* 과제 ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'과제 ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'TASK_ID'
GO

/* 수집 시간(시분초) */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집 시간(시분초)', 
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

/* 수집개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'COUNTOFDATA'
GO

/* 파일명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'파일명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'FILENAME'
GO

/* 데이터 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'데이터 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'COLUMN', @level2name=N'DATA_TYPE'
GO

/* 수집 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_RAWDATA'
GO

/* 수집 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'RAWDATA', 
	@level2type=N'INDEX', @level2name=N'PK_RAWDATA'
GO

/* LOB 데이터 */
CREATE TABLE [LOBDATA] (
	[OP_INIT_ID] [INT] NOT NULL,  /* OP_INIT_ID */
	[PDWID] [INT] NOT NULL,  /* PDW 번호 */
	[PLOBID] [INT] NOT NULL,  /* 가상 LOB 번호 */
	[LOBID] [int] NOT NULL,  /* LOB 번호 */
	[AETID] [int] NOT NULL,  /* 방사체 번호 */
	[ABTID] [int] NOT NULL,  /* 빔 번호 */
	[TASK_ID] [varchar](30) NOT NULL,  /* 과제 ID */
	[CONTACT_TIME] [datetime],  /* 접촉 시간(시분초) */
	[CONTACT_TIME_MS] [int],  /* 접촉 시간(ms) */
	[SIGNAL_TYPE] [tinyint],  /* 신호 형태 */
	[DOA_MEAN] [float],  /* 방위 평균 */
	[DOA_MIN] [float],  /* 최소 방위 */
	[DOA_MAX] [float],  /* 방위 최대 */
	[DI_RATIO] [int],  /* 방탐 유효율 */
	[FREQ_TYPE] [tinyint],  /* 주차수 형태 */
	[FREQ_PATTERN_TYPE] [tinyint],  /* 주파수 패턴 형태 */
	[FREQ_PATTERN_PERIOD] [float],  /* 주파수 패턴 주기 */
	[FREQ_MEAN] [float],  /* 주파수 평균 */
	[FREQ_MIN] [float],  /* 주파수 최소 */
	[FREQ_MAX] [float],  /* 주파수 최대 */
	[FREQ_POSITION_COUNT] [tinyint],  /* 주파수 값 개수 */
	[PRI_TYPE] [tinyint],  /* PRI 형태 */
	[PRI_PATTERN_TYPE] [tinyint],  /* PRI 패턴 형태 */
	[PRI_PATTERN_PERIOD] [float],  /* PRI 패턴 주기 */
	[PRI_MEAN] [float],  /* PRI 평균 */
	[PRI_MIN] [float],  /* PRI 최소 */
	[PRI_MAX] [float],  /* PRI 최대 */
	[PRI_JITTER_RATIO] [float],  /* PRI 지터율 */
	[PRI_POSITION_COUNT] [tinyint],  /* PRI 값 개수 */
	[PW_MEAN] [float],  /* 펄스폭 평균 */
	[PW_MIN] [float],  /* 펄스폭 최소 */
	[PW_MAX] [float],  /* 펄스폭 최대 */
	[PA_MEAN] [float],  /* 신호세기 평균 */
	[PA_MIN] [float],  /* 신호세기 최소 */
	[PA_MAX] [float],  /* 신호세기 최대 */
	[IS_STORED_PDW] [tinyint],  /* 저장 여부 */
	[NUM_PDW] [smallint],  /* PDW 개수 */
	[COLLECTOR_ID] [tinyint],  /* 수집소 */
	[LATITUDE] [float],  /* 위도 */
	[LONGITUDE] [float],  /* 경도 */
	[RADARMODE_NAME] [varchar](20),  /* 레이더모드명 */
	[RADARMODE_INDEX] [smallint] /* 레이더모드 인덱스 */
)
GO

/* LOB 데이터 기본키 */
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

/* LOB 데이터 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 데이터 입니다.', 
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

/* PDW 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PDWID'
GO

/* 가상 LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'가상 LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PLOBID'
GO

/* LOB 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'LOBID'
GO

/* 방사체 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방사체 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'AETID'
GO

/* 빔 번호 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 번호', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'ABTID'
GO

/* 과제 ID */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'과제 ID', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'TASK_ID'
GO

/* 접촉 시간(시분초) */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'접촉 시간(시분초)', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'CONTACT_TIME'
GO

/* 접촉 시간(ms) */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'접촉 시간(ms)', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'CONTACT_TIME_MS'
GO

/* 신호 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'SIGNAL_TYPE'
GO

/* 방위 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방위 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MEAN'
GO

/* 최소 방위 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'최소 방위', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MIN'
GO

/* 방위 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방위 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DOA_MAX'
GO

/* 방탐 유효율 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'방탐 유효율', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'DI_RATIO'
GO

/* 주차수 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주차수 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_TYPE'
GO

/* 주파수 패턴 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 패턴 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_TYPE'
GO

/* 주파수 패턴 주기 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 패턴 주기', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_PATTERN_PERIOD'
GO

/* 주파수 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MEAN'
GO

/* 주파수 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MIN'
GO

/* 주파수 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_MAX'
GO

/* 주파수 값 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'주파수 값 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'FREQ_POSITION_COUNT'
GO

/* PRI 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_TYPE'
GO

/* PRI 패턴 형태 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 형태', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_TYPE'
GO

/* PRI 패턴 주기 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 패턴 주기', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_PATTERN_PERIOD'
GO

/* PRI 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MEAN'
GO

/* PRI 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MIN'
GO

/* PRI 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_MAX'
GO

/* PRI 지터율 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 지터율', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_JITTER_RATIO'
GO

/* PRI 값 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PRI 값 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PRI_POSITION_COUNT'
GO

/* 펄스폭 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MEAN'
GO

/* 펄스폭 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MIN'
GO

/* 펄스폭 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'펄스폭 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PW_MAX'
GO

/* 신호세기 평균 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 평균', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MEAN'
GO

/* 신호세기 최소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 최소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MIN'
GO

/* 신호세기 최대 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'신호세기 최대', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'PA_MAX'
GO

/* 저장 여부 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'저장 여부', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'IS_STORED_PDW'
GO

/* PDW 개수 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'PDW 개수', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'NUM_PDW'
GO

/* 수집소 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집소', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'COLLECTOR_ID'
GO

/* 위도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'위도', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'LATITUDE'
GO

/* 경도 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'경도', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'LONGITUDE'
GO

/* 레이더모드명 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드명', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_NAME'
GO

/* 레이더모드 인덱스 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'레이더모드 인덱스', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'COLUMN', @level2name=N'RADARMODE_INDEX'
GO

/* LOB 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'PK_LOBDATA'
GO

/* LOB 데이터 기본키 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 데이터 기본키', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'INDEX', @level2name=N'PK_LOBDATA'
GO

/* 빔 데이터 -> 빔 포지션 */
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

/* 수집 데이터 -> 빔 데이터 */
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

/* LOB 데이터 -> LOB 포지션 */
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

/* 빔 데이터 -> 방사체 데이터 */
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

/* 빔 데이터 -> LOB 데이터 */
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

/* 빔 데이터 -> 빔 포지션 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 데이터 -> 빔 포지션', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABT_POSITION', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_ABT_POSITION'
GO

/* 수집 데이터 -> 빔 데이터 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'수집 데이터 -> 빔 데이터', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'ABTDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_RAWDATA_TO_ABTDATA'
GO

/* LOB 데이터 -> LOB 포지션 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'LOB 데이터 -> LOB 포지션', 
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

/* 빔 데이터 -> 방사체 데이터 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 데이터 -> 방사체 데이터', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'AETDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_AETDATA'
GO

/* 빔 데이터 -> LOB 데이터 */
EXEC sp_addextendedproperty 
	@name=N'MS_Description', @value=N'빔 데이터 -> LOB 데이터', 
	@level0type=N'SCHEMA', @level0name=N'dbo2', 
	@level1type=N'TABLE', @level1name=N'LOBDATA', 
	@level2type=N'CONSTRAINT', @level2name=N'FK_ABTDATA_TO_LOBDATA'
GO