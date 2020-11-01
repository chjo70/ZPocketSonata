
#include <stdlib.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include "./Include/defines.h"
#include "./Include/sysmsg.h"

#include <fcntl.h>

enum enTableHeader {
    enNo=0,
    enNoAET,
    enFirstSeen,
    enLastSeen,
    enPriority,
    enELNOT,

    enSIGTYPE,
    enAOA,
    enFREQ,
    enPRI,
    enPW,
    enPA,
    enSCAN,
    enEMITTER,
    enTHREAT,
    enID,

    enMax
} ;

char szTableHeader[enMax][30] = { "번호", "#", "최초접촉", "최근접촉", "위협도", "ELNOT", "신호형태", "방위[도]", "주파수[MHz]", "PRI[us]", "펄스폭[ns]", "신호세기[dBm]", "스캔", "에미터명", "위협명", "식별" } ;

void _InitResolution();



/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int i;

    ui->setupUi(this);

    ui->spinBoxStartAddress->setRange(UINT_MAX);
    ui->spinBoxStartAddress->setPrefix("0x");

    connect( & m_theTcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()) );
    connect( & m_theTcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect( & m_theTcpSocket, SIGNAL(readyRead()), this, SLOT(onReadMessage()));
    connect( & m_theTcpSocket, SIGNAL(error()), this, SLOT(onError()));

    QStringList aettableHeader;

    for( i=0 ; i < enMax ; ++i ) {
        aettableHeader << szTableHeader[i];
    }

    ui->aettableWidget->setColumnCount( enMax );
    ui->aettableWidget->setHorizontalHeaderLabels( aettableHeader );

    ui->aettableWidget->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color:#404040;color:#FFFFFF;}" );

    vTable.clear();

    _InitResolution();

    m_nCoList = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnection()
{

}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
}

void MainWindow::onError(QAbstractSocket::SocketState socketState)
{
    printf( "\nssss" );
}

void MainWindow::onReadyRead()
{
}

/**
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{
    bool bConnected;
    int iTotalRow, iRow;

    nextBlockSize = 0;

    if( m_bConnect == false ) {
        // 자신의 IP 에서 연결 요구하고 연결 실패되면 직접 다이렉트로 연결을 시도한다.
        m_theTcpSocket.connectToHost(QHostAddress::LocalHost, CCU_PORT );
        bConnected = m_theTcpSocket.waitForConnected();

        //ui->aettableWidget->clear();
        iTotalRow = ui->aettableWidget->rowCount();
        for( iRow=0 ; iRow < iTotalRow ; ++iRow ) {
            ui->aettableWidget->removeRow( iRow );
        }

        if( bConnected == false ) {
            m_theTcpSocket.connectToHost( "zcu111.com", CCU_PORT );
        }

        m_nCoList = 0;
    }
    else {
        m_theTcpSocket.close();

        EnableControl( false );

        vTable.clear();
    }

}

/**
 * @brief MainWindow::onConnectServer
 */
void MainWindow::onConnectServer()
{
    ui->pushButton->setText( tr("연결 해지") );
    m_bConnect = true;

    m_bHeader = true;

    EnableControl( true );

}

/**
 * @brief MainWindow::EnableControl
 * @param bEnable
 */
void MainWindow::EnableControl( bool bEnable )
{
    ui->MemoryDump->setEnabled( bEnable );
    //ui->ESMode->setEnabled( bEnable );
    //ui->EWMode->setEnabled( bEnable );
    ui->MODE->setEnabled( bEnable );
    ui->BITTEST->setEnabled( bEnable );

    ui->AnalStart->setEnabled( bEnable );

    ui->pushButton_ReloadLibrary->setEnabled( bEnable );
    ui->pushButton_SimPDW->setEnabled( bEnable );

    ui->bit_result->setText( "" );

}

/**
 * @brief MainWindow::connectionClosedByServer
 */
void MainWindow::connectionClosedByServer()
{
    ui->pushButton->setText( tr("연결") );
    m_bConnect = false;

    m_bHeader = true;

    EnableControl( false );
}


/**
 * @brief MainWindow::onReadMessage
 */
