/*
 * 본 문서는 시스템의 정의문을 정의합니다.
 * */


#ifndef _DEFINES_H
#define _DEFINES_H

////////////////////////////////////////////////////////////////////////////////
// 아래는 문자열에 관련된 정의를 나열합니다.
#define PROGRAM_NAME        "PocketSonata"
#define PROGRAM_VERSION     "Ver 0.1a"

// 실행 파일이 있는 위치에서 로그 디렉토리
#define LOG_DIRECTORY       ("/LOG")

////////////////////////////////////////////////////////////////////////////////
// 아래는 프로그램 설정과 관련된 정의를 나열합니다.

// 메인 프로그램을 데몬으로 구동합니다.
//#define _DAEMON_

// ZYNQ 보드의 GPIO 값으로 AUTO 설정함을 정의한다.
//#define _AUTO_ID_

// readline 라이브러리를 이용하여 쉘 입력을 처리한다.
#define _READLINE_

// LOG 디렉토리에서 실행 파일의 경로를 기준으로 LOG_DIRECTORY 경로를 생성한다.
//#define _LOG_RELATIVE_PATH_

// LOG 풀력시 함수, 라인 등의 정보를 출력한다.
//#define _LOG_WHERE


// 변수 타입을 정의합니다.
typedef unsigned int UINT;


// 포토 를 정의합니다.
#define MAX_CLIENTS     (30)
#define PORT            (8888)
#define CCU_PORT        (13030)
#define PMC_PORT        (13040)


/////////////////////////////////////////////////////////////////////////////////

#define DETECT_CHANNEL  (1)
#define TRACK_CHANNEL   (256)
#define SCAN_CHANNEL    (256)
#define USER_CHANNEL    (1)
#define TOTAL_CHANNELS  (DETECT_CHANNEL+TRACK_CHANNEL+SCAN_CHANNEL+USER_CHANNEL)



#endif // _DEFINES_H
