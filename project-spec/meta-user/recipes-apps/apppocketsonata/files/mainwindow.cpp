#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include <QMessageBox>
#include <QFileDialog>

#include "ui_mainwindow.h"
#include "mainwindow.h"


#include "./Include/defines.h"
#include "./Include/sysmsg.h"

#include <fcntl.h>

enum enTableHeader {
    enNoAET=0,
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

char szTableHeader[enMax][30] = { "#", "최초접촉", "최근접촉", "위협도", "ELNOT", "신호형태", "방위[도]", "주파수[MHz]", "PRI[us]", "펄스폭[ns]", "신호세기[dBm]", "스캔", "에미터명", "위협명", "식별" } ;

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

    // 스픽 박스 설정
    ui->spinBox_fmopthreshold->setMinimum( 0 );
    ui->spinBox_fmopthreshold->setMaximum( 255 );
    ui->spinBox_fmopthreshold->setValue( 55 );

    ui->spinBox_pmopthreshold->setMinimum( 0 );
    ui->spinBox_pmopthreshold->setMaximum( 255 );
    ui->spinBox_pmopthreshold->setValue( 155 );

    ui->spinBox_rxthreshold->setMinimum( 0 );
    ui->spinBox_rxthreshold->setMaximum( 65536 );
    ui->spinBox_rxthreshold->setValue( 9000 );

    ui->spinBox_rxthreshold->setMinimum( 0 );
    ui->spinBox_rxthreshold->setMaximum( 65536 );
    ui->spinBox_rxthreshold->setValue( 85 );

    ui->spinBox_corrthreshold->setMinimum( 0 );
    ui->spinBox_corrthreshold->setMaximum( 65536 );
    ui->spinBox_corrthreshold->setValue( 2065 );


    m_ptheTcpServer = new QTcpServer(this);
    if( ! m_ptheTcpServer->listen( QHostAddress::Any, 13030 ) ) {
        perror( "서버" );
    }

    connect( m_ptheTcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    //connect( & m_theTcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()) );
    //connect( m_ptheTcpServer, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    //connect( & m_theTcpSocket, SIGNAL(readyRead()), this, SLOT(onReadMessage()));
    //connect( & m_theTcpSocket, SIGNAL(error()), this, SLOT(onError()));

    QStringList aettableHeader;

    for( i=0 ; i < enMax ; ++i ) {
        aettableHeader << szTableHeader[i];
    }

    ui->aettableWidget->setColumnCount( enMax );
    ui->aettableWidget->setHorizontalHeaderLabels( aettableHeader );

    ui->aettableWidget->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color:#404040;color:#FFFFFF;}" );
    ui->aettableWidget->setAlternatingRowColors( true );

    ui->progressBar_IPL->setValue( 0 );

    _InitResolution();

}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    disConnected();

    delete ui;
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

    disConnected();

}

/**
 * @brief MainWindow::newConnection
 */
void MainWindow::newConnection()
{
    printf( "***클라이언트와 연결이 되었습니다.\n" );

    ui->pushButton->setText( tr("연결 해지") );
    m_bConnect = true;

    m_bHeader = true;
    m_uiTotalRead = 0;

    EnableControl( true );

    ui->progressBar_IPL->setValue( 0 );
    ui->progressBar_IPL_WriteStatus->setValue( 0 );

    // 수집된 센서 데이터 송신
    m_ptheClient = m_ptheTcpServer->nextPendingConnection();

    connect( m_ptheClient,SIGNAL(readyRead()),this,SLOT(readData()));
    connect( m_ptheClient,SIGNAL(disconnected()),this,SLOT(disConnected()));
    disconnect( m_ptheTcpServer, SIGNAL(newConnection()),this,SLOT(newConnection()));

}

