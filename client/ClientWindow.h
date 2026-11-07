#pragma one

#include <QWidget>
#include <QTcpSocket>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class ClientWindow: public QWidget
{
    public:
        ClientWindow(QWidget *parent = nullptr);
    
    private:
        void onSelectFile();
        void onSendFile();
        void onConnected();
        void onBytesWritten(qint64 bytes);
        void onError(QAbstractSocket::SocketError socketError);

        QLineEdit   *m_ipEdit;
        QLineEdit   *m_portEdit;
        QLineEdit   *m_filePathEdit;
        QPushButton *m_selectFileBtn;
        QPushButton *m_sendBtn;
        QLabel      *m_statusLabel;

        QTcpSocket  *m_socket;
        QString      m_selectedFilePath;
};