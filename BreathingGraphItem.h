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
    QX_PROPERTY_DECL(QColor, timeLineColor, setTimeLineColor, "yellow")
    QX_PROPERTY_DECL(QColor, backgroundColor, setBackgroundColor, "white")

    QX_PROPERTY_DECL(int, lineWidth, setLineWidth, 10)

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(int phase READ phase NOTIFY phaseChanged)
    Q_PROPERTY(int remainingTime READ remainingTime  NOTIFY remainingTimeChanged)

Q_SIGNALS:
    void runningChanged(bool);
    void phaseChanged(int);
    void remainingTimeChanged(int);

public:
    BreathingGraphItem(QQuickItem* = nullptr);
    ~BreathingGraphItem();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    bool running() const { return m_running; }
    int phase() const { return m_timeLine.section; }
    int remainingTime() const { return m_timeLine.remainingTime; }
    void paint(QPainter*) override;

    static void init() {
        qmlRegisterType<BreathingGraphItem>("breathAppItems", 1, 0, "BreathingGraphItem");
    }
protected:
    void timerEvent(QTimerEvent *) override;
    QPointF drawTimeSection(QPainter*, QPointF startPoint, int section);
    void drawTimeLine(QPainter*);
    void xPointToSection(float);
    void update(const QRect &rect = QRect());

private:
    QTime m_time;
    bool m_running;

    struct {
        qreal x;
        int section;
        int currentSectionPos;
        float remainingTime;
    } m_timeLine;

    struct {
        float duration;
        float width;
    } m_sequenceData[4];

    float m_widthStep;
    QPen m_sectionPen;
    float m_width;
    float m_sequencesWidth[4];

    void recalculate(bool force = false);
 };