void MainWindow::onReadMessage()
{
    int iRead;
    char *pLanData;

    UINT uiTotalRead=0;

    STR_LAN_HEADER strLanHeader;
    char szLanData[MAX_LAN_DATA];

    while( true ) {
         //nextBlcokSize 가 0 이면 아직 데이터를 못받은것
        if( m_bHeader == true ) {
            pLanData = (char *) & strLanHeader;
            if (( iRead = m_theTcpSocket.read( & pLanData[uiTotalRead], sizeof(STR_LAN_HEADER)-uiTotalRead ) ) == 0 ) {
                break;
                // m_theTcpSocket.disconnectFromHost();
                //CloseSocket( iSocket, & address, & iClientSocket[i] );
            }
            else {
                uiTotalRead += iRead;
                if( uiTotalRead == sizeof(STR_LAN_HEADER) ) {
                    m_bHeader = false;
                    uiTotalRead = 0;
                }
            }
        }
        else {
            pLanData = (char *) & szLanData;
            if (( iRead = m_theTcpSocket.read( & pLanData[uiTotalRead], strLanHeader.uiLength-uiTotalRead ) ) == 0 ) {
                break;
                //m_theTcpSocket.disconnectFromHost();
            }
            else {
                uiTotalRead += iRead;
                if( uiTotalRead == strLanHeader.uiLength ) {
                    m_bHeader = true;
                    uiTotalRead = 0;

                    //데이터를 표시
                    ParseAndDisplay( & strLanHeader, & szLanData[0] );

                    QTextCharFormat format;
                    format.setForeground(QColor(0x6F,0x77,0x97));
                    QTextCursor cursor = ui->memoryDump->textCursor();
                    cursor.select(QTextCursor::Document);
                    cursor.mergeCharFormat(format);

                    break;
                }
            }
        }

    }

}

/**
 * @brief MainWindow::ParseAndDisplay
 * @param pstLanHeader
 * @param pByteData
 */
void MainWindow::ParseAndDisplay( STR_LAN_HEADER *pstLanHeader, char *pByteData )
{
    unsigned int i, j;

    QString qBuffer;

    switch( pstLanHeader->uiOpCode ) {
    case enRES_MODE :
        {
            UINT uiMode;

            ui->MODE->setEnabled( true );

            uiMode = (UINT) *pByteData;

            // 클라이언트 랜 소켓 닫는다.
            if( uiMode == enREADY_MODE ) {
                m_theTcpSocket.close();
            }
        }
        break;

    case enRES_DUMP_LIST :
        {
            char *pData, *pValue;
            STR_RES_DUMP_LIST *pstrResDumpList = ( STR_RES_DUMP_LIST * ) pByteData;

            ui->memoryDump->clear();

            pData = & pstrResDumpList->cData[0];
            for( i=0 ; i < pstrResDumpList->strReqDumpList.uiDataLength ; i+=16 ) {
                qBuffer.sprintf( "0x%08X  " , pstrResDumpList->strReqDumpList.uiAddress+i );
                pValue = pData;
                ui->memoryDump->insertPlainText( qBuffer );
                for( j=0 ; j < 16 && i+j < pstrResDumpList->strReqDumpList.uiDataLength ; ++j ) {
                    qBuffer.sprintf( "%02X " , *pValue++ );
                    ui->memoryDump->insertPlainText( qBuffer );
                }

                pValue = pData;
                for( j=0 ; j < 16 && i+j < pstrResDumpList->strReqDumpList.uiDataLength ; ++j ) {
                    qBuffer.sprintf( "%01c" , *pValue );
                    if( isprint( *pValue ) )
                        ui->memoryDump->insertPlainText( qBuffer );
                    else
                        ui->memoryDump->insertPlainText( " " );
                    ++ pValue;
                }
                pData += 16;

                ui->memoryDump->insertPlainText( "\n" );
            }
        }
        break;

    case enRES_IBIT :
        ShowIBitResult( pByteData );

        ui->BITTEST->setEnabled( true );
        break;

    case enRES_CBIT :
        ShowCBitResult( pByteData );

        ui->BITTEST->setEnabled( true );
        break;

    case esAET_NEW_CCU :
        InsertAETTable( pByteData );
        break;

    case esAET_UPD_CCU :
        UpdateAETTable( pByteData );
        break;

    case esAET_DEL_CCU :
        DeleteAETTable( pByteData );
        break;

    default :
        break;
    }

    //ui->memoryDump->moveCursor( QTextCursor::start);

}

/**
 * @brief MainWindow::InsertTable
 * @param pByteData
 */
void MainWindow::InsertAETTable( void *pByteData )
{
    STR_AET *pAET;
    STR_LIST_TABLE stListTable;

    pAET = ( STR_AET *) pByteData;

    stListTable.uiABTID = pAET->noEMT;

    ui->aettableWidget->insertRow( ui->aettableWidget->rowCount() );

    stListTable.iIndexOfTable = ui->aettableWidget->rowCount() - 1;

    ++ m_nCoList;

    UpdateRow( ui->aettableWidget, );

    vTable.push_back( stListTable );

}

