#include "ClientWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QDataStream>

ClientWindow::ClientWindow(QWidget *parent): QWidget(parent)
{
    m_ipEdit = new QLineEdit("127.0.0.1", this);
    m_portEdit = new QLineEdit("6767", this);
    m_filePathEdit = new QLineEdit(this);
    m_filePathEdit->setReadOnly(true);
    m_filePathEdit->setPlaceholderText("Путь");

    m_selectFileBtn = new QPushButton("Выбрать файл", this);
    m_sendBtn = new QPushButton("Отправить", this);
    m_statusLabel = new QLabel("Ожидание выбора файла", this);

    //ui
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //settings
    QHBoxLayout *connLayout = new QHBoxLayout();
    connLayout->addWidget(new QLabel("IP:", this));
    connLayout->addWidget(m_ipEdit);
    connLayout->addWidget(new QLabel("Порт:", this));
    connLayout->addWidget(m_portEdit);
    mainLayout->addLayout(connLayout);

    //file
    QHBoxLayout *fileLayout = new QHBoxLayout();
    fileLayout->addWidget(m_filePathEdit);
    fileLayout->addWidget(m_selectFileBtn);
    mainLayout->addLayout(fileLayout);

    mainLayout->addWidget(m_sendBtn);
    mainLayout->addWidget(m_statusLabel);

    m_socket = new QTcpSocket(this);

    connect(m_selectFileBtn, &QPushButton::clicked, this, &ClientWindow::onSelectFile);
    connect(m_sendBtn, &QPushButton::clicked, this, &ClientWindow::onSendFile);

    connect(m_socket, &QTcpSocket::connected, this, &ClientWindow::onConnected);
    connect(m_socket, &QTcpSocket::bytesWritten, this, &ClientWindow::onBytesWritten);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &ClientWindow::onError);
}

void ClientWindow::onSelectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл для отправки");
    if (!filePath.isEmpty()) {
        m_selectedFilePath = filePath;
        m_filePathEdit->setText(m_selectedFilePath);
        m_statusLabel->setText("Файл выбран");
    }
}

void ClientWindow::onSendFile()
{
    if (m_selectedFilePath.isEmpty()) {
        m_statusLabel->setText("Ошибка, файл не выбран");
        return;
    }

    m_sendBtn->setEnabled(false);
    m_statusLabel->setText("Подключение к серверу...");

    QString ip = m_ipEdit->text().trimmed();
    quint16 port = m_portEdit->text().toUShort();
    m_socket->connectToHost(ip, port);
}

void ClientWindow::onConnected()
{
    m_statusLabel->setText("Соединение установлено.");

    QFile file(m_selectedFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_statusLabel->setText("Ошибка, не удалось прочитать файл");
        m_sendBtn->setEnabled(true);
        m_socket->disconnectFromHost();
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QFileInfo fileInfo(m_selectedFilePath);
    QString fileName = fileInfo.fileName();
    quint64 fileSize = fileData.size();

    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);

    out << fileSize << fileName << fileData;

    m_socket->write(packet);
}

void ClientWindow::onBytesWritten(qint64 bytes)
{
    Q_UNUSED(bytes);

    if (m_socket->bytesToWrite() == 0) {
        m_statusLabel->setText("Статус: Файл успешно отправлен на сервер");
        m_sendBtn->setEnabled(true);
        m_socket->disconnectFromHost();
    }
}

void ClientWindow::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    m_statusLabel->setText("Ошибка сети, " + m_socket->errorString());
    m_sendBtn->setEnabled(true);
}