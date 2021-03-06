#include "powerwidget.h"
#include "dbuspower.h"
#include "powerpopupwidget.h"
#include "fontlabel.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPainter>

using namespace dtb::widgets;

namespace dtb {
namespace power {
PowerWidget::PowerWidget(QWidget *parent) : QWidget(parent) {
    m_popup = new PowerPopupWidget;

    setFixedHeight(26);

    m_batteryIcon = new FontLabel;
    m_battery = new QLabel;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(3);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->addWidget(m_batteryIcon, 0, Qt::AlignVCenter);
    layout->addWidget(m_battery, 0, Qt::AlignVCenter);

    setLayout(layout);

    m_battery->setStyleSheet("QLabel {"
                             "font: 14px;"
                             "color: rgb(67, 67, 62);"
                             "font-weight: 500;"
                             "}");

    m_batteryIcon->setStyleSheet("QLabel {"
                                 "color: rgb(67, 67, 62);"
                                 "}");

    m_powerInter = new DBusPower(this);

    updateBatteryIcon();

    connect(m_powerInter, &DBusPower::BatteryPercentageChanged, this, &PowerWidget::updateBatteryIcon);
    connect(m_powerInter, &DBusPower::BatteryStateChanged, this, &PowerWidget::updateBatteryIcon);
    connect(m_powerInter, &DBusPower::OnBatteryChanged, this, &PowerWidget::updateBatteryIcon);
    connect(m_popup, &PowerPopupWidget::requestPowerPrecent, m_battery, &QLabel::setVisible);
    connect(m_popup, &PowerPopupWidget::requestHidePopup, this, &PowerWidget::requestHidePopup);
}

QWidget *PowerWidget::popup() {
    return m_popup;
}

void PowerWidget::updateBatteryIcon() {
    const BatteryPercentageMap data = m_powerInter->batteryPercentage();

    if (data.isEmpty()) {
        m_battery->hide();
        m_batteryIcon->setIcon(QChar(0xE836), 16);
        return;
    }

    m_battery->show();

    const uint value = qMin(100.0, qMax(0.0, data.value("Display")));
    const int percentage = std::round(value);
    const bool plugged = !m_powerInter->onBattery();

    QChar percentageStr;

    if (plugged) {
        if (percentage <= 5 && percentage >= 0)
            percentageStr = 0xE85A;
        else if (percentage <= 10)
            percentageStr = 0xE85B;
        else if (percentage <= 20)
            percentageStr = 0xE85C;
        else if (percentage <= 30)
            percentageStr = 0xE85D;
        else if (percentage <= 40)
            percentageStr = 0xE85E;
        else if (percentage <= 50)
            percentageStr = 0xE85F;
        else if (percentage <= 60)
            percentageStr = 0xE860;
        else if (percentage <= 70)
            percentageStr = 0xE861;
        else if (percentage <= 80)
            percentageStr = 0xE862;
        else if (percentage <= 90)
            percentageStr = 0xE863;
        else if (percentage <= 100)
            percentageStr = 0xEA93;
    } else {
        if (percentage <= 5 && percentage >= 0)
            percentageStr = 0xE850;
        else if (percentage <= 10)
            percentageStr = 0xE851;
        else if (percentage <= 20)
            percentageStr = 0xE852;
        else if (percentage <= 30)
            percentageStr = 0xE853;
        else if (percentage <= 40)
            percentageStr = 0xE854;
        else if (percentage <= 50)
            percentageStr = 0xE855;
        else if (percentage <= 60)
            percentageStr = 0xE856;
        else if (percentage <= 70)
            percentageStr = 0xE857;
        else if (percentage <= 80)
            percentageStr = 0xE858;
        else if (percentage <= 90)
            percentageStr = 0xE859;
        else if (percentage <= 100)
            percentageStr = 0xE83F;
    }

    m_battery->setText(QString::number(percentage) + "%");
    m_batteryIcon->setIcon(percentageStr, 17);
}

void PowerWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);

    m_enter = true;

    m_battery->setStyleSheet("QLabel {"
                             "font: 14px;"
                             "color: white;"
                             "font-weight: 500;"
                             "}");

    m_batteryIcon->setStyleSheet("QLabel {"
                                 "color: white;"
                                 "}");

    update();
}

void PowerWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    m_enter = false;

    m_battery->setStyleSheet("QLabel {"
                             "font: 14px;"
                             "color: rgb(67, 67, 62);"
                             "font-weight: 500;"
                             "}");

    m_batteryIcon->setStyleSheet("QLabel {"
                                 "color: rgb(67, 67, 62);"
                                 "}");

    update();
}

void PowerWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    if (m_enter) {
        painter.fillRect(rect(), QColor("#1E90FF"));
    }
}
}
}
