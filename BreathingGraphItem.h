#pragma once

#include "utils_qt.h"
#include <QQuickPaintedItem>

class QPainter;

class BreathingGraphItem : public QQuickPaintedItem {
    Q_OBJECT

    QX_PROPERTY_DECL(qreal, inhaleTime, setInhaleTime, 4.0)
    QX_PROPERTY_DECL(qreal, inhaleHoldTime, setInhaleHoldTime, 4.0)
    QX_PROPERTY_DECL(qreal, exhaleTime, setExhaleTime, 4.0)
    QX_PROPERTY_DECL(qreal, exhaleHoldTime, setExhaleHoldTime, 4.0)

    QX_PROPERTY_DECL(QColor, inhaleColor, setInhaleColor, "royalblue")
    QX_PROPERTY_DECL(QColor, inhaleHoldColor, setInhaleHoldColor, "green")
    QX_PROPERTY_DECL(QColor, exhaleColor, setExhaleColor, "steelblue")
    QX_PROPERTY_DECL(QColor, exhaleHoldColor, setExhaleHoldColor, "khaki")
    QX_PROPERTY_DECL(QColor, backgroundColor, setBackgroundColor, "white")

    QX_PROPERTY_DECL(int, lineWidth, setLineWidth, 10)
public:
    BreathingGraphItem(QQuickItem* = nullptr);
    ~BreathingGraphItem();

    void paint(QPainter*);
};

