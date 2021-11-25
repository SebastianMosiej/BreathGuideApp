#include "BreathingGraphItem.h"

#include <QPainter>

BreathingGraphItem::BreathingGraphItem(QQuickItem* parent) : QQuickPaintedItem(parent) {
}

BreathingGraphItem::~BreathingGraphItem() {

}

#include <QDebug>

void BreathingGraphItem::paint(QPainter* painter) {
    const auto topMargin = 20.0;
    const auto bottomMargin = 20.0;
    auto width = boundingRect().width();
    auto height = boundingRect().height();
    auto time = inhaleTime() + inhaleHoldTime() + exhaleTime() + exhaleHoldTime();


    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundColor());
    painter->drawRect(boundingRect());

    QPen pen{Qt::SolidLine};
    pen.setWidth(lineWidth());
    pen.setColor(inhaleColor());
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->setBrush(inhaleColor());

    auto start = QPointF(20.0, height - bottomMargin);
    auto target = QPointF((width / (float)time) * inhaleTime(),topMargin);
    painter->drawLine(start,target);

    start = target;
    target = QPointF((width / (float)time) * inhaleHoldTime() + target.x(),topMargin);
    pen.setColor(inhaleHoldColor());
    painter->setPen(pen);

    painter->drawLine(start,target);

    start = target;
    target = QPointF((width / (float)time) * exhaleTime() + target.x(),height - bottomMargin);
    pen.setColor(exhaleColor());
    painter->setPen(pen);
    painter->drawLine(start,target);

    start = target;
    target = QPointF((width / (float)time) * exhaleHoldTime() + target.x(),height - bottomMargin);
    pen.setColor(exhaleHoldColor());
    painter->setPen(pen);
    painter->drawLine(start,target);
}

QX_PROPERTY_IMPL(BreathingGraphItem, inhaleTime, setInhaleTime)
QX_PROPERTY_IMPL(BreathingGraphItem, inhaleHoldTime, setInhaleHoldTime)
QX_PROPERTY_IMPL(BreathingGraphItem, exhaleTime, setExhaleTime)
QX_PROPERTY_IMPL(BreathingGraphItem, exhaleHoldTime, setExhaleHoldTime)

QX_PROPERTY_IMPL(BreathingGraphItem, inhaleColor, setInhaleColor)
QX_PROPERTY_IMPL(BreathingGraphItem, inhaleHoldColor, setInhaleHoldColor)
QX_PROPERTY_IMPL(BreathingGraphItem, exhaleColor, setExhaleColor)
QX_PROPERTY_IMPL(BreathingGraphItem, exhaleHoldColor, setExhaleHoldColor)
QX_PROPERTY_IMPL(BreathingGraphItem, backgroundColor, setBackgroundColor)
QX_PROPERTY_IMPL(BreathingGraphItem, lineWidth, setLineWidth)
