# 2020-08-26 오후 3:22:26

# CED 관련 테이블을 삭제합니다.
drop table if exists "RADAR";
drop table if exists "RADAR_P";
drop table if exists "RADAR_CONTENTS";
drop table if exists "RADAR_CONTENTS_P";
drop table if exists "RADAR_COMMENTS";
drop table if exists "RADAR_COMMENTS_P";
drop table if exists "WEAPON_SYSTEM";
drop table if exists "WEAPON_SYSTEM_P";
drop table if exists "ASSOC_WEAP_SYS";
drop table if exists "ASSOC_WEAP_SYS_P";
drop table if exists "PLATFORM";
drop table if exists "PLATFORM_P";
drop table if exists "ASSOC_PLATFORM";
drop table if exists "ASSOC_PLATFORM_P";
drop table if exists "ASSOC_ELNOT";
drop table if exists "ASSOC_ELNOT_P";
drop table if exists "PARAM_SET_ASSOCIATIONS";
drop table if exists "PARAM_SET_ASSOCIATIONS_P";
drop table if exists "RADAR_MODE";
drop table if exists "RADAR_MODE_P";
drop table if exists "RADAR_MODE_COMMENTS";
drop table if exists "RADAR_MODE_COMMENTS_P";
drop table if exists "RADAR_MODE_LIFECYCLE";
drop table if exists "RADAR_MODE_LIFECYCLE_P";
drop table if exists "RADAR_PD_VALUES";
drop table if exists "RADAR_PD_VALUES_P";
drop table if exists "RADAR_PD_SEQUENCE_NAME";
drop table if exists "RADAR_PD_SEQUENCE_NAME_P";
drop table if exists "RADAR_PD_SEQUENCE";
drop table if exists "RADAR_PD_SEQUENCE_P";
drop table if exists "RADAR_PD_SPOT_VALUES";
drop table if exists "RADAR_PD_SPOT_VALUES_P";
drop table if exists "RADAR_RF_VALUES";
drop table if exists "RADAR_RF_VALUES_P";
drop table if exists "RADAR_RF_SEQUENCE_NAME";
drop table if exists "RADAR_RF_SEQUENCE_NAME_P";
drop table if exists "RADAR_RF_SEQUENCE";
drop table if exists "RADAR_RF_SEQUENCE_P";
drop table if exists "RADAR_RF_SPOT_VALUES";
drop table if exists "RADAR_RF_SPOT_VALUES_P";
drop table if exists "RADAR_PRI_VALUES";
drop table if exists "RADAR_PRI_VALUES_P";
drop table if exists "RADAR_PRI_SEQUENCE_NAME";
drop table if exists "RADAR_PRI_SEQUENCE_NAME_P";
drop table if exists "RADAR_PRI_SEQUENCE";
drop table if exists "RADAR_PRI_SEQUENCE_P";
drop table if exists "RADAR_PRI_SPOT_VALUES";
drop table if exists "RADAR_PRI_SPOT_VALUES_P";
drop table if exists "RADAR_PRI_GROUP_SPACING";
drop table if exists "RADAR_PRI_GROUP_SPACING_P";
drop table if exists "RADAR_MOP_CW";
drop table if exists "RADAR_MOP_CW_P";
drop table if exists "RADAR_MOP_CW_VALUES";
drop table if exists "RADAR_MOP_CW_VALUES_P";
drop table if exists "RADAR_MOP_CW_SEQ_NAME";
drop table if exists "RADAR_MOP_CW_SEQ_NAME_P";
drop table if exists "RADAR_MOP_CW_SEQUENCE";
drop table if exists "RADAR_MOP_CW_SEQUENCE_P";
drop table if exists "RADAR_MODE_PA_DIFF_IN_GROUP";
drop table if exists "RADAR_MODE_PA_DIFF_IN_GROUP_P";


