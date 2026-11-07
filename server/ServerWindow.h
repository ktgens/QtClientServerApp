#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QPushButton>

class ServerWindow: public QWidget
{

public:
    ServerWindow(QWidget *parent = nullptr);

private:
    void startServer();
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

    void log(const QString &message);

    QTcpServer *m_server;
    QTextEdit *m_logTextEdit;
    QPushButton *m_startBtn;

    const quint16 port = 6767;
};