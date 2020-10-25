
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
    enAOA,
} ;




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
    connect( & m_theTcpSocket, SIGNAL(error()), this, SLOT(onError()));

    QStringList aettableHeader;
    aettableHeader << "번호" << "AET#" << "방위";
    ui->aettableWidget->setColumnCount( 100 );
    ui->aettableWidget->setHorizontalHeaderLabels( aettableHeader );

    vTable.clear();

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
    nextBlockSize = 0;

    if( m_bConnect == false ) {
        // 자신의 IP 에서 연결 요구하고 연결 실패되면 직접 다이렉트로 연결을 시도한다.
        m_theTcpSocket.connectToHost(QHostAddress::LocalHost, CCU_PORT );
        bConnected = m_theTcpSocket.waitForConnected();

        ui->aettableWidget->clear();

        if( bConnected == false ) {
            m_theTcpSocket.connectToHost( "zcu111.com", CCU_PORT );
        }


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
        InsertTable( pByteData );
        break;

    case esAET_UPD_CCU :
        UpdateTable( pByteData );
        break;

    case esAET_DEL_CCU :
        DeleteTable( pByteData );
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
void MainWindow::InsertTable( void *pByteData )
{
    STR_AET *pAET;
    STR_LIST_TABLE stListTable;

    QString qTemp;

    pAET = ( STR_AET *) pByteData;

    stListTable.uiABTID = pAET->noEMT;

    ui->aettableWidget->insertRow( ui->aettableWidget->rowCount() );

    stListTable.iIndexOfTable = ui->aettableWidget->rowCount() - 1;

    qTemp.sprintf( "1" );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enNo, new QTableWidgetItem(qTemp) );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enNoAET, new QTableWidgetItem(qTemp) );
    ui->aettableWidget->setItem( stListTable.iIndexOfTable, enAOA, new QTableWidgetItem(qTemp) );

    vTable.push_back( stListTable );

}

/**
 * @brief MainWindow::UpdateTable
 * @param pByteData
 */
void MainWindow::UpdateTable( void *pByteData )
{

}

/**
 * @brief MainWindow::DeleteTable
 * @param pByteData
 */
void MainWindow::DeleteTable( void *pByteData )
{

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
