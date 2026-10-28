#include "ServerWindow.h"
#include <QVBoxLayout>
#include <QTime>

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
}

void ServerWindow::log(const QString &message)
{
    QString timeStr = QTime::currentTime().toString("hh:mm:ss");
    m_logTextEdit->append(QString("[%1] %2").arg(timeStr, message));
}