void MainWindow::UpdateRow()
{
    QString qTemp;

    struct tm *pTm;


    qTemp.sprintf( "%d", m_nCoList );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enNo, new QTableWidgetItem(qTemp) );
    qTemp.sprintf( "%d", pAET->noEMT );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enNoAET, new QTableWidgetItem(qTemp) );
    qTemp.sprintf( "%s", aet_signal_type[pAET->sigType] );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enSIGTYPE, new QTableWidgetItem(qTemp) );
    qTemp.sprintf( "%.1f", SONATA::DECODE::DOA( pAET->aoa ) );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enAOA, new QTableWidgetItem(qTemp) );
    if( pAET->frq.type == _PATTERN_AGILE ) {
        qTemp.sprintf( "%s(%.1f) %7.2f(%.1f,%.1f)", aet_freq_type[pAET->frq.type], SONATA::DECODE::TOA(pAET->frq.patPrd), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.mean ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.min ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.max ) );
    }
    else {
        qTemp.sprintf( "%s %-7.2f(%.2f,%.2f)", aet_freq_type[pAET->frq.type], SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.mean ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.min ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.max ) );
    }
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enFREQ, new QTableWidgetItem(qTemp) );

    if( pAET->pri.type == _JITTER_PATTERN ) {
        qTemp.sprintf( "%s(%.1f) %7.2f(%.1f,%.1f)", aet_pri_type[pAET->pri.type], SONATA::DECODE::TOA(pAET->pri.patPrd), SONATA::DECODE::TOA( pAET->pri.mean ), SONATA::DECODE::TOA(pAET->pri.min), SONATA::DECODE::TOA(pAET->pri.max) );
    }
    else {
        qTemp.sprintf( "%s %-7.2f(%.2f,%.2f)", aet_pri_type[pAET->pri.type], SONATA::DECODE::TOA( pAET->pri.mean ), SONATA::DECODE::TOA( pAET->pri.min ), SONATA::DECODE::TOA( pAET->pri.max ) );
    }
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enPRI, new QTableWidgetItem(qTemp) );

    qTemp.sprintf( "%7.0f(%.0f,%.0f)", SONATA::DECODE::PW( pAET->pw.mean ), SONATA::DECODE::PW(pAET->pw.min), SONATA::DECODE::PW(pAET->pw.max) );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enPW, new QTableWidgetItem(qTemp) );

    qTemp.sprintf( "%7.1f(%.1f,%.1f)", SONATA::DECODE::PA( pAET->pa.mean ), SONATA::DECODE::PA(pAET->pa.min), SONATA::DECODE::PA(pAET->pa.max) );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enPA, new QTableWidgetItem(qTemp) );

    if( pAET->as.type == CONICAL ) {
        qTemp.sprintf( "%s %s%7.1f", aet_asp_stat_ch[pAET->as.stat], aet_asp_type_ch[pAET->as.type], SONATA::DECODE::TOA(pAET->as.prd) );
    }
    else {
        qTemp.sprintf( "%s %s%7.1f", aet_asp_stat_ch[pAET->as.stat], aet_asp_type_ch[pAET->as.type], SONATA::DECODE::TOA(pAET->as.prd) );
    }
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enSCAN, new QTableWidgetItem(qTemp) );

    pTm = localtime( & pAET->seen.frst );
    qTemp.sprintf( "%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enFirstSeen, new QTableWidgetItem(qTemp) );

    pTm = localtime( & pAET->seen.last );
    qTemp.sprintf( "%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enLastSeen, new QTableWidgetItem(qTemp) );

    qTemp.sprintf( "%d", pAET->priLev );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enPriority, new QTableWidgetItem(qTemp) );

    if( pAET->id.coAmbi != 0 ) {
        qTemp.sprintf( "%s", pAET->elintNotation );
        ui->aettableWidget->setItem( stListTable.iIndexOfTable, enELNOT, new QTableWidgetItem(qTemp) );

        qTemp.sprintf( "%s", pAET->emitterName );
        ui->aettableWidget->setItem( stListTable.iIndexOfTable, enEMITTER, new QTableWidgetItem(qTemp) );

        qTemp.sprintf( "%s", pAET->threatName );
        ui->aettableWidget->setItem( stListTable.iIndexOfTable, enTHREAT, new QTableWidgetItem(qTemp) );

        qTemp.sprintf( "%d(%d,%d,%d)", pAET->id.coAmbi, pAET->id.noIPL[0], pAET->id.noIPL[1], pAET->id.noIPL[2] );
        ui->aettableWidget->setItem( stListTable.iIndexOfTable, enID, new QTableWidgetItem(qTemp) );
    }
    else {

    }

    ui->aettableWidget->resizeColumnsToContents();
}