# CED 관련 테이블을 생성합니다.
CREATE TABLE "RADAR" (
  RADAR_INDEX                 INTEGER           DEFAULT -1       				NOT NULL,
  SECLAB                      INTEGER           DEFAULT -1							NOT NULL,
  ELNOT                       VARCHAR2(5) 	UNIQUE  								NOT NULL,
  NICKNAME                    VARCHAR2(30 ),
  FUNCTION_CODE               VARCHAR2(2 ),
  PRIORITY                    INTEGER           DEFAULT 0               NOT NULL,
  STATUS                      VARCHAR2(20 ) DEFAULT 'ACTIVE' 				NOT NULL,
  DATE_LAST_UPDATED           TIMESTAMP(6),
  DATE_LAST_REVIEWED          TIMESTAMP(6),
  LAST_REVIEWED_BY            INTEGER						DEFAULT -1,
  LAST_UPDATED_BY             INTEGER						DEFAULT -1,
  DATE_ACTIVATED              TIMESTAMP(6),
  DATE_INACTIVATED            TIMESTAMP(6),
  SRT_REVIEWED                INTEGER           DEFAULT 0               NOT NULL,
  TIME_INACTIVATED            INTEGER				  	DEFAULT -1,
  AOR_INDEX                   INTEGER						DEFAULT -1,
  DATE_CADCN                  TIMESTAMP(6),
  ACCEPTED                    INTEGER           DEFAULT 1               NOT NULL,
  PRIMARY_WEAP_SYS            INTEGER						DEFAULT -1,
  PRIMARY_PLATFORM            INTEGER						DEFAULT -1,
  SECURITY_REVIEW_DATE        TIMESTAMP(6),
  COMBINED_DATE_LAST_UPDATED  TIMESTAMP(6),

  PRIMARY KEY (RADAR_INDEX)
);
CREATE TABLE "RADAR_P" (
  RADAR_INDEX                 INTEGER                  NOT NULL,
  SECLAB                      INTEGER                  NOT NULL,
  ELNOT                       VARCHAR2(5 ) UNIQUE  NOT NULL,
  NICKNAME                    VARCHAR2(30 ),
  FUNCTION_CODE               VARCHAR2(2 ),
  PRIORITY                    INTEGER           DEFAULT 0                     NOT NULL,
  STATUS                      VARCHAR2(20 ) DEFAULT 'ACTIVE' NOT NULL,
  DATE_LAST_UPDATED           TIMESTAMP(6),
  DATE_LAST_REVIEWED          TIMESTAMP(6),
  LAST_REVIEWED_BY            INTEGER,
  LAST_UPDATED_BY             INTEGER,
  DATE_ACTIVATED              TIMESTAMP(6),
  DATE_INACTIVATED            TIMESTAMP(6),
  SRT_REVIEWED                INTEGER           DEFAULT 0                     NOT NULL,
  TIME_INACTIVATED            INTEGER,
  AOR_INDEX                   INTEGER,
  DATE_CADCN                  TIMESTAMP(6),
  ACCEPTED                    INTEGER           DEFAULT 1                     NOT NULL,
  PRIMARY_WEAP_SYS            INTEGER,
  PRIMARY_PLATFORM            INTEGER,
  SECURITY_REVIEW_DATE        TIMESTAMP(6),
  COMBINED_DATE_LAST_UPDATED  TIMESTAMP(6),
  PRIMARY KEY (RADAR_INDEX)
);
CREATE TABLE RADAR_COMMENTS
(
  RADAR_COMMENT_INDEX     INTEGER               NOT NULL,
  RADAR_INDEX             INTEGER               NOT NULL,
  TITLE                   VARCHAR2(30 )     NOT NULL,
  DATE_CREATED            TIMESTAMP(6)          NOT NULL,
  DATE_LAST_UPDATED       TIMESTAMP(6)          NOT NULL,
  TYPE                    VARCHAR2(10 )     NOT NULL,
  COMMENTS                CLOB,
  THIRD_PARTY_RELEASABLE  INTEGER,
  SECURITY_REVIEW_DATE    TIMESTAMP(6),
  COMMENT_ORDER           INTEGER,
  SECLAB                  INTEGER               NOT NULL,
  PRIMARY KEY (RADAR_INDEX, RADAR_COMMENT_INDEX)
);
CREATE TABLE RADAR_COMMENTS_P
(
  RADAR_COMMENT_INDEX     INTEGER               NOT NULL,
  RADAR_INDEX             INTEGER               NOT NULL,
  TITLE                   VARCHAR2(30 )     NOT NULL,
  DATE_CREATED            TIMESTAMP(6)          NOT NULL,
  DATE_LAST_UPDATED       TIMESTAMP(6)          NOT NULL,
  TYPE                    VARCHAR2(10 )     NOT NULL,
  COMMENTS                CLOB,
  THIRD_PARTY_RELEASABLE  INTEGER,
  SECURITY_REVIEW_DATE    TIMESTAMP(6),
  COMMENT_ORDER           INTEGER,
  SECLAB                  INTEGER               NOT NULL,
  PRIMARY KEY (RADAR_INDEX, RADAR_COMMENT_INDEX)
);
CREATE TABLE WEAPON_SYSTEM
(
  WEAPON_SYS            VARCHAR2(40 )       NOT NULL,
  WEAPON_INDEX          INTEGER                 NOT NULL,
  SECLAB                INTEGER                 NOT NULL,
  SUPPORT_CNT           INTEGER                 DEFAULT 0                     NOT NULL,
  SECURITY_REVIEW_DATE  TIMESTAMP(6),
  DATE_LAST_UPDATED     TIMESTAMP(6),
  PRIMARY KEY (WEAPON_INDEX)
);
CREATE TABLE WEAPON_SYSTEM_P
(
  WEAPON_SYS            VARCHAR2(40 )       NOT NULL,
  WEAPON_INDEX          INTEGER                 NOT NULL,
  SECLAB                INTEGER                 NOT NULL,
  SUPPORT_CNT           INTEGER                 DEFAULT 0                     NOT NULL,
  SECURITY_REVIEW_DATE  TIMESTAMP(6),
  DATE_LAST_UPDATED     TIMESTAMP(6),
  PRIMARY KEY (WEAPON_INDEX)
);
CREATE TABLE ASSOC_WEAP_SYS
(
  RADAR_INDEX   INTEGER                         NOT NULL,
  WEAPON_INDEX  INTEGER                         NOT NULL,
  SECLAB        INTEGER                         NOT NULL,
  PRIMARY KEY (RADAR_INDEX, WEAPON_INDEX)
);
CREATE TABLE ASSOC_WEAP_SYS_P
(
  RADAR_INDEX   INTEGER                         NOT NULL,
  WEAPON_INDEX  INTEGER                         NOT NULL,
  SECLAB        INTEGER                         NOT NULL,
  PRIMARY KEY (RADAR_INDEX, WEAPON_INDEX)
);
CREATE TABLE PLATFORM
(
  PLATFORM_INDEX        INTEGER                 NOT NULL,
  PLATFORM              VARCHAR2(40 )       NOT NULL,
  SECURITY_REVIEW_DATE  TIMESTAMP(6),
  DATE_LAST_UPDATED     TIMESTAMP(6),
  SECLAB                INTEGER                 NOT NULL,
  PRIMARY KEY (PLATFORM_INDEX)
);
CREATE TABLE PLATFORM_P
(
  PLATFORM_INDEX        INTEGER                 NOT NULL,
  PLATFORM              VARCHAR2(40 )       NOT NULL,
  SECURITY_REVIEW_DATE  TIMESTAMP(6),
  DATE_LAST_UPDATED     TIMESTAMP(6),
  SECLAB                INTEGER                 NOT NULL,
  PRIMARY KEY (PLATFORM_INDEX)
);
CREATE TABLE ASSOC_PLATFORM
(
  RADAR_INDEX     INTEGER                       NOT NULL,
  PLATFORM_INDEX  INTEGER                       NOT NULL,
  SECLAB          INTEGER                       NOT NULL,
  PRIMARY KEY (RADAR_INDEX, PLATFORM_INDEX)
);
CREATE TABLE ASSOC_PLATFORM_P
(
  RADAR_INDEX     INTEGER                       NOT NULL,
  PLATFORM_INDEX  INTEGER                       NOT NULL,
  SECLAB          INTEGER                       NOT NULL,
  PRIMARY KEY (RADAR_INDEX, PLATFORM_INDEX)
);
CREATE TABLE ASSOC_ELNOT
(
  RADAR_INDEX        INTEGER                    NOT NULL,
  ASSOC_RADAR_INDEX  INTEGER                    NOT NULL,
  SECLAB             INTEGER                    NOT NULL,
  PRIMARY KEY (RADAR_INDEX, ASSOC_RADAR_INDEX)
);
CREATE TABLE ASSOC_ELNOT_P
(
  RADAR_INDEX        INTEGER                    NOT NULL,
  ASSOC_RADAR_INDEX  INTEGER                    NOT NULL,
  SECLAB             INTEGER                    NOT NULL,
  PRIMARY KEY (RADAR_INDEX, ASSOC_RADAR_INDEX)
);
CREATE TABLE PARAM_SET_ASSOCIATIONS
(
  ASSOC_INDEX  INTEGER                          NOT NULL,
  RADAR_INDEX  INTEGER                          NOT NULL,
  SET_CODE     VARCHAR2(2 )                 NOT NULL,
  ASSOC_TYPE   INTEGER                          NOT NULL,
  SECLAB       INTEGER                          DEFAULT NULL                  NOT NULL,
  PRIMARY KEY (ASSOC_INDEX)
);
CREATE TABLE PARAM_SET_ASSOCIATIONS_P
(
  ASSOC_INDEX  INTEGER                          NOT NULL,
  RADAR_INDEX  INTEGER                          NOT NULL,
  SET_CODE     VARCHAR2(2 )                 NOT NULL,
  ASSOC_TYPE   INTEGER                          NOT NULL,
  SECLAB       INTEGER                          DEFAULT NULL                  NOT NULL,
  PRIMARY KEY (ASSOC_INDEX)
);
CREATE TABLE RADAR_MODE
(
  RADAR_MODE_INDEX                INTEGER       NOT NULL,
  SECLAB                          INTEGER       DEFAULT 0,
  FUNCTION_CODE                   VARCHAR2(2 ),
  DATE_CREATED                    TIMESTAMP(6)                   DEFAULT '2020/08/28 12:34:56.123',
  DATE_LAST_UPDATED               TIMESTAMP(6)                   DEFAULT '1970/01/01 0:00:00.000',
  DATE_LAST_REVIEWED              TIMESTAMP(6)                   DEFAULT '1970/01/01 0:00:00.000',
  DATE_FIRST_SEEN                 TIMESTAMP(6)                   DEFAULT '1970/01/01 0:00:00.000',
  DATE_LAST_SEEN                  TIMESTAMP(6)                   DEFAULT '1970/01/01 0:00:00.000',
  LAST_UPDATED_BY                 INTEGER                        DEFAULT -1,
  SIGNAL_TYPE                     VARCHAR2(10 ) DEFAULT 'Pulsed',
  ERP_CONTINUITY                  INTEGER                        DEFAULT -1,
  ERP_DWELL_TIME_MIN              FLOAT(52)                      DEFAULT -1,
  ERP_DWELL_TIME_MAX              FLOAT(52)                      DEFAULT -1,
  ERP_EXTREME_MIN                 FLOAT(52)                      DEFAULT -1,
  ERP_EXTREME_MAX                 FLOAT(52)                      DEFAULT -1,
  ERP_MEAN_MIN                    FLOAT(52)                      DEFAULT -1,
  ERP_MEAN_MAX                    FLOAT(52)                      DEFAULT -1,
  ERP_NUM_ELEMENTS                INTEGER                        DEFAULT -1,
  ERP_NUM_POSITIONS               INTEGER                        DEFAULT -1,
  ERP_PATTERN                     INTEGER                        DEFAULT -1,
  ERP_PATTERN_DRIVER              VARCHAR2(400 )             DEFAULT 'X',
  ERP_PATTERN_RULE                VARCHAR2(400 )             DEFAULT 'X',
  ERP_PATTERN_PERIOD_MIN          FLOAT(52)                      DEFAULT -1,
  ERP_PATTERN_PERIOD_MAX          FLOAT(52)                      DEFAULT -1,
  ERP_RANGE_MIN                   FLOAT(52)                      DEFAULT -1,
  ERP_RANGE_MAX                   FLOAT(52)                      DEFAULT -1,
  ERP_RATE_MIN                    FLOAT(52)                      DEFAULT -1,
  ERP_RATE_MAX                    FLOAT(52)                      DEFAULT -1,
  ERP_STANDARD_DEVIATION          FLOAT(52)                      DEFAULT -1,
  ERP_STEP_MIN                    FLOAT(52)                      DEFAULT -1,
  ERP_STEP_MAX                    FLOAT(52)                      DEFAULT -1,
  ERP_TYPICAL_MIN                 FLOAT(52)                      DEFAULT -1,
  ERP_TYPICAL_MAX                 FLOAT(52)                      DEFAULT -1,
  POLARIZATION                    INTEGER                        DEFAULT -1,
  POL_AXIAL_RATIO_MIN             FLOAT(52)                      DEFAULT -1,
  POL_AXIAL_RATIO_MAX             FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_PATTERN_DRIVER   VARCHAR2(400 )             DEFAULT 'X',
  POL_TILT_ANGLE_PATTERN_RULE     VARCHAR2(400 )             DEFAULT 'X',
  POL_TILT_ANGLE_RATE_MIN         FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_RATE_MAX         FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_CONTINUITY       INTEGER                        DEFAULT -1,
  POL_TILT_ANGLE_DWELL_TIME_MIN   FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_DWELL_TIME_MAX   FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_EXTREME_MIN      FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_EXTREME_MAX      FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_MEAN_MIN         FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_MEAN_MAX         FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_NUM_ELEMENTS     INTEGER                        DEFAULT -1,
  POL_TILT_ANGLE_NUM_POSITIONS    INTEGER                        DEFAULT -1,
  POL_TILT_ANGLE_PATTERN          INTEGER                        DEFAULT -1,
  POL_TILT_ANGLE_PAT_PERIOD_MIN   FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_PAT_PERIOD_MAX   FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_RANGE_MIN        FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_RANGE_MAX        FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_STEP_MIN         FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_STEP_MAX         FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_TYPICAL_MIN      FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_TYPICAL_MAX      FLOAT(52)                      DEFAULT -1,
  POL_TILT_ANGLE_STAND_DEVIATION  FLOAT(52)                      DEFAULT -1,
  POL_ROTATION_DIRECTION          INTEGER                        DEFAULT -1,
  POL_ROTATION_FREQUENCY_MIN      FLOAT(52)                      DEFAULT -1,
  POL_ROTATION_FREQUENCY_MAX      FLOAT(52)                      DEFAULT -1,
  POL_SENSE                       INTEGER                        DEFAULT -1,
  PLATFORM                        INTEGER                        DEFAULT -1,
  RF_EXTREME_MIN                  FLOAT(52)                      DEFAULT -1,
  RF_EXTREME_MAX                  FLOAT(52)                      DEFAULT -1,
  RF_TYPICAL_MIN                  FLOAT(52)                      DEFAULT 480,
  RF_TYPICAL_MAX                  FLOAT(52)                      DEFAULT 18000,
  BANDWIDTH_OPER_MIN              FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_OPER_MAX              FLOAT(52)                      DEFAULT -1,
  RF_CHANNEL_SPACING_MIN          FLOAT(52)                      DEFAULT -1,
  RF_CHANNEL_SPACING_MAX          FLOAT(52)                      DEFAULT -1,
  RF_CHIP_RATE                    FLOAT(52)                      DEFAULT -1,
  RF_CONTINUITY                   INTEGER                        DEFAULT -1,
  RF_DWELL_TIME_MIN               FLOAT(52)                      DEFAULT -1,
  RF_DWELL_TIME_MAX               FLOAT(52)                      DEFAULT -1,
  RF_GUARD_BAND                   FLOAT(52)                      DEFAULT -1,
  RF_NUM_SIMULTANEOUS             INTEGER                        DEFAULT -1,
  RF_REST_MIN                     FLOAT(52)                      DEFAULT -1,
  RF_REST_MAX                     FLOAT(52)                      DEFAULT -1,
  RF_SLOT_DURATION                FLOAT(52)                      DEFAULT -1,
  RF_PATTERN                      INTEGER                        DEFAULT -1,
  RF_NUM_CHANNELS                 INTEGER                        DEFAULT -1,
  RF_NUM_ELEMENTS                 INTEGER                        DEFAULT -1,
  RF_NUM_POSITIONS                INTEGER                        DEFAULT -1,
  RF_PATTERN_PERIOD_MIN           FLOAT(52)                      DEFAULT -1,
  RF_PATTERN_PERIOD_MAX           FLOAT(52)                      DEFAULT -1,
  RF_STANDARD_DEVIATION           FLOAT(52)                      DEFAULT -1,
  RF_RANGE_MIN                    FLOAT(52)                      DEFAULT -1,
  RF_RANGE_MAX                    FLOAT(52)                      DEFAULT -1,
  RF_RATE_MIN                     FLOAT(52)                      DEFAULT -1,
  RF_RATE_MAX                     FLOAT(52)                      DEFAULT -1,
  RF_STEP_MIN                     FLOAT(52)                      DEFAULT -1,
  RF_STEP_MAX                     FLOAT(52)                      DEFAULT -1,
  RF_PATTERN_DRIVER               VARCHAR2(400 )             DEFAULT 'X',
  RF_PATTERN_RULE                 VARCHAR2(400 )             DEFAULT 'X',
  RF_STABILITY                    FLOAT(52)                      DEFAULT -1,
  RF_STAB_PERIOD                  FLOAT(52)                      DEFAULT -1,
  RF_COHERENCY                    INTEGER                        DEFAULT -1,
  RF_MEAN_MIN                     FLOAT(52)                      DEFAULT -1,
  RF_MEAN_MAX                     FLOAT(52)                      DEFAULT -1,
  RF_XTAL_MIN                     FLOAT(52)                      DEFAULT -1,
  RF_XTAL_MAX                     FLOAT(52)                      DEFAULT -1,
  PRI_CONTINUITY                  INTEGER                        DEFAULT -1,
  PRI_DWELL_TIME_MIN              FLOAT(52)                      DEFAULT -1,
  PRI_DWELL_TIME_MAX              FLOAT(52)                      DEFAULT -1,
  PRI_EXTREME_MIN                 FLOAT(52)                      DEFAULT -1,
  PRI_EXTREME_MAX                 FLOAT(52)                      DEFAULT -1,
  PRI_FRAME_PERIOD_MIN            FLOAT(52)                      DEFAULT -1,
  PRI_FRAME_PERIOD_MAX            FLOAT(52)                      DEFAULT -1,
  PRI_GROUP_FORM                  INTEGER                        DEFAULT -1,
  PRI_GROUP_DWELL                 FLOAT(52)                      DEFAULT -1,
  PRI_GROUP_TRANS_MIN             FLOAT(52)                      DEFAULT -1,
  PRI_GROUP_TRANS_MAX             FLOAT(52)                      DEFAULT -1,
  PRI_MEAN_MIN                    FLOAT(52)                      DEFAULT -1,
  PRI_MEAN_MAX                    FLOAT(52)                      DEFAULT -1,
  PRI_NUM_ELEMENTS                INTEGER                        DEFAULT -1,
  PRI_NUM_POSITIONS               INTEGER                        DEFAULT -1,
  PRI_PATTERN                     INTEGER                        DEFAULT -1,
  PRI_PATTERN_DRIVER              VARCHAR2(400 )             DEFAULT 'X',
  PRI_PATTERN_RULE                VARCHAR2(400 )             DEFAULT 'X',
  PRI_PATTERN_PERIOD_MIN          FLOAT(52)                      DEFAULT -1,
  PRI_PATTERN_PERIOD_MAX          FLOAT(52)                      DEFAULT -1,
  PRI_PATTERN_PERIOD_COUNT_MIN    INTEGER                        DEFAULT -1,
  PRI_PATTERN_PERIOD_COUNT_MAX    INTEGER                        DEFAULT -1,
  PRI_PPG_MIN                     INTEGER                        DEFAULT -1,
  PRI_PPG_MAX                     INTEGER                        DEFAULT -1,
  PRI_RANGE_MIN                   FLOAT(52)                      DEFAULT -1,
  PRI_RANGE_MAX                   FLOAT(52)                      DEFAULT -1,
  PRI_RATE_MIN                    FLOAT(52)                      DEFAULT -1,
  PRI_RATE_MAX                    FLOAT(52)                      DEFAULT -1,
  PRI_SHIFT_VAL                   FLOAT(52)                      DEFAULT -1,
  PRI_STABILITY                   FLOAT(52)                      DEFAULT -1,
  PRI_STAB_PERIOD                 FLOAT(52)                      DEFAULT -1,
  PRI_STANDARD_DEVIATION          FLOAT(52)                      DEFAULT -1,
  PRI_STEP_MIN                    FLOAT(52)                      DEFAULT -1,
  PRI_STEP_MAX                    FLOAT(52)                      DEFAULT -1,
  PRI_SUBFRAME_PERIOD_MIN         FLOAT(52)                      DEFAULT -1,
  PRI_SUBFRAME_PERIOD_MAX         FLOAT(52)                      DEFAULT -1,
  PRI_TYPICAL_MIN                 FLOAT(52)                      DEFAULT 2,
  PRI_TYPICAL_MAX                 FLOAT(52)                      DEFAULT 2000,
  PRI_XTAL_MIN                    FLOAT(52)                      DEFAULT -1,
  PRI_XTAL_MAX                    FLOAT(52)                      DEFAULT -1,
  PRI_XTAL_COUNT_MIN              INTEGER                        DEFAULT -1,
  PRI_XTAL_COUNT_MAX              INTEGER                        DEFAULT -1,
  PD_CONTINUITY                   INTEGER                        DEFAULT -1,
  PD_DWELL_TIME_MIN               FLOAT(52)                      DEFAULT -1,
  PD_DWELL_TIME_MAX               FLOAT(52)                      DEFAULT -1,
  PD_EXTREME_MIN                  FLOAT(52)                      DEFAULT -1,
  PD_EXTREME_MAX                  FLOAT(52)                      DEFAULT -1,
  PD_TYPICAL_MIN                  FLOAT(52)                      DEFAULT -1,
  PD_TYPICAL_MAX                  FLOAT(52)                      DEFAULT -1,
  PD_NUM_ELEMENTS                 INTEGER                        DEFAULT -1,
  PD_NUM_POSITIONS                INTEGER                        DEFAULT -1,
  PD_PATTERN                      INTEGER                        DEFAULT -1,
  PD_PATTERN_PERIOD_MIN           FLOAT(52)                      DEFAULT -1,
  PD_PATTERN_PERIOD_MAX           FLOAT(52)                      DEFAULT -1,
  PD_PATTERN_DRIVER               VARCHAR2(400 )             DEFAULT 'X',
  PD_PATTERN_RULE                 VARCHAR2(400 )             DEFAULT 'X',
  PD_RANGE_MIN                    FLOAT(52)                      DEFAULT -1,
  PD_RANGE_MAX                    FLOAT(52)                      DEFAULT -1,
  PD_RATE_MIN                     FLOAT(52)                      DEFAULT -1,
  PD_RATE_MAX                     FLOAT(52)                      DEFAULT -1,
  PD_STANDARD_DEVIATION           FLOAT(52)                      DEFAULT -1,
  PD_STEP_MIN                     FLOAT(52)                      DEFAULT -1,
  PD_STEP_MAX                     FLOAT(52)                      DEFAULT -1,
  PD_MEAN_MIN                     FLOAT(52)                      DEFAULT -1,
  PD_MEAN_MAX                     FLOAT(52)                      DEFAULT -1,
  SCAN_EXTENT_ELEVATION_MIN       FLOAT(52)                      DEFAULT -1,
  SCAN_EXTENT_ELEVATION_MAX       FLOAT(52)                      DEFAULT -1,
  SCAN_EXTENT_AZIMUTH_MIN         FLOAT(52)                      DEFAULT -1,
  SCAN_EXTENT_AZIMUTH_MAX         FLOAT(52)                      DEFAULT -1,
  SCAN_SLEW_RATE_MIN              FLOAT(52)                      DEFAULT -1,
  SCAN_SLEW_RATE_MAX              FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_PATTERN_DRIVER     VARCHAR2(400 )             DEFAULT 'X',
  SCAN_PRIMARY_PATTERN_RULE       VARCHAR2(400 )             DEFAULT 'X',
  SCAN_PRIMARY_CONTINUITY         INTEGER                        DEFAULT -1,
  SCAN_PRIMARY_DWELL_TIME_MIN     FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_DWELL_TIME_MAX     FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_EXTREME_MIN        FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_EXTREME_MAX        FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_MEAN_MIN           FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_MEAN_MAX           FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_NUM_ELEMENTS       INTEGER                        DEFAULT -1,
  SCAN_PRIMARY_NUM_POSITIONS      INTEGER                        DEFAULT -1,
  SCAN_PRIMARY_PATTERN            INTEGER                        DEFAULT -1,
  SCAN_PRIMARY_PAT_PERIOD_MIN     FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_PAT_PERIOD_MAX     FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_RANGE_MIN          FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_RANGE_MAX          FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_RATE_MIN           FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_RATE_MAX           FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_STAND_DEVIATION    FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_STEP_MIN           FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_STEP_MAX           FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_TYPICAL_MIN        FLOAT(52)                      DEFAULT -1,
  SCAN_PRIMARY_TYPICAL_MAX        FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_PATTERN_DRIVER   VARCHAR2(400 )             DEFAULT 'X',
  SCAN_SECONDARY_PATTERN_RULE     VARCHAR2(400 )             DEFAULT 'X',
  SCAN_SECONDARY_CONTINUITY       INTEGER                        DEFAULT -1,
  SCAN_SECONDARY_DWELL_TIME_MIN   FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_DWELL_TIME_MAX   FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_EXTREME_MIN      FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_EXTREME_MAX      FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_MEAN_MIN         FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_MEAN_MAX         FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_NUM_ELEMENTS     INTEGER                        DEFAULT -1,
  SCAN_SECONDARY_NUM_POSITIONS    INTEGER                        DEFAULT -1,
  SCAN_SECONDARY_PATTERN          INTEGER                        DEFAULT -1,
  SCAN_SECONDARY_PAT_PERIOD_MIN   FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_PAT_PERIOD_MAX   FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_RANGE_MIN        FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_RANGE_MAX        FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_RATE_MIN         FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_RATE_MAX         FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_STAND_DEVIATION  FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_STEP_MIN         FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_STEP_MAX         FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_TYPE             INTEGER                        DEFAULT -1,
  SCAN_SECONDARY_TYPICAL_MIN      FLOAT(52)                      DEFAULT -1,
  SCAN_SECONDARY_TYPICAL_MAX      FLOAT(52)                      DEFAULT -1,
  SCAN_UNIQUE_BEAM_POSITIONS      INTEGER                        DEFAULT -1,
  SCAN_START_POINT_ELEVATION_MIN  FLOAT(52)                      DEFAULT -1,
  SCAN_START_POINT_ELEVATION_MAX  FLOAT(52)                      DEFAULT -1,
  SCAN_START_POINT_AZIMUTH_MIN    FLOAT(52)                      DEFAULT -1,
  SCAN_START_POINT_AZIMUTH_MAX    FLOAT(52)                      DEFAULT -1,
  SCAN_END_POINT_ELEVATION_MIN    FLOAT(52)                      DEFAULT -1,
  SCAN_END_POINT_ELEVATION_MAX    FLOAT(52)                      DEFAULT -1,
  SCAN_END_POINT_AZIMUTH_MIN      FLOAT(52)                      DEFAULT -1,
  SCAN_END_POINT_AZIMUTH_MAX      FLOAT(52)                      DEFAULT -1,
  SCAN_SECT_BEAMWIDTH_RATIO_MIN   FLOAT(52)                      DEFAULT -1,
  SCAN_SECT_BEAMWIDTH_RATIO_MAX   FLOAT(52)                      DEFAULT -1,
  SCAN_BEAM_POS_PER_RASTER_MIN    INTEGER                        DEFAULT -1,
  SCAN_BEAM_POS_PER_RASTER_MAX    INTEGER                        DEFAULT -1,
  SCAN_BARS_PER_RASTER_MIN        INTEGER                        DEFAULT -1,
  SCAN_BARS_PER_RASTER_MAX        INTEGER                        DEFAULT -1,
  SCAN_AZIMUTH_COVERAGE           FLOAT(52)                      DEFAULT -1,
  SCAN_AZIMUTH_CENTER             FLOAT(52)                      DEFAULT -1,
  SCAN_HORIZONTAL_BEAMWIDTH_MIN   FLOAT(52)                      DEFAULT -1,
  SCAN_HORIZONTAL_BEAMWIDTH_MAX   FLOAT(52)                      DEFAULT -1,
  SCAN_VERTICAL_BEAMWIDTH_MIN     FLOAT(52)                      DEFAULT -1,
  SCAN_VERTICAL_BEAMWIDTH_MAX     FLOAT(52)                      DEFAULT -1,
  SCAN_DWELLS                     INTEGER                        DEFAULT -1,
  SCAN_ELEVATION_STEP_TYPE        INTEGER                        DEFAULT -1,
  SCAN_ELEVATION_WIDTH            FLOAT(52)                      DEFAULT -1,
  SCAN_NUM_TURNS                  INTEGER                        DEFAULT -1,
  HORIZON_AVG_SIDELOBE_LEVEL_MIN  FLOAT(52)                      DEFAULT -1,
  HORIZON_AVG_SIDELOBE_LEVEL_MAX  FLOAT(52)                      DEFAULT -1,
  VERT_AVG_SIDELOBE_LEVEL_MIN     FLOAT(52)                      DEFAULT -1,
  VERT_AVG_SIDELOBE_LEVEL_MAX     FLOAT(52)                      DEFAULT -1,
  COMMS_MULTIP_SCHEME             VARCHAR2(20 )              DEFAULT 'X',
  COMMS_MULTIP_TYPE               VARCHAR2(20 )              DEFAULT 'X',
  COMMS_MULTIP_LEVEL              VARCHAR2(20 )              DEFAULT 'X',
  COMMS_SUBCARRIER_MODULATION     VARCHAR2(20 )              DEFAULT 'X',
  COMMS_SUBCARRIER_RF             FLOAT(52)                      DEFAULT -1,
  COMMS_TONE                      FLOAT(52)                      DEFAULT -1,
  COMMS_TONE_DURATION             FLOAT(52)                      DEFAULT -1,
  COMMS_SUBCARRIER_REST_RF        FLOAT(52)                      DEFAULT -1,
  COMMS_KEYING_RATE               FLOAT(52)                      DEFAULT -1,
  VALIDATION                      INTEGER       DEFAULT 1                     NOT NULL,
  MANUAL_REVISION                 INTEGER       DEFAULT 0                     NOT NULL,
  ACCEPTED                        INTEGER       DEFAULT 1                     NOT NULL,
  SRT_REVIEWED                    INTEGER       DEFAULT 0                     NOT NULL,
  PARENT_INDEX                    INTEGER                        DEFAULT -1,
  DATE_CADCN                      TIMESTAMP(6)                   DEFAULT '1970/01/01 0:00:00.000',
  HOR_FIRST_SIDELOBE_LEVEL_MIN    FLOAT(52)                      DEFAULT -1,
  HOR_FIRST_SIDELOBE_LEVEL_MAX    FLOAT(52)                      DEFAULT -1,
  HOR_SECOND_SIDELOBE_LEVEL_MIN   FLOAT(52)                      DEFAULT -1,
  HOR_SECOND_SIDELOBE_LEVEL_MAX   FLOAT(52)                      DEFAULT -1,
  HOR_THIRD_SIDELOBE_LEVEL_MIN    FLOAT(52)                      DEFAULT -1,
  HOR_THIRD_SIDELOBE_LEVEL_MAX    FLOAT(52)                      DEFAULT -1,
  VERT_FIRST_SIDELOBE_LEVEL_MIN   FLOAT(52)                      DEFAULT -1,
  VERT_FIRST_SIDELOBE_LEVEL_MAX   FLOAT(52)                      DEFAULT -1,
  VERT_SECOND_SIDELOBE_LEVEL_MIN  FLOAT(52)                      DEFAULT -1,
  VERT_SECOND_SIDELOBE_LEVEL_MAX  FLOAT(52)                      DEFAULT -1,
  VERT_THIRD_SIDELOBE_LEVEL_MIN   FLOAT(52)                      DEFAULT -1,
  VERT_THIRD_SIDELOBE_LEVEL_MAX   FLOAT(52)                      DEFAULT -1,
  RF_LEGACY_TYPE                  INTEGER                        DEFAULT -1,
  PRI_LEGACY_TYPE                 INTEGER                        DEFAULT -1,
  PD_LEGACY_TYPE                  INTEGER                        DEFAULT -1,
  PD_RISE_MIN                     FLOAT(52)                      DEFAULT -1,
  PD_RISE_MAX                     FLOAT(52)                      DEFAULT -1,
  PD_FALL_MIN                     FLOAT(52)                      DEFAULT -1,
  PD_FALL_MAX                     FLOAT(52)                      DEFAULT -1,
  BLANKING_DURATION_MIN           FLOAT(52)                      DEFAULT -1,
  BLANKING_DURATION_MAX           FLOAT(52)                      DEFAULT -1,
  BLANKING_PERIOD_MIN             FLOAT(52)                      DEFAULT -1,
  BLANKING_PERIOD_MAX             FLOAT(52)                      DEFAULT -1,
  POWER_DIFFERENCE_MIN            FLOAT(52)                      DEFAULT -1,
  POWER_DIFFERENCE_MAX            FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_THREE_MIN        FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_THREE_MAX        FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_SIX_MIN          FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_SIX_MAX          FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_TEN_MIN          FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_TEN_MAX          FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_TWENTY_MIN       FLOAT(52)                      DEFAULT -1,
  BANDWIDTH_INST_TWENTY_MAX       FLOAT(52)                      DEFAULT -1,
  PARAM_ASSOC                     VARCHAR2(390 )             DEFAULT 'X',
  SCAN_PRIMARY_TYPE               INTEGER                        DEFAULT -1,
  HOR_FIRST_SIDELOBE_POS_MIN      FLOAT(52)                      DEFAULT -1,
  HOR_FIRST_SIDELOBE_POS_MAX      FLOAT(52)                      DEFAULT -1,
  HOR_SECOND_SIDELOBE_POS_MIN     FLOAT(52)                      DEFAULT -1,
  HOR_SECOND_SIDELOBE_POS_MAX     FLOAT(52)                      DEFAULT -1,
  HOR_THIRD_SIDELOBE_POS_MIN      FLOAT(52)                      DEFAULT -1,
  HOR_THIRD_SIDELOBE_POS_MAX      FLOAT(52)                      DEFAULT -1,
  VERT_FIRST_SIDELOBE_POS_MIN     FLOAT(52)                      DEFAULT -1,
  VERT_FIRST_SIDELOBE_POS_MAX     FLOAT(52)                      DEFAULT -1,
  VERT_SECOND_SIDELOBE_POS_MIN    FLOAT(52)                      DEFAULT -1,
  VERT_SECOND_SIDELOBE_POS_MAX    FLOAT(52)                      DEFAULT -1,
  VERT_THIRD_SIDELOBE_POS_MIN     FLOAT(52)                      DEFAULT -1,
  VERT_THIRD_SIDELOBE_POS_MAX     FLOAT(52)                      DEFAULT -1,
  SECURITY_REVIEW_DATE            TIMESTAMP(6)                   DEFAULT '1970/01/01 0:00:00.000',
  ASSOC_INDEX                     INTEGER                        DEFAULT -1,
  MODULATION_CODE                 VARCHAR2(2 )               DEFAULT 'ZZ',
  PRIORITY                        INTEGER                        DEFAULT 0,
  RF_TYPE                         INTEGER DEFAULT 0,
  PRI_TYPE                        INTEGER DEFAULT 0,
  PRIMARY KEY (RADAR_MODE_INDEX)
);
CREATE TABLE RADAR_MODE_P
(
  RADAR_MODE_INDEX                INTEGER       NOT NULL,
  SECLAB                          INTEGER       NOT NULL,
  FUNCTION_CODE                   VARCHAR2(2 ),
  DATE_CREATED                    TIMESTAMP(6),
  DATE_LAST_UPDATED               TIMESTAMP(6),
  DATE_LAST_REVIEWED              TIMESTAMP(6),
  DATE_FIRST_SEEN                 TIMESTAMP(6),
  DATE_LAST_SEEN                  TIMESTAMP(6),
  LAST_UPDATED_BY                 INTEGER,
  SIGNAL_TYPE                     VARCHAR2(10 ) NOT NULL,
  ERP_CONTINUITY                  INTEGER,
  ERP_DWELL_TIME_MIN              FLOAT(52),
  ERP_DWELL_TIME_MAX              FLOAT(52),
  ERP_EXTREME_MIN                 FLOAT(52),
  ERP_EXTREME_MAX                 FLOAT(52),
  ERP_MEAN_MIN                    FLOAT(52),
  ERP_MEAN_MAX                    FLOAT(52),
  ERP_NUM_ELEMENTS                INTEGER,
  ERP_NUM_POSITIONS               INTEGER,
  ERP_PATTERN                     INTEGER,
  ERP_PATTERN_DRIVER              VARCHAR2(400 ),
  ERP_PATTERN_RULE                VARCHAR2(400 ),
  ERP_PATTERN_PERIOD_MIN          FLOAT(52),
  ERP_PATTERN_PERIOD_MAX          FLOAT(52),
  ERP_RANGE_MIN                   FLOAT(52),
  ERP_RANGE_MAX                   FLOAT(52),
  ERP_RATE_MIN                    FLOAT(52),
  ERP_RATE_MAX                    FLOAT(52),
  ERP_STANDARD_DEVIATION          FLOAT(52),
  ERP_STEP_MIN                    FLOAT(52),
  ERP_STEP_MAX                    FLOAT(52),
  ERP_TYPICAL_MIN                 FLOAT(52),
  ERP_TYPICAL_MAX                 FLOAT(52),
  POLARIZATION                    INTEGER,
  POL_AXIAL_RATIO_MIN             FLOAT(52),
  POL_AXIAL_RATIO_MAX             FLOAT(52),
  POL_TILT_ANGLE_PATTERN_DRIVER   VARCHAR2(400 ),
  POL_TILT_ANGLE_PATTERN_RULE     VARCHAR2(400 ),
  POL_TILT_ANGLE_RATE_MIN         FLOAT(52),
  POL_TILT_ANGLE_RATE_MAX         FLOAT(52),
  POL_TILT_ANGLE_CONTINUITY       INTEGER,
  POL_TILT_ANGLE_DWELL_TIME_MIN   FLOAT(52),
  POL_TILT_ANGLE_DWELL_TIME_MAX   FLOAT(52),
  POL_TILT_ANGLE_EXTREME_MIN      FLOAT(52),
  POL_TILT_ANGLE_EXTREME_MAX      FLOAT(52),
  POL_TILT_ANGLE_MEAN_MIN         FLOAT(52),
  POL_TILT_ANGLE_MEAN_MAX         FLOAT(52),
  POL_TILT_ANGLE_NUM_ELEMENTS     INTEGER,
  POL_TILT_ANGLE_NUM_POSITIONS    INTEGER,
  POL_TILT_ANGLE_PATTERN          INTEGER,
  POL_TILT_ANGLE_PAT_PERIOD_MIN   FLOAT(52),
  POL_TILT_ANGLE_PAT_PERIOD_MAX   FLOAT(52),
  POL_TILT_ANGLE_RANGE_MIN        FLOAT(52),
  POL_TILT_ANGLE_RANGE_MAX        FLOAT(52),
  POL_TILT_ANGLE_STEP_MIN         FLOAT(52),
  POL_TILT_ANGLE_STEP_MAX         FLOAT(52),
  POL_TILT_ANGLE_TYPICAL_MIN      FLOAT(52),
  POL_TILT_ANGLE_TYPICAL_MAX      FLOAT(52),
  POL_TILT_ANGLE_STAND_DEVIATION  FLOAT(52),
  POL_ROTATION_DIRECTION          INTEGER,
  POL_ROTATION_FREQUENCY_MIN      FLOAT(52),
  POL_ROTATION_FREQUENCY_MAX      FLOAT(52),
  POL_SENSE                       INTEGER,
  PLATFORM                        INTEGER,
  RF_EXTREME_MIN                  FLOAT(52),
  RF_EXTREME_MAX                  FLOAT(52),
  RF_TYPICAL_MIN                  FLOAT(52),
  RF_TYPICAL_MAX                  FLOAT(52),
  BANDWIDTH_OPER_MIN              FLOAT(52),
  BANDWIDTH_OPER_MAX              FLOAT(52),
  RF_CHANNEL_SPACING_MIN          FLOAT(52),
  RF_CHANNEL_SPACING_MAX          FLOAT(52),
  RF_CHIP_RATE                    FLOAT(52),
  RF_CONTINUITY                   INTEGER,
  RF_DWELL_TIME_MIN               FLOAT(52),
  RF_DWELL_TIME_MAX               FLOAT(52),
  RF_GUARD_BAND                   FLOAT(52),
  RF_NUM_SIMULTANEOUS             INTEGER,
  RF_REST_MIN                     FLOAT(52),
  RF_REST_MAX                     FLOAT(52),
  RF_SLOT_DURATION                FLOAT(52),
  RF_PATTERN                      INTEGER                           DEFAULT -1,
  RF_NUM_CHANNELS                 INTEGER,
  RF_NUM_ELEMENTS                 INTEGER,
  RF_NUM_POSITIONS                INTEGER,
  RF_PATTERN_PERIOD_MIN           FLOAT(52),
  RF_PATTERN_PERIOD_MAX           FLOAT(52),
  RF_STANDARD_DEVIATION           FLOAT(52),
  RF_RANGE_MIN                    FLOAT(52),
  RF_RANGE_MAX                    FLOAT(52),
  RF_RATE_MIN                     FLOAT(52),
  RF_RATE_MAX                     FLOAT(52),
  RF_STEP_MIN                     FLOAT(52),
  RF_STEP_MAX                     FLOAT(52),
  RF_PATTERN_DRIVER               VARCHAR2(400 ),
  RF_PATTERN_RULE                 VARCHAR2(400 ),
  RF_STABILITY                    FLOAT(52),
  RF_STAB_PERIOD                  FLOAT(52),
  RF_COHERENCY                    INTEGER,
  RF_MEAN_MIN                     FLOAT(52),
  RF_MEAN_MAX                     FLOAT(52),
  RF_XTAL_MIN                     FLOAT(52),
  RF_XTAL_MAX                     FLOAT(52),
  PRI_CONTINUITY                  INTEGER,
  PRI_DWELL_TIME_MIN              FLOAT(52),
  PRI_DWELL_TIME_MAX              FLOAT(52),
  PRI_EXTREME_MIN                 FLOAT(52),
  PRI_EXTREME_MAX                 FLOAT(52),
  PRI_FRAME_PERIOD_MIN            FLOAT(52),
  PRI_FRAME_PERIOD_MAX            FLOAT(52),
  PRI_GROUP_FORM                  INTEGER,
  PRI_GROUP_DWELL                 FLOAT(52),
  PRI_GROUP_TRANS_MIN             FLOAT(52),
  PRI_GROUP_TRANS_MAX             FLOAT(52),
  PRI_MEAN_MIN                    FLOAT(52),
  PRI_MEAN_MAX                    FLOAT(52),
  PRI_NUM_ELEMENTS                INTEGER,
  PRI_NUM_POSITIONS               INTEGER,
  PRI_PATTERN                     INTEGER                           DEFAULT -1,
  PRI_PATTERN_DRIVER              VARCHAR2(400 ),
  PRI_PATTERN_RULE                VARCHAR2(400 ),
  PRI_PATTERN_PERIOD_MIN          FLOAT(52),
  PRI_PATTERN_PERIOD_MAX          FLOAT(52),
  PRI_PATTERN_PERIOD_COUNT_MIN    INTEGER,
  PRI_PATTERN_PERIOD_COUNT_MAX    INTEGER,
  PRI_PPG_MIN                     INTEGER,
  PRI_PPG_MAX                     INTEGER,
  PRI_RANGE_MIN                   FLOAT(52),
  PRI_RANGE_MAX                   FLOAT(52),
  PRI_RATE_MIN                    FLOAT(52),
  PRI_RATE_MAX                    FLOAT(52),
  PRI_SHIFT_VAL                   FLOAT(52),
  PRI_STABILITY                   FLOAT(52),
  PRI_STAB_PERIOD                 FLOAT(52),
  PRI_STANDARD_DEVIATION          FLOAT(52),
  PRI_STEP_MIN                    FLOAT(52),
  PRI_STEP_MAX                    FLOAT(52),
  PRI_SUBFRAME_PERIOD_MIN         FLOAT(52),
  PRI_SUBFRAME_PERIOD_MAX         FLOAT(52),
  PRI_TYPICAL_MIN                 FLOAT(52),
  PRI_TYPICAL_MAX                 FLOAT(52),
  PRI_XTAL_MIN                    FLOAT(52),
  PRI_XTAL_MAX                    FLOAT(52),
  PRI_XTAL_COUNT_MIN              INTEGER,
  PRI_XTAL_COUNT_MAX              INTEGER,
  PD_CONTINUITY                   INTEGER,
  PD_DWELL_TIME_MIN               FLOAT(52),
  PD_DWELL_TIME_MAX               FLOAT(52),
  PD_EXTREME_MIN                  FLOAT(52),
  PD_EXTREME_MAX                  FLOAT(52),
  PD_TYPICAL_MIN                  FLOAT(52),
  PD_TYPICAL_MAX                  FLOAT(52),
  PD_NUM_ELEMENTS                 INTEGER,
  PD_NUM_POSITIONS                INTEGER,
  PD_PATTERN                      INTEGER,
  PD_PATTERN_PERIOD_MIN           FLOAT(52),
  PD_PATTERN_PERIOD_MAX           FLOAT(52),
  PD_PATTERN_DRIVER               VARCHAR2(400 ),
  PD_PATTERN_RULE                 VARCHAR2(400 ),
  PD_RANGE_MIN                    FLOAT(52),
  PD_RANGE_MAX                    FLOAT(52),
  PD_RATE_MIN                     FLOAT(52),
  PD_RATE_MAX                     FLOAT(52),
  PD_STANDARD_DEVIATION           FLOAT(52),
  PD_STEP_MIN                     FLOAT(52),
  PD_STEP_MAX                     FLOAT(52),
  PD_MEAN_MIN                     FLOAT(52),
  PD_MEAN_MAX                     FLOAT(52),
  SCAN_EXTENT_ELEVATION_MIN       FLOAT(52),
  SCAN_EXTENT_ELEVATION_MAX       FLOAT(52),
  SCAN_EXTENT_AZIMUTH_MIN         FLOAT(52),
  SCAN_EXTENT_AZIMUTH_MAX         FLOAT(52),
  SCAN_SLEW_RATE_MIN              FLOAT(52),
  SCAN_SLEW_RATE_MAX              FLOAT(52),
  SCAN_PRIMARY_PATTERN_DRIVER     VARCHAR2(400 ),
  SCAN_PRIMARY_PATTERN_RULE       VARCHAR2(400 ),
  SCAN_PRIMARY_CONTINUITY         INTEGER,
  SCAN_PRIMARY_DWELL_TIME_MIN     FLOAT(52),
  SCAN_PRIMARY_DWELL_TIME_MAX     FLOAT(52),
  SCAN_PRIMARY_EXTREME_MIN        FLOAT(52),
  SCAN_PRIMARY_EXTREME_MAX        FLOAT(52),
  SCAN_PRIMARY_MEAN_MIN           FLOAT(52),
  SCAN_PRIMARY_MEAN_MAX           FLOAT(52),
  SCAN_PRIMARY_NUM_ELEMENTS       INTEGER,
  SCAN_PRIMARY_NUM_POSITIONS      INTEGER,
  SCAN_PRIMARY_PATTERN            INTEGER,
  SCAN_PRIMARY_PAT_PERIOD_MIN     FLOAT(52),
  SCAN_PRIMARY_PAT_PERIOD_MAX     FLOAT(52),
  SCAN_PRIMARY_RANGE_MIN          FLOAT(52),
  SCAN_PRIMARY_RANGE_MAX          FLOAT(52),
  SCAN_PRIMARY_RATE_MIN           FLOAT(52),
  SCAN_PRIMARY_RATE_MAX           FLOAT(52),
  SCAN_PRIMARY_STAND_DEVIATION    FLOAT(52),
  SCAN_PRIMARY_STEP_MIN           FLOAT(52),
  SCAN_PRIMARY_STEP_MAX           FLOAT(52),
  SCAN_PRIMARY_TYPICAL_MIN        FLOAT(52),
  SCAN_PRIMARY_TYPICAL_MAX        FLOAT(52),
  SCAN_SECONDARY_PATTERN_DRIVER   VARCHAR2(400 ),
  SCAN_SECONDARY_PATTERN_RULE     VARCHAR2(400 ),
  SCAN_SECONDARY_CONTINUITY       INTEGER,
  SCAN_SECONDARY_DWELL_TIME_MIN   FLOAT(52),
  SCAN_SECONDARY_DWELL_TIME_MAX   FLOAT(52),
  SCAN_SECONDARY_EXTREME_MIN      FLOAT(52),
  SCAN_SECONDARY_EXTREME_MAX      FLOAT(52),
  SCAN_SECONDARY_MEAN_MIN         FLOAT(52),
  SCAN_SECONDARY_MEAN_MAX         FLOAT(52),
  SCAN_SECONDARY_NUM_ELEMENTS     INTEGER,
  SCAN_SECONDARY_NUM_POSITIONS    INTEGER,
  SCAN_SECONDARY_PATTERN          INTEGER,
  SCAN_SECONDARY_PAT_PERIOD_MIN   FLOAT(52),
  SCAN_SECONDARY_PAT_PERIOD_MAX   FLOAT(52),
  SCAN_SECONDARY_RANGE_MIN        FLOAT(52),
  SCAN_SECONDARY_RANGE_MAX        FLOAT(52),
  SCAN_SECONDARY_RATE_MIN         FLOAT(52),
  SCAN_SECONDARY_RATE_MAX         FLOAT(52),
  SCAN_SECONDARY_STAND_DEVIATION  FLOAT(52),
  SCAN_SECONDARY_STEP_MIN         FLOAT(52),
  SCAN_SECONDARY_STEP_MAX         FLOAT(52),
  SCAN_SECONDARY_TYPE             INTEGER,
  SCAN_SECONDARY_TYPICAL_MIN      FLOAT(52),
  SCAN_SECONDARY_TYPICAL_MAX      FLOAT(52),
  SCAN_UNIQUE_BEAM_POSITIONS      INTEGER,
  SCAN_START_POINT_ELEVATION_MIN  FLOAT(52),
  SCAN_START_POINT_ELEVATION_MAX  FLOAT(52),
  SCAN_START_POINT_AZIMUTH_MIN    FLOAT(52),
  SCAN_START_POINT_AZIMUTH_MAX    FLOAT(52),
  SCAN_END_POINT_ELEVATION_MIN    FLOAT(52),
  SCAN_END_POINT_ELEVATION_MAX    FLOAT(52),
  SCAN_END_POINT_AZIMUTH_MIN      FLOAT(52),
  SCAN_END_POINT_AZIMUTH_MAX      FLOAT(52),
  SCAN_SECT_BEAMWIDTH_RATIO_MIN   FLOAT(52),
  SCAN_SECT_BEAMWIDTH_RATIO_MAX   FLOAT(52),
  SCAN_BEAM_POS_PER_RASTER_MIN    INTEGER,
  SCAN_BEAM_POS_PER_RASTER_MAX    INTEGER,
  SCAN_BARS_PER_RASTER_MIN        INTEGER,
  SCAN_BARS_PER_RASTER_MAX        INTEGER,
  SCAN_AZIMUTH_COVERAGE           FLOAT(52),
  SCAN_AZIMUTH_CENTER             FLOAT(52),
  SCAN_HORIZONTAL_BEAMWIDTH_MIN   FLOAT(52),
  SCAN_HORIZONTAL_BEAMWIDTH_MAX   FLOAT(52),
  SCAN_VERTICAL_BEAMWIDTH_MIN     FLOAT(52),
  SCAN_VERTICAL_BEAMWIDTH_MAX     FLOAT(52),
  SCAN_DWELLS                     INTEGER,
  SCAN_ELEVATION_STEP_TYPE        INTEGER,
  SCAN_ELEVATION_WIDTH            FLOAT(52),
  SCAN_NUM_TURNS                  INTEGER,
  HORIZON_AVG_SIDELOBE_LEVEL_MIN  FLOAT(52),
  HORIZON_AVG_SIDELOBE_LEVEL_MAX  FLOAT(52),
  VERT_AVG_SIDELOBE_LEVEL_MIN     FLOAT(52),
  VERT_AVG_SIDELOBE_LEVEL_MAX     FLOAT(52),
  COMMS_MULTIP_SCHEME             VARCHAR2(20 ),
  COMMS_MULTIP_TYPE               VARCHAR2(20 ),
  COMMS_MULTIP_LEVEL              VARCHAR2(20 ),
  COMMS_SUBCARRIER_MODULATION     VARCHAR2(20 ),
  COMMS_SUBCARRIER_RF             FLOAT(52),
  COMMS_TONE                      FLOAT(52),
  COMMS_TONE_DURATION             FLOAT(52),
  COMMS_SUBCARRIER_REST_RF        FLOAT(52),
  COMMS_KEYING_RATE               FLOAT(52),
  VALIDATION                      INTEGER       DEFAULT 0                     NOT NULL,
  MANUAL_REVISION                 INTEGER       DEFAULT 0                     NOT NULL,
  ACCEPTED                        INTEGER       DEFAULT 1                     NOT NULL,
  SRT_REVIEWED                    INTEGER       DEFAULT 0                     NOT NULL,
  PARENT_INDEX                    INTEGER,
  DATE_CADCN                      TIMESTAMP(6),
  HOR_FIRST_SIDELOBE_LEVEL_MIN    FLOAT(52),
  HOR_FIRST_SIDELOBE_LEVEL_MAX    FLOAT(52),
  HOR_SECOND_SIDELOBE_LEVEL_MIN   FLOAT(52),
  HOR_SECOND_SIDELOBE_LEVEL_MAX   FLOAT(52),
  HOR_THIRD_SIDELOBE_LEVEL_MIN    FLOAT(52),
  HOR_THIRD_SIDELOBE_LEVEL_MAX    FLOAT(52),
  VERT_FIRST_SIDELOBE_LEVEL_MIN   FLOAT(52),
  VERT_FIRST_SIDELOBE_LEVEL_MAX   FLOAT(52),
  VERT_SECOND_SIDELOBE_LEVEL_MIN  FLOAT(52),
  VERT_SECOND_SIDELOBE_LEVEL_MAX  FLOAT(52),
  VERT_THIRD_SIDELOBE_LEVEL_MIN   FLOAT(52),
  VERT_THIRD_SIDELOBE_LEVEL_MAX   FLOAT(52),
  RF_LEGACY_TYPE                  INTEGER                       DEFAULT -1,
  PRI_LEGACY_TYPE                 INTEGER                       DEFAULT -1,
  PD_LEGACY_TYPE                  INTEGER                       DEFAULT -1,
  PD_RISE_MIN                     FLOAT(52),
  PD_RISE_MAX                     FLOAT(52),
  PD_FALL_MIN                     FLOAT(52),
  PD_FALL_MAX                     FLOAT(52),
  BLANKING_DURATION_MIN           FLOAT(52),
  BLANKING_DURATION_MAX           FLOAT(52),
  BLANKING_PERIOD_MIN             FLOAT(52),
  BLANKING_PERIOD_MAX             FLOAT(52),
  POWER_DIFFERENCE_MIN            FLOAT(52),
  POWER_DIFFERENCE_MAX            FLOAT(52),
  BANDWIDTH_INST_THREE_MIN        FLOAT(52),
  BANDWIDTH_INST_THREE_MAX        FLOAT(52),
  BANDWIDTH_INST_SIX_MIN          FLOAT(52),
  BANDWIDTH_INST_SIX_MAX          FLOAT(52),
  BANDWIDTH_INST_TEN_MIN          FLOAT(52),
  BANDWIDTH_INST_TEN_MAX          FLOAT(52),
  BANDWIDTH_INST_TWENTY_MIN       FLOAT(52),
  BANDWIDTH_INST_TWENTY_MAX       FLOAT(52),
  PARAM_ASSOC                     VARCHAR2(390 ),
  SCAN_PRIMARY_TYPE               INTEGER,
  HOR_FIRST_SIDELOBE_POS_MIN      FLOAT(52),
  HOR_FIRST_SIDELOBE_POS_MAX      FLOAT(52),
  HOR_SECOND_SIDELOBE_POS_MIN     FLOAT(52),
  HOR_SECOND_SIDELOBE_POS_MAX     FLOAT(52),
  HOR_THIRD_SIDELOBE_POS_MIN      FLOAT(52),
  HOR_THIRD_SIDELOBE_POS_MAX      FLOAT(52),
  VERT_FIRST_SIDELOBE_POS_MIN     FLOAT(52),
  VERT_FIRST_SIDELOBE_POS_MAX     FLOAT(52),
  VERT_SECOND_SIDELOBE_POS_MIN    FLOAT(52),
  VERT_SECOND_SIDELOBE_POS_MAX    FLOAT(52),
  VERT_THIRD_SIDELOBE_POS_MIN     FLOAT(52),
  VERT_THIRD_SIDELOBE_POS_MAX     FLOAT(52),
  SECURITY_REVIEW_DATE            TIMESTAMP(6),
  ASSOC_INDEX                     INTEGER,
  MODULATION_CODE                 VARCHAR2(2 ),
  PRIORITY                        INTEGER,
  RF_TYPE                         INTEGER,
  PRI_TYPE                        INTEGER,
  PRIMARY KEY (RADAR_MODE_INDEX)
);
CREATE TABLE RADAR_MODE_COMMENTS
(
  RADAR_MODE_COMMENT_INDEX    INTEGER               NOT NULL,
  RADAR_MODE_INDEX            INTEGER               NOT NULL,
  TITLE                       VARCHAR2(30 )     NOT NULL,
  DATE_CREATED                TIMESTAMP(6)          NOT NULL,
  DATE_LAST_UPDATED           TIMESTAMP(6)          NOT NULL,
  TYPE                        VARCHAR2(10 )     NOT NULL,
  COMMENTS                    CLOB,
  THIRD_PARTY_RELEASABLE      INTEGER,
  SECURITY_REVIEW_DATE        TIMESTAMP(6),
  COMMENT_ORDER               INTEGER,
  SECLAB                      INTEGER               NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RADAR_MODE_COMMENT_INDEX)
);
CREATE TABLE RADAR_MODE_COMMENTS_P
(
  RADAR_MODE_COMMENT_INDEX    INTEGER               NOT NULL,
  RADAR_MODE_INDEX            INTEGER               NOT NULL,
  TITLE                       VARCHAR2(30 )     NOT NULL,
  DATE_CREATED                TIMESTAMP(6)          NOT NULL,
  DATE_LAST_UPDATED           TIMESTAMP(6)          NOT NULL,
  TYPE                        VARCHAR2(10 )     NOT NULL,
  COMMENTS                    CLOB,
  THIRD_PARTY_RELEASABLE      INTEGER,
  SECURITY_REVIEW_DATE        TIMESTAMP(6),
  COMMENT_ORDER               INTEGER,
  SECLAB                      INTEGER               NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RADAR_MODE_COMMENT_INDEX)
);
CREATE TABLE RADAR_MODE_LIFECYCLE
(
  RADAR_INDEX       INTEGER                     NOT NULL,
  RADAR_MODE_INDEX  INTEGER                     DEFAULT 1,
  RADAR_MODE_NAME   VARCHAR2(30 )           DEFAULT 'TEST',
  MODE_CODE         VARCHAR2(5 )            DEFAULT 'ZZ',
  SECLAB            INTEGER                     DEFAULT 0                  NOT NULL,
  PRIMARY KEY (RADAR_INDEX, RADAR_MODE_INDEX)
);
CREATE TABLE RADAR_MODE_LIFECYCLE_P
(
  RADAR_INDEX       INTEGER                     NOT NULL,
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RADAR_MODE_NAME   VARCHAR2(30 )           NOT NULL,
  MODE_CODE         VARCHAR2(5 )            NOT NULL,
  SECLAB            INTEGER                     DEFAULT NULL                  NOT NULL,
  PRIMARY KEY (RADAR_INDEX, RADAR_MODE_INDEX)
);
CREATE TABLE RADAR_PD_VALUES
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_INDEX          INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PD_MIN            FLOAT(52)                   NOT NULL,
  PD_MAX            FLOAT(52)                   NOT NULL,
  PD_RISE_MIN       FLOAT(52),
  PD_RISE_MAX       FLOAT(52),
  PD_FALL_MIN       FLOAT(52),
  PD_FALL_MAX       FLOAT(52),
  PRIMARY KEY (RADAR_MODE_INDEX, PD_INDEX)
);
CREATE TABLE RADAR_PD_VALUES_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_INDEX          INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PD_MIN            FLOAT(52)                   NOT NULL,
  PD_MAX            FLOAT(52)                   NOT NULL,
  PD_RISE_MIN       FLOAT(52),
  PD_RISE_MAX       FLOAT(52),
  PD_FALL_MIN       FLOAT(52),
  PD_FALL_MAX       FLOAT(52),
  PRIMARY KEY (RADAR_MODE_INDEX, PD_INDEX)
);
CREATE TABLE RADAR_PD_SEQUENCE_NAME
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_SEQ_ID         INTEGER                     NOT NULL,
  PD_SEQ_NAME       VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PD_SEQ_ID)
);
CREATE TABLE RADAR_PD_SEQUENCE_NAME_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_SEQ_ID         INTEGER                     NOT NULL,
  PD_SEQ_NAME       VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PD_SEQ_ID)
);
CREATE TABLE RADAR_PD_SEQUENCE
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_SEQUENCE_NUM   INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PD_INDEX          INTEGER                     NOT NULL,
  PD_SEQ_ID         INTEGER                     DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PD_SEQUENCE_NUM, PD_SEQ_ID)
);
CREATE TABLE RADAR_PD_SEQUENCE_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_SEQUENCE_NUM   INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PD_INDEX          INTEGER                     NOT NULL,
  PD_SEQ_ID         INTEGER                     DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PD_SEQUENCE_NUM, PD_SEQ_ID)
);
CREATE TABLE RADAR_PD_SPOT_VALUES
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_MIN            FLOAT(52)                   NOT NULL,
  PD_MAX            FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PD_MIN, PD_MAX)
);
CREATE TABLE RADAR_PD_SPOT_VALUES_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PD_MIN            FLOAT(52)                   NOT NULL,
  PD_MAX            FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PD_MIN, PD_MAX)
);
CREATE TABLE RADAR_RF_VALUES
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_INDEX          INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  RF_MIN            FLOAT(52)                   NOT NULL,
  RF_MAX            FLOAT(52)                   NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_INDEX)
);
CREATE TABLE RADAR_RF_VALUES_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_INDEX          INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  RF_MIN            FLOAT(52)                   NOT NULL,
  RF_MAX            FLOAT(52)                   NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_INDEX)
);
CREATE TABLE RADAR_RF_SEQUENCE_NAME
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_SEQ_ID         INTEGER                     NOT NULL,
  RF_SEQ_NAME       VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_SEQ_ID)
);
CREATE TABLE RADAR_RF_SEQUENCE_NAME_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_SEQ_ID         INTEGER                     NOT NULL,
  RF_SEQ_NAME       VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_SEQ_ID)
);
CREATE TABLE RADAR_RF_SEQUENCE
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_SEQUENCE_NUM   INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  RF_INDEX          INTEGER                     NOT NULL,
  RF_SEQ_ID         INTEGER                     DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_SEQUENCE_NUM, RF_SEQ_ID)
);
CREATE TABLE RADAR_RF_SEQUENCE_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_SEQUENCE_NUM   INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  RF_INDEX          INTEGER                     NOT NULL,
  RF_SEQ_ID         INTEGER                     DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_SEQUENCE_NUM, RF_SEQ_ID)
);
CREATE TABLE RADAR_RF_SPOT_VALUES
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_MIN            FLOAT(52)                   NOT NULL,
  RF_MAX            FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_MIN, RF_MAX)
);
CREATE TABLE RADAR_RF_SPOT_VALUES_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  RF_MIN            FLOAT(52)                   NOT NULL,
  RF_MAX            FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, RF_MIN, RF_MAX)
);
CREATE TABLE RADAR_PRI_VALUES
(
  RADAR_MODE_INDEX    INTEGER                   NOT NULL,
  PRI_INDEX           INTEGER                   NOT NULL,
  SECLAB              INTEGER                   NOT NULL,
  PRI_MIN             FLOAT(52)                 NOT NULL,
  PRI_MAX             FLOAT(52)                 NOT NULL,
  DWELL_DURATION_MIN  FLOAT(52),
  DWELL_DURATION_MAX  FLOAT(52),
  PULSES_PER_DWELL    INTEGER,
  TRANSITION_MIN      FLOAT(52),
  TRANSITION_MAX      FLOAT(52),
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_INDEX)
);
CREATE TABLE RADAR_PRI_VALUES_P
(
  RADAR_MODE_INDEX    INTEGER                   NOT NULL,
  PRI_INDEX           INTEGER                   NOT NULL,
  SECLAB              INTEGER                   NOT NULL,
  PRI_MIN             FLOAT(52)                 NOT NULL,
  PRI_MAX             FLOAT(52)                 NOT NULL,
  DWELL_DURATION_MIN  FLOAT(52),
  DWELL_DURATION_MAX  FLOAT(52),
  PULSES_PER_DWELL    INTEGER,
  TRANSITION_MIN      FLOAT(52),
  TRANSITION_MAX      FLOAT(52),
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_INDEX)
);
CREATE TABLE RADAR_PRI_SEQUENCE_NAME
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PRI_SEQ_ID        INTEGER                     NOT NULL,
  PRI_SEQ_NAME      VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_SEQ_ID)
);
CREATE TABLE RADAR_PRI_SEQUENCE_NAME_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PRI_SEQ_ID        INTEGER                     NOT NULL,
  PRI_SEQ_NAME      VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_SEQ_ID)
);
CREATE TABLE RADAR_PRI_SEQUENCE
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PRI_SEQUENCE_NUM  INTEGER                     NOT NULL,
  SECLAB            INTEGER                     DEFAULT 1 NOT NULL,
  PRI_INDEX         INTEGER                     NOT NULL,
  PULSES_PER_DWELL  INTEGER,
  PRI_SEQ_ID        INTEGER                     DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_SEQUENCE_NUM, PRI_SEQ_ID)
);
CREATE TABLE RADAR_PRI_SEQUENCE_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PRI_SEQUENCE_NUM  INTEGER                     NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRI_INDEX         INTEGER                     NOT NULL,
  PULSES_PER_DWELL  INTEGER,
  PRI_SEQ_ID        INTEGER                     DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_SEQUENCE_NUM, PRI_SEQ_ID)
);
CREATE TABLE RADAR_PRI_SPOT_VALUES
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PRI_MIN           FLOAT(52)                   NOT NULL,
  PRI_MAX           FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_MIN, PRI_MAX)
);
CREATE TABLE RADAR_PRI_SPOT_VALUES_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  PRI_MIN           FLOAT(52)                   NOT NULL,
  PRI_MAX           FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, PRI_MIN, PRI_MAX)
);
CREATE TABLE RADAR_PRI_GROUP_SPACING
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  SEQUENCE_NUM      INTEGER                     NOT NULL,
  GROUP_SPACING     FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, SEQUENCE_NUM)
);
CREATE TABLE RADAR_PRI_GROUP_SPACING_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  SEQUENCE_NUM      INTEGER                     NOT NULL,
  GROUP_SPACING     FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, SEQUENCE_NUM)
);
CREATE TABLE RADAR_MOP_CW
(
  RADAR_MODE_INDEX               INTEGER        NOT NULL,
  MOP_CW_INDEX                   INTEGER        NOT NULL,
  SECLAB                         INTEGER        NOT NULL,
  MOP_CW_MODULATION_TYPE         INTEGER,
  MOP_CW_BIT_DURATION_MIN        FLOAT(52),
  MOP_CW_BIT_DURATION_MAX        FLOAT(52),
  MOP_CW_CONTINUITY              INTEGER,
  MOP_CW_NUM_ELEMENTS            INTEGER,
  MOP_CW_NUM_POSITIONS           INTEGER,
  MOP_CW_PATTERN                 INTEGER,
  MOP_CW_PATTERN_DRIVER          VARCHAR2(400 ),
  MOP_CW_PATTERN_PERIOD_MIN      FLOAT(52),
  MOP_CW_PATTERN_PERIOD_MAX      FLOAT(52),
  MOP_CW_PATTERN_RULE            VARCHAR2(400 ),
  MOP_CW_RANGE_MIN               FLOAT(52),
  MOP_CW_RANGE_MAX               FLOAT(52),
  MOP_CW_RATE_MIN                FLOAT(52),
  MOP_CW_RATE_MAX                FLOAT(52),
  MOP_CW_STANDARD_DEVIATION      FLOAT(52),
  MOP_CW_STEP_MIN                FLOAT(52),
  MOP_CW_STEP_MAX                FLOAT(52),
  MOP_CW_MEAN_MIN                FLOAT(52),
  MOP_CW_MEAN_MAX                FLOAT(52),
  PD_INDEX                       INTEGER,
  MOP_CW_LEGACY_TYPE             INTEGER,
  MOP_CW_PATTERN_NAME            VARCHAR2(20 ),
  MOP_CW_ON_TIME_MIN             FLOAT(52),
  MOP_CW_ON_TIME_MAX             FLOAT(52),
  MOP_CW_OFF_TIME_MIN            FLOAT(52),
  MOP_CW_OFF_TIME_MAX            FLOAT(52),
  MOP_CW_BIT_SEQ_LENGTH_MIN      INTEGER,
  MOP_CW_BIT_SEQ_LENGTH_MAX      INTEGER,
  MOP_CW_DUTY_CYCLE_MIN          FLOAT(52),
  MOP_CW_DUTY_CYCLE_MAX          FLOAT(52),
  SPECTRAL_COMPONENTS_MIN        FLOAT(52),
  SPECTRAL_COMPONENTS_MAX        FLOAT(52),
  LOOK_THROUGH_DURATION_MIN      FLOAT(52),
  LOOK_THROUGH_DURATION_MAX      FLOAT(52),
  LOOK_THROUGH_PERIOD_MIN        FLOAT(52),
  LOOK_THROUGH_PERIOD_MAX        FLOAT(52),
  MOP_CW_TIME_BANDWIDTH_PRODUCT  INTEGER,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_INDEX)
);
CREATE TABLE RADAR_MOP_CW_P
(
  RADAR_MODE_INDEX               INTEGER        NOT NULL,
  MOP_CW_INDEX                   INTEGER        NOT NULL,
  SECLAB                         INTEGER        NOT NULL,
  MOP_CW_MODULATION_TYPE         INTEGER,
  MOP_CW_BIT_DURATION_MIN        FLOAT(52),
  MOP_CW_BIT_DURATION_MAX        FLOAT(52),
  MOP_CW_CONTINUITY              INTEGER,
  MOP_CW_NUM_ELEMENTS            INTEGER,
  MOP_CW_NUM_POSITIONS           INTEGER,
  MOP_CW_PATTERN                 INTEGER,
  MOP_CW_PATTERN_DRIVER          VARCHAR2(400 ),
  MOP_CW_PATTERN_PERIOD_MIN      FLOAT(52),
  MOP_CW_PATTERN_PERIOD_MAX      FLOAT(52),
  MOP_CW_PATTERN_RULE            VARCHAR2(400 ),
  MOP_CW_RANGE_MIN               FLOAT(52),
  MOP_CW_RANGE_MAX               FLOAT(52),
  MOP_CW_RATE_MIN                FLOAT(52),
  MOP_CW_RATE_MAX                FLOAT(52),
  MOP_CW_STANDARD_DEVIATION      FLOAT(52),
  MOP_CW_STEP_MIN                FLOAT(52),
  MOP_CW_STEP_MAX                FLOAT(52),
  MOP_CW_MEAN_MIN                FLOAT(52),
  MOP_CW_MEAN_MAX                FLOAT(52),
  PD_INDEX                       INTEGER,
  MOP_CW_LEGACY_TYPE             INTEGER,
  MOP_CW_PATTERN_NAME            VARCHAR2(20 ),
  MOP_CW_ON_TIME_MIN             FLOAT(52),
  MOP_CW_ON_TIME_MAX             FLOAT(52),
  MOP_CW_OFF_TIME_MIN            FLOAT(52),
  MOP_CW_OFF_TIME_MAX            FLOAT(52),
  MOP_CW_BIT_SEQ_LENGTH_MIN      INTEGER,
  MOP_CW_BIT_SEQ_LENGTH_MAX      INTEGER,
  MOP_CW_DUTY_CYCLE_MIN          FLOAT(52),
  MOP_CW_DUTY_CYCLE_MAX          FLOAT(52),
  SPECTRAL_COMPONENTS_MIN        FLOAT(52),
  SPECTRAL_COMPONENTS_MAX        FLOAT(52),
  LOOK_THROUGH_DURATION_MIN      FLOAT(52),
  LOOK_THROUGH_DURATION_MAX      FLOAT(52),
  LOOK_THROUGH_PERIOD_MIN        FLOAT(52),
  LOOK_THROUGH_PERIOD_MAX        FLOAT(52),
  MOP_CW_TIME_BANDWIDTH_PRODUCT  INTEGER,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_INDEX)
);
CREATE TABLE RADAR_MOP_CW_VALUES
(
  RADAR_MODE_INDEX    INTEGER                   NOT NULL,
  MOP_CW_INDEX        INTEGER                   NOT NULL,
  MOP_CW_VALUE_INDEX  INTEGER                   NOT NULL,
  SECLAB              INTEGER                   NOT NULL,
  MOP_CW_MIN          FLOAT(52)                 NOT NULL,
  MOP_CW_MAX          FLOAT(52)                 NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_INDEX, MOP_CW_VALUE_INDEX)
);
CREATE TABLE RADAR_MOP_CW_VALUES_P
(
  RADAR_MODE_INDEX    INTEGER                   NOT NULL,
  MOP_CW_INDEX        INTEGER                   NOT NULL,
  MOP_CW_VALUE_INDEX  INTEGER                   NOT NULL,
  SECLAB              INTEGER                   NOT NULL,
  MOP_CW_MIN          FLOAT(52)                 NOT NULL,
  MOP_CW_MAX          FLOAT(52)                 NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_INDEX, MOP_CW_VALUE_INDEX)
);
CREATE TABLE RADAR_MOP_CW_SEQ_NAME
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  MOP_CW_INDEX      INTEGER                     NOT NULL,
  MOP_CW_SEQ_ID     INTEGER                     NOT NULL,
  MOP_CW_SEQ_NAME   VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_INDEX, MOP_CW_SEQ_ID)
);
CREATE TABLE RADAR_MOP_CW_SEQ_NAME_P
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  MOP_CW_INDEX      INTEGER                     NOT NULL,
  MOP_CW_SEQ_ID     INTEGER                     NOT NULL,
  MOP_CW_SEQ_NAME   VARCHAR2(32 ),
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_INDEX, MOP_CW_SEQ_ID)
);
CREATE TABLE RADAR_MOP_CW_SEQUENCE
(
  RADAR_MODE_INDEX     INTEGER                  NOT NULL,
  MOP_CW_INDEX         INTEGER                  NOT NULL,
  MOP_CW_SEQUENCE_NUM  INTEGER                  NOT NULL,
  SECLAB               INTEGER                  NOT NULL,
  MOP_CW_VALUE_INDEX   INTEGER                  NOT NULL,
  MOP_CW_DURATION      FLOAT(52),
  MOP_CW_SEQ_ID        INTEGER                  DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_SEQUENCE_NUM, MOP_CW_INDEX, MOP_CW_SEQ_ID)
);
CREATE TABLE RADAR_MOP_CW_SEQUENCE_P
(
  RADAR_MODE_INDEX     INTEGER                  NOT NULL,
  MOP_CW_INDEX         INTEGER                  NOT NULL,
  MOP_CW_SEQUENCE_NUM  INTEGER                  NOT NULL,
  SECLAB               INTEGER                  NOT NULL,
  MOP_CW_VALUE_INDEX   INTEGER                  NOT NULL,
  MOP_CW_DURATION      FLOAT(52),
  MOP_CW_SEQ_ID        INTEGER                  DEFAULT 0                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, MOP_CW_SEQUENCE_NUM, MOP_CW_INDEX, MOP_CW_SEQ_ID)
);
CREATE TABLE RADAR_MODE_PA_DIFF_IN_GROUP
(
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  SEQUENCE_NUM      INTEGER                     NOT NULL,
  PA_DIFF           FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, SEQUENCE_NUM)
);
CREATE TABLE "RADAR_MODE_PA_DIFF_IN_GROUP_P" (
  RADAR_MODE_INDEX  INTEGER                     NOT NULL,
  SEQUENCE_NUM      INTEGER                     NOT NULL,
  PA_DIFF           FLOAT(52)                   NOT NULL,
  SECLAB            INTEGER                     NOT NULL,
  PRIMARY KEY (RADAR_MODE_INDEX, SEQUENCE_NUM)
);
