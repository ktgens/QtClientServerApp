#include "StateButton.h"

StateButton::StateButton(QWidget *parent): QToolButton(parent)
{
    setCheckable(true);

    connect(this, &QToolButton::toggled, this, &StateButton::updateButtonIcon);
}

void StateButton::setOnIcon(const QIcon &icon)
{
    m_onIcon = icon;
    if(isChecked())
        updateButtonIcon(true);
}

void StateButton::setOffIcon(const QIcon &icon)
{
    m_offIcon = icon;
    if(!isChecked())
        updateButtonIcon(false);
}

void StateButton::updateButtonIcon(bool checked)
{
    setIcon(checked ? m_onIcon : m_offIcon);
}