/**
 * @brief MainWindow::UpdateTable
 * @param pByteData
 */
void MainWindow::UpdateAETTable( void *pByteData )
{
    int i;
    int iTotalRowCount = ui->aettableWidget->rowCount();

    STR_AET *pAET;

    QString qStrNoAET;

    pAET = ( STR_AET *) pByteData;

    qStrNoAET.sprintf( "%d", pAET->noEMT );

    for( i=0 ; i < iTotalRowCount ; ++i ) {
        QString qString;

        qString = ui->aettableWidget->item(i, enNoAET )->text();

        if( qString == qStrNoAET ) {

        }

    }
}

/**
 * @brief MainWindow::DeleteTable
 * @param pByteData
 */
void MainWindow::DeleteAETTable( void *pByteData )
{
    -- m_nCoList;
}

/**
 * @brief MainWindow::ShowIBitResult
 * @param pData
 */
void MainWindow::ShowIBitResult( void *pData )
{
    UNI_ES_IBIT *pESIBit;
    QString qBitResult;

    pESIBit = ( UNI_ES_IBIT * ) pData;
    qBitResult.sprintf( "0x%x", pESIBit->w32 );
    ui->bit_result->setText( qBitResult );

}

void MainWindow::ShowCBitResult( void *pData )
{
    STR_ES_CBIT *pESCBit;
    QString qBitResult;

    pESCBit = ( STR_ES_CBIT * ) pData;
    qBitResult.sprintf( "0x%x/0x%x/0x%x, 0x%x", pESCBit->sp[0].w32, pESCBit->sp[1].w32, pESCBit->sp[2].w32, pESCBit->rsa.w32 );
    ui->bit_result->setText( qBitResult );

}

/**
 * @brief MainWindow::SendRSA
 * @param pstrLanHeader
 * @param pData
 * @param iLength
 * @return
 */
int MainWindow::SendRSA( STR_LAN_HEADER *pstrLanHeader, void *pData, int iLength )
{
    int iRet;

    iRet = m_theTcpSocket.write( (char *) pstrLanHeader, sizeof(STR_LAN_HEADER) );

    if( pData != NULL && iRet > 0 ) {
        iRet = m_theTcpSocket.write( (char *) pData, iLength );
    }
    else {
        //LOGMSG( enWarning, )
    }

    return iRet;

}


/**
 * @brief MainWindow::on_MemoryDump_clicked
 */
void MainWindow::on_MemoryDump_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;
    STR_REQ_DUMP_LIST strReqDumpList;

    strLanHeader.uiOpCode = enREQ_DUMP_LIST;
    strLanHeader.uiLength = sizeof( STR_REQ_DUMP_LIST );

    strReqDumpList.uiAddress = ui->spinBoxStartAddress->value();
    strReqDumpList.uiDataSize = 1;
    strReqDumpList.uiDataLength = 50;

    iRet = SendRSA( & strLanHeader, & strReqDumpList, strLanHeader.uiLength );

}

/**
 * @brief MainWindow::on_ESMode_clicked
 */
void MainWindow::on_ESMode_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;
    UINT uiMode;

    strLanHeader.uiOpCode = enREQ_MODE;
    strLanHeader.uiLength = sizeof( int );

    uiMode = enES_MODE;

    iRet = SendRSA( & strLanHeader, & uiMode, strLanHeader.uiLength );

}

/**
 * @brief MainWindow::on_EWMode_clicked
 */
void MainWindow::on_EWMode_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;
    UINT uiMode;

    strLanHeader.uiOpCode = enREQ_MODE;
    strLanHeader.uiLength = sizeof( int );

    uiMode = enEW_MODE;

    iRet = SendRSA( & strLanHeader, & uiMode, strLanHeader.uiLength );
}

/**
 * @brief 대기 모드 명령으로 내부 메시지를 전달한다.
 */
void MainWindow::on_ReadyMode_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;
    UINT uiMode;

    strLanHeader.uiOpCode = enREQ_MODE;
    strLanHeader.uiLength = sizeof( int );

    uiMode = enREADY_MODE;

    iRet = SendRSA( & strLanHeader, & uiMode, strLanHeader.uiLength );

    // 클라이언트 랜 소켓 닫는다.
    m_theTcpSocket.close();

    EnableControl( false );
}