void MainWindow::readData()
{
    //if(m_ptheClient->bytesAvailable() >= 0 )
    //{
    //    QByteArray data = client->readAll();
    //}

    int iRead;

    //UINT uiTotalRead=0;
    char *pLanData;

    QTextCharFormat format;

    pLanData = (char *) & m_szLanData[m_uiTotalRead];

    while( true ) {
         //nextBlcokSize 가 0 이면 아직 데이터를 못받은것
        if( m_bHeader == true ) {
            printf( "*read header" );
            if (( iRead = m_ptheClient->read( & m_szLanData[m_uiTotalRead], sizeof(STR_LAN_HEADER) ) ) == 0 ) {
                printf( "rd[%d]\n" , iRead );
                break;
                // m_theTcpSocket.disconnectFromHost();
                //CloseSocket( iSocket, & address, & iClientSocket[i] );
            }
            else {
                printf( "rd[%d]\n" , iRead );
                m_uiTotalRead += iRead;
                if( m_uiTotalRead == sizeof(STR_LAN_HEADER) ) {
                    AllSwapData32( & m_szLanData[0], sizeof(STR_LAN_HEADER) );
                    m_bHeader = false;
                }
                else {
                    iRead = 0;
                }
            }
        }
        else {
            STR_LAN_HEADER *pLanHeader;

            pLanHeader = ( STR_LAN_HEADER * ) & m_szLanData[0];
            printf( "*read data [%d]" , pLanHeader->uiLength );
            if (( iRead = m_ptheClient->read( & m_szLanData[m_uiTotalRead], pLanHeader->uiLength ) ) == 0 ) {
                printf( "rd[%d]\n" , iRead );
                break;
            }
            else {
                printf( "rd[%d]\n" , iRead );
                m_uiTotalRead += iRead;
                if( m_uiTotalRead-sizeof(STR_LAN_HEADER) >= pLanHeader->uiLength ) {
                    AllSwapData32( & m_szLanData[sizeof(STR_LAN_HEADER)], pLanHeader->uiLength );

                    m_bHeader = true;
                    m_uiTotalRead = 0;

                    //데이터를 표시
                    ParseAndDisplay( pLanHeader, & m_szLanData[sizeof(STR_LAN_HEADER)] );

                    format.setForeground(QColor(0x6F,0x77,0x97));
                    QTextCursor cursor = ui->memoryDump->textCursor();
                    cursor.select(QTextCursor::Document);
                    cursor.mergeCharFormat(format);

                    memset( pLanHeader, 0, sizeof(STR_LAN_HEADER)+pLanHeader->uiLength );
                }
                else {
                    iRead = 0;
                }
            }
        }

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
 * @brief MainWindow::disConnected
 */
void MainWindow::disConnected()
{
    printf( "***클라이언트와 연결 해지 되었습니다.\n" );

    if( m_ptheClient != NULL ) {
        m_ptheClient->close();
    }

    ui->pushButton->setText( tr("연결") );
    m_bConnect = false;

    m_bHeader = true;

    EnableControl( false );

    if( ! m_ptheTcpServer->listen( QHostAddress::Any, 13030 ) ) {
        perror( "서버" );
    }

    // 수집된 센서 데이터 송신
    connect(m_ptheTcpServer,SIGNAL(newConnection()),this,SLOT(newConnection()));

    ClearTable();

} // 소켓 연결 해제

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
    ui->pushButton_IPLVersion->setEnabled( bEnable );
    ui->pushButton_DownloadIPL->setEnabled( bEnable );
    ui->pushButton_SimPDW->setEnabled( bEnable );

    ui->pushButton_audio->setEnabled( bEnable );
    ui->pushButton_audiosetup->setEnabled( bEnable );

    ui->pushButton_bandenable->setEnabled( bEnable );
    ui->pushButton_fmopthreshold->setEnabled( bEnable );
    ui->pushButton_pmopthreshold->setEnabled( bEnable );
    ui->pushButton_rx->setEnabled( bEnable );

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
            //if (( iRead = m_theTcpServer.read( & pLanData[uiTotalRead], sizeof(STR_LAN_HEADER)-uiTotalRead ) ) == 0 ) {
            //    break;
                // m_theTcpSocket.disconnectFromHost();
                //CloseSocket( iSocket, & address, & iClientSocket[i] );
            //}
            //else {
                uiTotalRead += iRead;
                if( uiTotalRead == sizeof(STR_LAN_HEADER) ) {
                    m_bHeader = false;
                    uiTotalRead = 0;
                }
            //}
        }
        else {
            pLanData = (char *) & szLanData;

            //if (( iRead = m_theTcpSocket.read( & pLanData[uiTotalRead], strLanHeader.uiLength-uiTotalRead ) ) == 0 ) {
            //    break;
                //m_theTcpSocket.disconnectFromHost();
            //}
            //else
            {
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
                m_ptheTcpServer->close();
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

    //////////////////////////////////////////////////////////////////////////////////////////////

    case esIPL_VERSION :
        ShowIPLVersion( pByteData );
        break;

    case esIPL_WRITESTATUS :
        ShowIPLWriteStatus( pByteData );
        break;

    //////////////////////////////////////////////////////////////////////////////////////////////
    case esAET_NEW_CCU :
        InsertAETTable( pByteData );
        break;

    case esAET_UPD_CCU :
        UpdateAETTable( pByteData );
        break;

    case esAET_LST_CCU :
        LostAETTable( pByteData );
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
    int iIndexOfTable;

    pAET = ( STR_AET *) pByteData;

    ui->aettableWidget->insertRow( ui->aettableWidget->rowCount() );

    iIndexOfTable = ui->aettableWidget->rowCount() - 1;

    UpdateRow( ui->aettableWidget, pAET, iIndexOfTable );

    UpdateColor( iIndexOfTable, pAET, Maet_New_Ccu );

}

/**
 * @brief MainWindow::UpdateRow
 * @param pQTableWidget
 * @param pAET
 * @param iIndexOfTable
 */
void MainWindow::UpdateRow( QTableWidget *pQTableWidget, STR_AET *pAET, int iIndexOfTable )
{
    QString qTemp;

    struct tm *pTm;

    time_t time64;

    qTemp.sprintf( (char *) "%d", pAET->noEMT );
    pQTableWidget->setItem( iIndexOfTable, enNoAET, new QTableWidgetItem(qTemp) );
    qTemp.sprintf( "%s", aet_signal_type[pAET->sigType] );
    pQTableWidget->setItem( iIndexOfTable, enSIGTYPE, new QTableWidgetItem(qTemp) );
    qTemp.sprintf( "%.1f", SONATA::DECODE::DOA( pAET->aoa ) );
    pQTableWidget->setItem( iIndexOfTable, enAOA, new QTableWidgetItem(qTemp) );
    if( pAET->frq.type == _PATTERN_AGILE ) {
        qTemp.sprintf( "%s(%.1f) %7.2f(%.1f,%.1f)", aet_freq_type[pAET->frq.type], SONATA::DECODE::TOA(pAET->frq.patPrd), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.mean ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.min ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.max ) );
    }
    else {
        qTemp.sprintf( "%s %-7.2f(%.2f,%.2f)", aet_freq_type[pAET->frq.type], SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.mean ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.min ), SONATA::DECODE::FREQ( pAET->frq.band, pAET->frq.max ) );
    }
    pQTableWidget->setItem( iIndexOfTable, enFREQ, new QTableWidgetItem(qTemp) );

    if( pAET->pri.type == _JITTER_PATTERN ) {
        qTemp.sprintf( "%s(%.1f) %7.2f(%.1f,%.1f)", aet_pri_type[pAET->pri.type], SONATA::DECODE::TOA(pAET->pri.patPrd), SONATA::DECODE::TOA( pAET->pri.mean ), SONATA::DECODE::TOA(pAET->pri.min), SONATA::DECODE::TOA(pAET->pri.max) );
    }
    else {
        qTemp.sprintf( "%s %-7.2f(%.2f,%.2f)", aet_pri_type[pAET->pri.type], SONATA::DECODE::TOA( pAET->pri.mean ), SONATA::DECODE::TOA( pAET->pri.min ), SONATA::DECODE::TOA( pAET->pri.max ) );
    }
    pQTableWidget->setItem( iIndexOfTable, enPRI, new QTableWidgetItem(qTemp) );

    qTemp.sprintf( "%7.0f(%.0f,%.0f)", SONATA::DECODE::PW( pAET->pw.mean ), SONATA::DECODE::PW(pAET->pw.min), SONATA::DECODE::PW(pAET->pw.max) );
    pQTableWidget->setItem( iIndexOfTable, enPW, new QTableWidgetItem(qTemp) );

    qTemp.sprintf( "%7.1f(%.1f,%.1f)", SONATA::DECODE::PA( pAET->pa.mean ), SONATA::DECODE::PA(pAET->pa.min), SONATA::DECODE::PA(pAET->pa.max) );
    pQTableWidget->setItem( iIndexOfTable, enPA, new QTableWidgetItem(qTemp) );

    if( pAET->as.type == CONICAL ) {
        qTemp.sprintf( "%s %s%7.1f", aet_asp_stat_ch[pAET->as.stat], aet_asp_type_ch[pAET->as.type], SONATA::DECODE::TOA(pAET->as.prd) );
    }
    else {
        qTemp.sprintf( "%s %s%7.1f", aet_asp_stat_ch[pAET->as.stat], aet_asp_type_ch[pAET->as.type], SONATA::DECODE::TOA(pAET->as.prd) );
    }
    pQTableWidget->setItem( iIndexOfTable, enSCAN, new QTableWidgetItem(qTemp) );

    time64 = (time_t) pAET->seen.frst;
    pTm = localtime( & time64 );
    qTemp.sprintf( "%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
    pQTableWidget->setItem( iIndexOfTable, enFirstSeen, new QTableWidgetItem(qTemp) );

    time64 = (time_t) pAET->seen.last;
    pTm = localtime( & time64 );
    qTemp.sprintf( "%02d:%02d:%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec );
    pQTableWidget->setItem( iIndexOfTable, enLastSeen, new QTableWidgetItem(qTemp) );

    qTemp.sprintf( "%d", pAET->priLev );
    pQTableWidget->setItem( iIndexOfTable, enPriority, new QTableWidgetItem(qTemp) );

    if( pAET->id.coAmbi != 0 ) {
        qTemp.sprintf( "%s", pAET->elintNotation );
        pQTableWidget->setItem( iIndexOfTable, enELNOT, new QTableWidgetItem(qTemp) );

        qTemp.sprintf( "%s", pAET->emitterName );
        pQTableWidget->setItem( iIndexOfTable, enEMITTER, new QTableWidgetItem(qTemp) );

        qTemp.sprintf( "%s", pAET->threatName );
        pQTableWidget->setItem( iIndexOfTable, enTHREAT, new QTableWidgetItem(qTemp) );

        qTemp.sprintf( "%d(%d,%d,%d)", pAET->id.coAmbi, pAET->id.noIPL[0], pAET->id.noIPL[1], pAET->id.noIPL[2] );
        pQTableWidget->setItem( iIndexOfTable, enID, new QTableWidgetItem(qTemp) );
    }
    else {

    }

    pQTableWidget->resizeColumnsToContents();
}

/**
 * @brief MainWindow::GetIndexOfAETTable
 * @param uiAETID
 * @return
 */
int MainWindow::GetIndexOfAETTable( unsigned int uiAETID )
{
    int i, iTotalRowCount = ui->aettableWidget->rowCount();

    QString qStrNoAET;

    qStrNoAET.sprintf( "%d", uiAETID );
    for( i=0 ; i < iTotalRowCount ; ++i ) {
        QString qString;

        qString = ui->aettableWidget->item(i, enNoAET )->text();

        if( qString == qStrNoAET ) {
            break;
        }

    }

    return i;

}

/**
 * @brief MainWindow::UpdateTable
 * @param pByteData
 */
void MainWindow::UpdateAETTable( void *pByteData )
{
    int iIndexOfTable;
    STR_AET *pAET;

    pAET = ( STR_AET *) pByteData;

    iIndexOfTable = GetIndexOfAETTable( pAET->noEMT );

    UpdateRow( ui->aettableWidget, pAET, iIndexOfTable );

    UpdateColor( iIndexOfTable, pAET, Maet_Update_Ccu );

}

/**
 * @brief MainWindow::UpdateColor
 * @param iIndex
 * @param pAET
 */
void MainWindow::UpdateColor( int iIndex, STR_AET *pAET, unsigned int opCode )
{
    // 위협도
    if( pAET->priLev >= 6 ) {
        ui->aettableWidget->item( iIndex, 0 )->setBackgroundColor( Qt::red );
    }

    if( opCode == esAET_NEW_CCU ) {
        ui->aettableWidget->item( iIndex, 0 )->setBackgroundColor( Qt::white );
    }
    else if( opCode == esAET_LST_CCU ) {
        ui->aettableWidget->item( iIndex, 0 )->setBackgroundColor( Qt::yellow );
    }
    else {
        ui->aettableWidget->item( iIndex, 0 )->setBackgroundColor( qRgb(255,0,0) );
    }

}

/**
 * @brief MainWindow::LostAETTable
 * @param pByteData
 */
void MainWindow::LostAETTable( void *pByteData )
{
    int iIndexOfTable;
    STR_AET *pAET;

    pAET = ( STR_AET *) pByteData;

    iIndexOfTable = GetIndexOfAETTable( pAET->noEMT );

    UpdateColor( iIndexOfTable, pAET, Maet_Lost_Ccu );

}

/**
 * @brief MainWindow::DeleteTable
 * @param pByteData
 */
void MainWindow::DeleteAETTable( void *pByteData )
{
    int iIndexOfTable;
    STR_AET *pAET;

    pAET = ( STR_AET *) pByteData;

    iIndexOfTable = GetIndexOfAETTable( pAET->noEMT );
    ui->aettableWidget->removeRow( iIndexOfTable );
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

/**
 * @brief MainWindow::ShowCBitResult
 * @param pData
 */
void MainWindow::ShowCBitResult( void *pData )
{
    STR_ES_CBIT *pESCBit;
    QString qBitResult;

    pESCBit = ( STR_ES_CBIT * ) pData;
    qBitResult.sprintf( "0x%x/0x%x/0x%x, 0x%x", pESCBit->sp[0].w32, pESCBit->sp[1].w32, pESCBit->sp[2].w32, pESCBit->rsa.w32 );
    ui->bit_result->setText( qBitResult );

}

/**
 * @brief MainWindow::ShowIPLVersion
 * @param pData
 */
void MainWindow::ShowIPLVersion( void *pData )
{
    STR_IPL_VERSION *pIPLVersion;
    QString qStrTitle;

    pIPLVersion = ( STR_IPL_VERSION * ) pData;
    qStrTitle.sprintf( "PocketSonata - IPL[%0X]" , pIPLVersion->uiIPLVersion );
    setWindowTitle( qStrTitle );

}

/**
 * @brief MainWindow::ShowIPLWriteStatus
 * @param pData
 */
void MainWindow::ShowIPLWriteStatus( void *pData )
{
    unsigned int *puiWriteStatus;

    puiWriteStatus = ( unsigned int * ) pData;
    printf( "WriteStatus[%d]\n" , *puiWriteStatus );
    ui->progressBar_IPL_WriteStatus->setValue( *puiWriteStatus );
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
    int iRet=-1;

    AllSwapData32( (char *) pstrLanHeader, sizeof(STR_LAN_HEADER) );
    if( m_ptheClient != NULL ) {
        iRet = m_ptheClient->write( (char *) pstrLanHeader, sizeof(STR_LAN_HEADER) );

        if( pData != NULL && iRet > 0 ) {
            AllSwapData32( (char *) pData, iLength );
            iRet = m_ptheClient->write( (char *) pData, iLength );
        }
        else {
            //LOGMSG( enWarning, )
        }
    }

    return iRet;

}

/**
 * @brief MainWindow::AllSwapData32
 * @param pData
 * @param iLength
 */
void MainWindow::AllSwapData32( void *pData, int iLength )
{
    int i;
    UINT *pWord;

    printf( " AllSwapData32 : %d\n" , iLength );

    pWord = (UINT *) pData;
    for( i=0 ; i < iLength ; i+=sizeof(int) ) {
        swapByteOrder( *pWord );
        ++ pWord;
    }

}

/**
 * @brief MainWindow::swapByteOrder
 * @param ui
 */
void MainWindow::swapByteOrder(unsigned int& ui)
{
    ui = (ui >> 24) |
        ((ui<<8) & 0x00FF0000) |
        ((ui>>8) & 0x0000FF00) |
        (ui << 24);
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
    m_ptheTcpServer->close();

    ui->pushButton->setText( tr("연결") );
    m_bConnect = false;

    m_bHeader = true;

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

    QString fileName = QFileDialog::getOpenFileName( this, QString::fromLocal8Bit("파일 선택"), "~/", "PDW 파일(*.zpdw)" );

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
        MessageBox( (char *) "모의 발생할 파일이 존재하지 않습니다.!" );
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

/**
 * @brief MainWindow::on_pushButton_IPLVersion_clicked
 */
void MainWindow::on_pushButton_IPLVersion_clicked()
{
    int iRet;
    QString qStrTitle;

    STR_LAN_HEADER strLanHeader;

    qStrTitle.sprintf( "PocketSonata - IPL" );
    setWindowTitle( qStrTitle );

    strLanHeader.uiOpCode = enREQ_IPL_VERSION;
    strLanHeader.uiLength = 0;

    iRet = SendRSA( & strLanHeader, NULL, strLanHeader.uiLength );
}

/**
 * @brief MainWindow::on_pushButton_DownloadIPL_clicked
 */
void MainWindow::on_pushButton_DownloadIPL_clicked()
{
    int i, iRet;

    time_t timer;
    struct tm* t;

    STR_LAN_HEADER strLanHeader;
    STR_IPL_START strIPLStart;

    ui->progressBar_IPL->setValue( 0 );
    ui->progressBar_IPL_WriteStatus->setValue( 0 );

    timer = time( NULL );
    t = localtime(&timer);

    ReadIPLFIle();

    strLanHeader.uiOpCode = enREQ_IPL_START;
    strLanHeader.uiLength = sizeof(STR_IPL_START);
    strIPLStart.uiCountOfIPL = m_coLoadIPL;
    strIPLStart.uiIPLVersion = ( ( t->tm_year - 100 ) << 16 ) | ( ( t->tm_mon + 1 ) << 8 ) | t->tm_mday;;

    iRet = SendRSA( & strLanHeader, & strIPLStart, strLanHeader.uiLength );

    if( iRet == sizeof(STR_IPL_START) ) {
        for( i=1 ; i <= m_coLoadIPL ; ++i ) {
            strLanHeader.uiOpCode = enREQ_IPL_DOWNLOAD;
            strLanHeader.uiLength = sizeof( STR_IPL );
            iRet = SendRSA( & strLanHeader, & m_strIpl[i], sizeof( STR_IPL ) );

            if( iRet == sizeof( STR_IPL ) ) {
                ui->progressBar_IPL->setValue( (int) ( 0.5 + (float) ( ( (float) i * 100. ) / (float) m_coLoadIPL ) ) );
            }

            usleep( 100000 );
        }
    }

    strLanHeader.uiOpCode = enREQ_IPL_END;
    strLanHeader.uiLength = 0;
    SendRSA( & strLanHeader, NULL, strLanHeader.uiLength );

}

/**
 * @brief MainWindow::ReadIPLFIle
 */
void MainWindow::ReadIPLFIle()
{
    FILE *iplfile;

    STR_IPL *ptmp;

    UINT i;

    char da[1500];
    char str[100];

    iplfile = fopen( "ipl.txt" , "rt" );          /* open the IPL file    */
    if( iplfile != NULL ) {
        fgets( da, 1500, iplfile );                  /* skip the header of IPL   */
        fgets( da, 1500, iplfile );

        ptmp = & m_strIpl[1];
        m_coLoadIPL = 0;

        while( ! feof( iplfile ) ) {
            /* Signal Type	*/
            fscanf( iplfile, "%d", &ptmp->sigType );	// dummy ipl #

            fscanf( iplfile, "%d", &ptmp->sigType );

            if( feof( iplfile ) ) {
                break;
            }

            ptmp->noIPL = m_coLoadIPL + 1;

            /* Frequency   */
            fscanf( iplfile, "%d", &ptmp->frq.type );
            fscanf( iplfile, "%s", str );
            ptmp->frq.low = ( UINT ) ( ( double ) atof( str ) );
            fscanf( iplfile, "%s", str );
            ptmp->frq.hgh = ( UINT ) ( ( double ) atof( str ) );
            fscanf( iplfile, "%s", str );
            ptmp->frq.bw = ( UINT ) ( ( double ) atof( str ) );

            fscanf( iplfile, "%d", &ptmp->frq.patType );			// Pattern Type
            fscanf( iplfile, "%d", &ptmp->frq.swtLev );			// Pattern Type
            for( i=0 ; i < _spMaxSwtLev ; ++i ) {
                fscanf( iplfile, "%s", str );
                ptmp->frq.swtValLow[i] = ( UINT ) ( ( double ) atof( str ) );
                fscanf( iplfile, "%s", str );
                ptmp->frq.swtValHgh[i] = ( UINT ) ( ( double ) atof( str ) );
            }

            fscanf( iplfile, "%s", str );
            ptmp->frq.ppLow = ( UINT ) ( ( double ) atof( str ) );
            fscanf( iplfile, "%s", str );
            ptmp->frq.ppHgh = ( UINT ) ( ( double ) atof( str ) );

            /*  PRI  */
            fscanf( iplfile, "%d", &ptmp->pri.type );
            fscanf( iplfile, "%s", str );
            ptmp->pri.low = ( UINT ) ( ( double ) atof( str ) );
            fscanf( iplfile, "%s", str );
            ptmp->pri.hgh = ( UINT ) ( ( double ) atof( str ) );
            fscanf( iplfile, "%d", &ptmp->pri.patType );
            fscanf( iplfile, "%d", &ptmp->pri.jtrPer );
            fscanf( iplfile, "%d", &ptmp->pri.swtLev );
            for( i=0 ; i < _spMaxSwtLev ; ++i )  {
                fscanf( iplfile, "%s", str );
                ptmp->pri.swtValLow[i] = ( UINT ) ( ( double ) atof( str ) );
                fscanf( iplfile, "%s", str );
                ptmp->pri.swtValHgh[i] = ( UINT ) ( ( double ) atof( str ) );
            }
            fscanf( iplfile, "%d", &ptmp->pri.ppLow );
            fscanf( iplfile, "%d", &ptmp->pri.ppHgh );

            /*	Pulsewidth	*/
            fscanf( iplfile, "%s", str );
            ptmp->pw.low = ( UINT ) ( ( double ) atof( str ) );
            fscanf( iplfile, "%s", str );
            ptmp->pw.hgh = ( UINT ) ( ( double ) atof( str ) );

            /*  Antenna Scan Period */
            fscanf( iplfile, "%d", &ptmp->as.type );
            fscanf( iplfile, "%s", str );
            ptmp->as.prdLow = ( UINT ) ( ( double ) atof( str ) );
            fscanf( iplfile, "%s", str );
            ptmp->as.prdHgh = ( UINT ) ( ( double ) atof( str ) );

            /* Delete Time		*/
            fscanf( iplfile, "%d", &ptmp->tmoDel );

            /* Threat Level */
            fscanf( iplfile, "%d", &ptmp->thrLev );

            /* AutoWarning */
            fscanf( iplfile, "%d", &ptmp->autoWarn );

            /* Elint Notation */
            fscanf( iplfile, "%s", ptmp->elintNot );

            /* Elint Name */
            fscanf( iplfile, "%s", ptmp->elintName );

            /* Category */
            fscanf( iplfile, "%d", &ptmp->cat );

            /* Threat ERP */
            fscanf( iplfile, "%d", &ptmp->thrERP );

            /* Platform name */
            fscanf( iplfile, "%d", &ptmp->platform[0].noplat );
            fscanf( iplfile, "%s", ptmp->platform[0].platName );

            fscanf( iplfile, "%d", &ptmp->platform[1].noplat );
            fscanf( iplfile, "%s", ptmp->platform[1].platName );

            fscanf( iplfile, "%d", &ptmp->platform[2].noplat );
            fscanf( iplfile, "%s", ptmp->platform[2].platName );

            fscanf( iplfile, "%d", &ptmp->platform[3].noplat );
            fscanf( iplfile, "%s", ptmp->platform[3].platName );

            fscanf( iplfile, "%d", &ptmp->platform[4].noplat );
            fscanf( iplfile, "%s", ptmp->platform[4].platName );

#ifdef ID_DEBUG
          fprintf( stderr, "#" );
#endif

//          DISP_FineIPL( ptmp );
            ++ m_coLoadIPL;
            ++ ptmp;

        }

        fclose( iplfile );

    }

}

/**
 * @brief MainWindow::on_pushButton_audio_clicked
 */
void MainWindow::on_pushButton_audio_clicked()
{
    UINT uiSwitch;
    QString qText;

    STR_LAN_HEADER strLanHeader;

    qText = ui->pushButton_audio->text();

    if( qText.compare( "ON" ) == 0 ) {
        ui->pushButton_audio->setText( tr("OFF") );

        strLanHeader.uiOpCode = enREQ_AUDIO;
        strLanHeader.uiLength = sizeof( int );

        uiSwitch = _spFalse;

    }
    else {
        ui->pushButton_audio->setText( tr("ON") );

        strLanHeader.uiOpCode = enREQ_AUDIO;
        strLanHeader.uiLength = sizeof( int );

        uiSwitch = _spTrue;

    }

    SendRSA( & strLanHeader, & uiSwitch, sizeof( int ) );

}

/**
 * @brief MainWindow::on_pushButton_audiosetup_clicked
 */
void MainWindow::on_pushButton_audiosetup_clicked()
{
    STR_LAN_HEADER strLanHeader;
    STR_AUDIO_PARAM strAudioParam;

    strLanHeader.uiOpCode = enREQ_AUDIO_PARAM;
    strLanHeader.uiLength = sizeof( STR_AUDIO_PARAM );

    strAudioParam.iLowerBC = 0;
    strAudioParam.iUpperBC = 0;
    strAudioParam.iLowerFrq = 500;
    strAudioParam.iUpperFrq = 18000;
    strAudioParam.iFromAoa = 0;
    strAudioParam.iToAoa = 360;
    strAudioParam.iFromPa = 0;
    strAudioParam.iToPa = 18000;

    SendRSA( & strLanHeader, & strAudioParam, sizeof( STR_AUDIO_PARAM ) );

}

int MainWindow::GetUIBand()
{
    int iRet=0;

    if( ui->checkBox_band1->checkState() == Qt::CheckState::Checked ) {
        iRet |= 0x1;
    }
    if( ui->checkBox_band2->checkState() == Qt::CheckState::Checked ) {
        iRet |= 0x2;
    }
    if( ui->checkBox_band3->checkState() == Qt::CheckState::Checked ) {
        iRet |= 0x4;
    }
    if( ui->checkBox_band4->checkState() == Qt::CheckState::Checked ) {
        iRet |= 0x8;
    }
    if( ui->checkBox_band5->checkState() == Qt::CheckState::Checked ) {
        iRet |= 0x10;
    }

    return iRet;
}

/**
 * @brief MainWindow::on_pushButton_bandenable_clicked
 */
void MainWindow::on_pushButton_bandenable_clicked()
{
    QString qText;
    STR_LAN_HEADER strLanHeader;
    STR_BAND_ENABLE strBandEnable;

    strLanHeader.uiOpCode = enREQ_Band_Enable;
    strLanHeader.uiLength = sizeof( STR_BAND_ENABLE );

    strBandEnable.iBand = GetUIBand();

    qText = ui->pushButton_bandenable->text();
    if( qText.compare( "대역 설정 ON" ) == 0 ) {
        ui->pushButton_bandenable->setText( tr("대역 설정 OFF") );

        strBandEnable.iOnOff = 0;

    }
    else {
        ui->pushButton_bandenable->setText( tr("대역 설정 ON") );

        strBandEnable.iOnOff = 0xff;
    }

    SendRSA( & strLanHeader, & strBandEnable, sizeof( STR_BAND_ENABLE ) );

}

/**
 * @brief MainWindow::on_pushButton_fmopthreshold_clicked
 */
void MainWindow::on_pushButton_fmopthreshold_clicked()
{
    QString qText;
    STR_LAN_HEADER strLanHeader;
    STR_FMOP_THRESHOLD strFMOPThreshold;

    strLanHeader.uiOpCode = enREQ_FMOP_Threshold;
    strLanHeader.uiLength = sizeof( STR_FMOP_THRESHOLD );

    strFMOPThreshold.iBand = GetUIBand();

    strFMOPThreshold.iThreshold = ui->spinBox_fmopthreshold->value();

    qText = ui->pushButton_bandenable->text();

    SendRSA( & strLanHeader, & strFMOPThreshold, sizeof( STR_FMOP_THRESHOLD ) );
}

/**
 * @brief MainWindow::on_pushButton_pmopthreshold_clicked
 */
void MainWindow::on_pushButton_pmopthreshold_clicked()
{
    QString qText;
    STR_LAN_HEADER strLanHeader;
    STR_PMOP_THRESHOLD strPMOPThreshold;

    strLanHeader.uiOpCode = enREQ_PMOP_Threshold;
    strLanHeader.uiLength = sizeof( STR_PMOP_THRESHOLD );

    strPMOPThreshold.iBand = GetUIBand();

    strPMOPThreshold.iThreshold = ui->spinBox_pmopthreshold->value();

    qText = ui->pushButton_bandenable->text();

    SendRSA( & strLanHeader, & strPMOPThreshold, sizeof( STR_PMOP_THRESHOLD ) );
}

/**
 * @brief MainWindow::on_pushButton_rx_clicked
 */
void MainWindow::on_pushButton_rx_clicked()
{
    QString qText;
    STR_LAN_HEADER strLanHeader;
    STR_RX_THRESHOLD strRXThreshold;

    strLanHeader.uiOpCode = enREQ_RX_Threshold;
    strLanHeader.uiLength = sizeof( STR_RX_THRESHOLD );

    strRXThreshold.iBand = GetUIBand();

    strRXThreshold.uiMagThreshold = ui->spinBox_rxthreshold->value();

    qText = ui->pushButton_bandenable->text();

    SendRSA( & strLanHeader, & strRXThreshold, sizeof( STR_RX_THRESHOLD ) );
}

void MainWindow::ClearTable()
{
    int i, iCount;

    iCount = ui->aettableWidget->rowCount();

    for( i=iCount ; i >= 0 ; --i ) {
        ui->aettableWidget->removeRow( i );
    }
}
