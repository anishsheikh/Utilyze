#include "Headers/haptic.h"
#include <QPainter>

HapticButton::HapticButton(const QString &label) :
    QWidget(0), m_label(label)
{
    setMinimumSize(100, 100);
}

void HapticButton::setLabel(const QString& label)
{
    m_label = label;
}

void HapticButton::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}

void HapticButton::paintEvent(QPaintEvent *)
{
    QPainter paint(this);

    QRect r(1, 1, width()-2, height()-2);
    paint.drawRoundedRect(r, 10, 10);
    paint.drawText(r, Qt::AlignCenter, m_label);
}