/**
 * @brief MainWindow::on_AnalStart_clicked
 */
void MainWindow::on_AnalStart_clicked()
{
    STR_LAN_HEADER strLanHeader;
    time_t tiNow;

    strLanHeader.uiOpCode = enREQ_ANAL_START;
    strLanHeader.uiLength = sizeof( time_t );

    tiNow = time(NULL);

    SendRSA( & strLanHeader, & tiNow, strLanHeader.uiLength );
}

/**
 * @brief MainWindow::on_MODE_clicked
 */
void MainWindow::on_MODE_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;
    UINT uiMode;

    ui->MODE->setEnabled( false );

    strLanHeader.uiOpCode = enREQ_MODE;
    strLanHeader.uiLength = sizeof( int );

    if( ui->radioButton_ESMode->isChecked() ) {
        uiMode = enES_MODE;
    }
    if( ui->radioButton_EWMode->isChecked() ) {
        uiMode = enEW_MODE;
    }
    if( ui->radioButton_ReadyMode->isChecked() ) {
        uiMode = enREADY_MODE;
    }

    iRet = SendRSA( & strLanHeader, & uiMode, strLanHeader.uiLength );

}

/**
 * @brief MainWindow::MessageBox
 * @param pText
 */
void MainWindow::MessageBox( char *pText )
{
    QMessageBox::information( this, "파일 로딩", pText );

}

/**
 * @brief MainWindow::on_BITTEST_clicked
 */
void MainWindow::on_BITTEST_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;

    ui->BITTEST->setEnabled( false );

    strLanHeader.uiLength = 0;

    if( ui->radioButton_IBIT->isChecked() ) {
        strLanHeader.uiOpCode = enREQ_IBIT;
    }
    else if( ui->radioButton_URBIT->isChecked() ) {
        strLanHeader.uiOpCode = enREQ_UBIT;
    }
    else if( ui->radioButton_SYSTEM->isChecked() ) {
        strLanHeader.uiOpCode = enREQ_SBIT;
    }
    else {
        strLanHeader.uiOpCode = enREQ_CBIT;
    }

    iRet = SendRSA( & strLanHeader, NULL, strLanHeader.uiLength );

}

/**
 * @brief MainWindow::on_pushButton_SimPDW_clicked
 */
void MainWindow::on_pushButton_SimPDW_clicked()
{
    int iRet;

    CFile theRawDataFile;
    STR_LAN_HEADER strLanHeader;

    UINT uiFilelength;
    char *pRawDataBuffer;

    ui->BITTEST->setEnabled( false );

    strLanHeader.uiOpCode = enREQ_SIM_PDWDATA;

    QString fileName = QFileDialog::getOpenFileName( this, QString::fromLocal8Bit("파일 선택"), "~/", "PDW 파일(*.kpdw)" );

    if (theRawDataFile.Open( fileName.toStdString().c_str(), O_RDONLY ) == TRUE) {
        uiFilelength = theRawDataFile.GetFileLength();
        strLanHeader.uiLength = uiFilelength;

        pRawDataBuffer = ( char * ) malloc( sizeof(char) * uiFilelength );

        if( pRawDataBuffer != NULL ) {
            theRawDataFile.Read( pRawDataBuffer, MAX_RAWDATA_SIZE );

            iRet = SendRSA( & strLanHeader, pRawDataBuffer, strLanHeader.uiLength );

            free( pRawDataBuffer );
            theRawDataFile.Close();

        }
        else {

        }
    }
    else {
        MessageBox( "모의 발생할 파일이 존재하지 않습니다.!" );
    }

}

/**
 * @brief MainWindow::on_pushButton_2_clicked
 */
void MainWindow::on_pushButton_2_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;

    strLanHeader.uiOpCode = enREQ_TEST1;
    strLanHeader.uiLength = 0;

    iRet = SendRSA( & strLanHeader, NULL, strLanHeader.uiLength );
}

/**
 * @brief MainWindow::on_pushButton_ReloadLibrary_clicked
 */
void MainWindow::on_pushButton_ReloadLibrary_clicked()
{
    int iRet;

    STR_LAN_HEADER strLanHeader;

    strLanHeader.uiOpCode = enREQ_RELOAD_LIBRARY;
    strLanHeader.uiLength = 0;

    iRet = SendRSA( & strLanHeader, NULL, strLanHeader.uiLength );

}
