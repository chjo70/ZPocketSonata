/****** Object: View [dbo].[VIEW_RADARMODE_THREAT]   Script Date: 2019-04-22 오전 11:19:49 ******/
USE [ELINT];
GO
SET ANSI_NULLS ON;
GO
SET QUOTED_IDENTIFIER ON;
GO

drop VIEW [dbo].[VIEW_RADARMODE_THREAT]

/* https://codeday.me/ko/qa/20190330/176631.html 참조.. */
PRINT 'Creating Player View'
GO

CREATE VIEW [dbo].[VIEW_RADARMODE_THREAT]
AS
select a.RADAR_MODE_NAME, 
       a.RADAR_MODE_INDEX, 
       a.DATE_CREATED, 
       a.DATE_LAST_UPDATED, 
       a.DATE_FIRST_SEEN, 
       a.DATE_LAST_SEEN, 
       a.PLATFORM, 
       a.SIGNAL_TYPE, 
       a.RF_TYPE, 
       a.RF_TYPICAL_MIN, 
       a.RF_TYPICAL_MAX, 
       a.RF_PATTERN_TYPE, 
       a.RF_NUM_POSITIONS, 
       a.RF_PATTERN_PERIOD_MIN, 
       a.RF_PATTERN_PERIOD_MAX, 
       a.PRI_TYPE, 
       a.PRI_TYPICAL_MIN, 
       a.PRI_TYPICAL_MAX, 
       a.PRI_PATTERN_TYPE, 
       a.PRI_NUM_POSITIONS, 
       a.PRI_PATTERN_PERIOD_MIN, 
       a.PRI_PATTERN_PERIOD_MAX, 
       a.PW_TYPICAL_MIN, 
       a.PW_TYPICAL_MAX, 
       a.VALIDATION, 
       b.THREAT_INDEX, 
       b.LATITUDE, 
       b.LONGITUDE, 
       b.SITE_NAME, 
       b.PLATFORM_THREAT

from dbo.RADARMODE as a inner join dbo.threat as b on A.radar_mode_name=b.radar_mode_name
GO
