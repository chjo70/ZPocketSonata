#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./Include/defines.h"
#include "./Include/sysmsg.h"






/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxStartAddress->setRange(UINT_MAX);
    ui->spinBoxStartAddress->setPrefix("0x");

    connect( & m_theTcpSocket, SIGNAL(connected()), this, SLOT(onConnectServer()) );
    connect( & m_theTcpSocket, SIGNAL(disconnected()), this, SLOT(connectionClosedByServer()));
    connect( & m_theTcpSocket, SIGNAL(readyRead()), this, SLOT(onReadMessage()));


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

void MainWindow::onReadyRead()
{
}

/**
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{
    nextBlockSize = 0;

    if( m_bConnect == false ) {
        m_theTcpSocket.connectToHost(QHostAddress::LocalHost, CCU_PORT );

    }
    else {
        m_theTcpSocket.close();

        EnableControl( false );
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

void MainWindow::EnableControl( bool bEnable )
{
    ui->MemoryDump->setEnabled( bEnable );
    //ui->ESMode->setEnabled( bEnable );
    //ui->EWMode->setEnabled( bEnable );
    ui->MODE->setEnabled( bEnable );
    ui->AnalStart->setEnabled( bEnable );

}

/**
 * @brief MainWindow::connectionClosedByServer
 */
void MainWindow::connectionClosedByServer()
{
    ui->pushButton->setText( tr("연결") );
    m_bConnect = false;

    m_bHeader = true;
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
    int i, j;

    QString qBuffer;

    switch( pstLanHeader->opCode ) {
    case enRES_MODE :

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

    default :
        break;
    }

    //ui->memoryDump->moveCursor( QTextCursor::start);

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

    if( iRet > 0 ) {
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

    strLanHeader.opCode = enREQ_DUMP_LIST;
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

    strLanHeader.opCode = enREQ_MODE;
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

    strLanHeader.opCode = enREQ_MODE;
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

    strLanHeader.opCode = enREQ_MODE;
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
    int iRet;

    STR_LAN_HEADER strLanHeader;
    time_t tiNow;

    strLanHeader.opCode = enREQ_ANAL_START;
    strLanHeader.uiLength = sizeof( time_t );

    tiNow = time(NULL);

    iRet = SendRSA( & strLanHeader, & tiNow, strLanHeader.uiLength );
}

void MainWindow::on_MODE_clicked()
{

}

/**
 * @brief MainWindow::on_radioButton_3_clicked
 */
void MainWindow::on_radioButton_3_clicked()
{

}

void MainWindow::on_radioButton_ESMode_clicked()
{
    // g_enMode = enESMode
}
