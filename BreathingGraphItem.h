#pragma once

#include "utils_qt.h"
#include <QQuickPaintedItem>
#include <QTime>
#include <QPen>

class QPainter;

class BreathingGraphItem : public QQuickPaintedItem {
    Q_OBJECT

    QX_PROPERTY_DECL(qreal, inhaleTime, setInhaleTime, 4.0)
    QX_PROPERTY_DECL(qreal, inhaleHoldTime, setInhaleHoldTime, 2.0)
    QX_PROPERTY_DECL(qreal, exhaleTime, setExhaleTime, 4.0)
    QX_PROPERTY_DECL(qreal, exhaleHoldTime, setExhaleHoldTime, 2.0)

    QX_PROPERTY_DECL(QColor, inhaleColor, setInhaleColor, "royalblue")
    QX_PROPERTY_DECL(QColor, inhaleHoldColor, setInhaleHoldColor, "green")
    QX_PROPERTY_DECL(QColor, exhaleColor, setExhaleColor, "steelblue")
    QX_PROPERTY_DECL(QColor, exhaleHoldColor, setExhaleHoldColor, "khaki")
    QX_PROPERTY_DECL(QColor, backgroundColor, setBackgroundColor, "white")

    QX_PROPERTY_DECL(int, lineWidth, setLineWidth, 10)
public:
    BreathingGraphItem(QQuickItem* = nullptr);
    ~BreathingGraphItem();

    void start();
    void stop();
    bool isRunning() { return m_running; }
    void paint(QPainter*) override;

protected:
    void timerEvent(QTimerEvent *) override;
    QPointF drawTimeSection(QPainter*, QPointF startPoint, int section);
    void drawTimeLine(QPainter*);
    int xPointToSection(float);
    void update(const QRect &rect = QRect());

private:
    QTime m_time;
    bool m_running;
    qreal m_timeLinePos;
    float m_widthStep;
    QPen m_sectionPen;
    float m_width;
    float m_sequencesWidth[4];

    void recalculate(bool force = false);
 };

