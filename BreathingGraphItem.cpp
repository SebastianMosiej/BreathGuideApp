#include "BreathingGraphItem.h"
#include <QPainter>

namespace {
    constexpr const int milisecondInterval{25};
    constexpr const float topMargin{20.0};
    constexpr const float bottomMargin{20.0};
    constexpr const float leftMargin{20.0};
    constexpr const float rightMargin{20.0};
    enum {
        INHALE_SECTION = 0,
        INHALE_HOLD_SECTION,
        EXHALE_SECTION,
        EXHALE_HOLD_SECTION,
        SECTION_MAX
    };
}

BreathingGraphItem::BreathingGraphItem(QQuickItem* parent) : QQuickPaintedItem(parent), m_running(true), m_timeLinePos(0), m_widthStep(-1) {
    startTimer(milisecondInterval);

    m_sectionPen.setStyle(Qt::SolidLine);
    m_sectionPen.setWidth(lineWidth());
    m_sectionPen.setColor(inhaleColor());
    m_sectionPen.setCapStyle(Qt::RoundCap);

    connect(this, &BreathingGraphItem::inhaleTimeChanged, [this](){this->recalculate(true);});
    connect(this, &BreathingGraphItem::inhaleHoldTimeChanged, [this](){this->recalculate(true);});
    connect(this, &BreathingGraphItem::exhaleTimeChanged, [this](){this->recalculate(true);});
    connect(this, &BreathingGraphItem::exhaleHoldTimeChanged, [this](){this->recalculate(true);});
    connect(this, &BreathingGraphItem::widthChanged, [this](){this->recalculate(true);});
    connect(this, &BreathingGraphItem::heightChanged, [this](){this->recalculate(true);});
 }

BreathingGraphItem::~BreathingGraphItem() {
}

void BreathingGraphItem::recalculate(bool force) {
    if (m_widthStep < 0 || force) {
        auto duration = inhaleTime() + inhaleHoldTime() + exhaleTime() + exhaleHoldTime();
        m_width = (boundingRect().width() - leftMargin - rightMargin);
        m_widthStep = m_width / (float)duration;
        m_sequencesWidth[0] = inhaleTime() * m_widthStep;
        m_sequencesWidth[1] = inhaleHoldTime() * m_widthStep;
        m_sequencesWidth[2] = exhaleTime() * m_widthStep;
        m_sequencesWidth[3] = exhaleHoldTime() * m_widthStep;
    }
}

void BreathingGraphItem::start() {
    m_time = QTime::currentTime();
    m_running = true;
    m_timeLinePos = 0;
    update();
}

void BreathingGraphItem::stop() {
    m_running = false;
    m_time = QTime::currentTime();
    update();
}

void BreathingGraphItem::timerEvent(QTimerEvent *) {
    update();
}

void BreathingGraphItem::update(const QRect &rect) {
             recalculate();
    QQuickPaintedItem::update(rect);
}

#include <QDebug>

void BreathingGraphItem::paint(QPainter* painter) {
    const auto bottomMargin = 20.0;
    auto height = boundingRect().height();

    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundColor());
    painter->drawRect(boundingRect());

    painter->setPen(m_sectionPen);

    auto section = xPointToSection(m_timeLinePos);
    auto start = QPointF(leftMargin, height - bottomMargin);
//    for(const auto i : m_sequencesWidth) {
    for(int i = 0; i < SECTION_MAX; i++) {
        if (section > i){
            start = drawTimeSection(painter, start, i);
        } else if (section == i){
            start = drawTimeSection(painter, start, i);
        } else {
            start = drawTimeSection(painter, start, i);
        }
//        start = drawTimeSection(painter, start, INHALE_HOLD_SECTION);
//        start = drawTimeSection(painter, start, EXHALE_SECTION);
//        start = drawTimeSection(painter, start, EXHALE_HOLD_SECTION);
    }

    drawTimeLine(painter);
}
/////////////////

QPointF BreathingGraphItem::drawTimeSection(QPainter* painter, QPointF start, int section) {
    auto circle = QRect{0,0, lineWidth(), lineWidth()};
    auto target = QPointF(0, 0);
    switch (section) {
    case INHALE_SECTION:
        target.ry() = topMargin;
        target.rx() = m_widthStep * inhaleTime();
        m_sectionPen.setColor(inhaleColor());
        break;
    case INHALE_HOLD_SECTION:
        target.ry() = topMargin;
        target.rx() = m_widthStep * inhaleHoldTime();
        m_sectionPen.setColor(inhaleHoldColor());
        break;
    case EXHALE_SECTION:
        target.ry() = boundingRect().height() - bottomMargin;
        target.rx() = m_widthStep * exhaleTime();
        m_sectionPen.setColor(exhaleColor());
        break;
    case EXHALE_HOLD_SECTION:
        target.ry() = boundingRect().height() - bottomMargin;
        target.rx() = m_widthStep * exhaleHoldTime();
        m_sectionPen.setColor(exhaleHoldColor());
        break;
    }
    target.rx() += start.x();
    painter->setPen(m_sectionPen);
    circle.moveCenter(start.toPoint());
    painter->drawEllipse(circle);
    painter->drawLine(start, target);
    circle.moveCenter(target.toPoint());
    painter->drawEllipse(circle);
    return target;
}

void BreathingGraphItem::drawTimeLine(QPainter* painter) {
    const qreal delta = m_time.msecsTo(QTime::currentTime()) / 1000.0;
    m_timeLinePos = m_timeLinePos+delta*m_widthStep;
    if (m_timeLinePos >= m_width)
        m_timeLinePos -= m_width;

    QPen pen{Qt::SolidLine};
    pen.setWidth(lineWidth());
    pen.setCapStyle(Qt::RoundCap);

    pen.setWidth(2);
    pen.setColor("yellow");
    painter->setPen(pen);
    painter->drawLine(m_timeLinePos+leftMargin,0.0, m_timeLinePos+leftMargin, boundingRect().height());
    m_time = QTime::currentTime();
}

int BreathingGraphItem::xPointToSection(float xPos) {
    auto pos = leftMargin;
    if (xPos < pos)
        return -1;
    for (int i = 0; i < 4; i++ ) {
        pos += m_sequencesWidth[i];
        if (xPos < pos)
            return i;
    }
    return 4;
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
