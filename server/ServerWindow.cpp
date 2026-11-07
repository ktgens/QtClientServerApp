#include "ServerWindow.h"
#include <QVBoxLayout>
#include <QTime>
#include <QFile>
#include <QFileInfo>

ServerWindow::ServerWindow(QWidget *parent) 
    : QWidget(parent)
{
    m_startBtn = new QPushButton("Запустить сервер", this);
    m_logTextEdit = new QTextEdit(this);
    m_logTextEdit->setReadOnly(true); 

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_startBtn);
    layout->addWidget(m_logTextEdit);

    log("Сервер инициализирован. Нажмите кнопку для старта.");

    connect(m_startBtn, &QPushButton::clicked, this, &ServerWindow::startServer);
}

void ServerWindow::log(const QString &message)
{
    QString timeStr = QTime::currentTime().toString("hh:mm:ss");
    m_logTextEdit->append(QString("[%1] %2").arg(timeStr, message));
}

void ServerWindow::startServer()
{
    m_server = new QTcpServer(this);
    
    if(!m_server->listen(QHostAddress::Any,port))
    {
        log("Ошибка запуска сервера: " + m_server->errorString());
        return;
    }

    log(QString("Сервер запущен на порту %1").arg(port));
    m_startBtn->setEnabled(false);

    connect(m_server, &QTcpServer::newConnection, this, &ServerWindow::onNewConnection);
}

void ServerWindow::onNewConnection()
{
    QTcpSocket *clientSocket = m_server->nextPendingConnection();
    log(QString("Подключился клиент:%1").arg(clientSocket->peerAddress().toString()));

    connect(clientSocket,&QTcpSocket::readyRead, this, &ServerWindow::onReadyRead);
    connect(clientSocket,&QTcpSocket::disconnected, this, &ServerWindow::onClientDisconnected);
}

void ServerWindow::onClientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    log(QString("Отключился клиент:%1").arg(socket->peerAddress().toString()));

    socket->deleteLater();

}

void ServerWindow::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    in.startTransaction();

    quint64 fileSize = 0;
    QString fileName;
    QByteArray fileData;

    in >> fileSize >> fileName >> fileData;

    if (!in.commitTransaction()) return; 

    log(QString("Принят файл: %1 (размер: %2 байт)").arg(fileName).arg(fileSize));

    QFile file("received_" + QFileInfo(fileName).fileName());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(fileData);
        file.close();
        log(QString("Файл успешно сохранён: %1").arg(file.fileName()));
    } else {
        log(QString("Ошибка сохранения файла: %1").arg(file.errorString()));
    }
}