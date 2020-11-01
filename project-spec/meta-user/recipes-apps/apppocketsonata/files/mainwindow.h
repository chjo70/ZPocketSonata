#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#include "chexspinbox.h"

#include "./Include/system.h"

#include "./Collect/DataFile/DataFile.h"

#define MAX_LAN_DATA            (1000)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct STR_LIST_TABLE {
    unsigned int uiABTID;

    int iIndexOfTable;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void EnableControl( bool bEnable );

    int SendRSA( STR_LAN_HEADER *pstrLanHeader, void *pData, int iLength );
    void MessageBox( char *pText );

    void ShowIBitResult( void *pData );
    void ShowCBitResult( void *pData );

    void InsertAETTable( void *pByteData );
    void UpdateAETTable( void *pByteData );
    void DeleteAETTable( void *pByteData );

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ParseAndDisplay( STR_LAN_HEADER *pstLanHeader, char *pByteData );

private slots:
    void newConnection();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onError(QAbstractSocket::SocketState socketState);
    void onReadyRead();

    void onConnectServer();
    void connectionClosedByServer();
    void onReadMessage();

    void on_pushButton_clicked();

    void on_MemoryDump_clicked();

    void on_ESMode_clicked();

    void on_EWMode_clicked();

    void on_ReadyMode_clicked();

    void on_AnalStart_clicked();

    void on_MODE_clicked();

    void on_BITTEST_clicked();

    void on_pushButton_SimPDW_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_ReloadLibrary_clicked();

private:
    Ui::MainWindow *ui;

    quint16 nextBlockSize;
    bool m_bConnect;

    bool m_bHeader;

    CDataFile m_theDataFile;

    QTcpSocket m_theTcpSocket;   //socket
    //QTcpServer *pServer;
    //QList<QTcpSocket*> _sockets;

    vector<STR_LIST_TABLE> vTable;

    int m_nCoList;

};
#endif // MAINWINDOW_H
