#pragma once

#include <QIcon>
#include <QToolButton>

class StateButton: public QToolButton
{
    public:
        explicit StateButton(QWidget *parent = nullptr);

        void setOnIcon(const QIcon &icon);
        void setOffIcon(const QIcon &icon);

    private:
        void updateButtonIcon(bool checked);

        QIcon m_onIcon;
        QIcon m_offIcon;
};