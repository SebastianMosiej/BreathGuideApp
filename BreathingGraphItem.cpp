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

BreathingGraphItem::BreathingGraphItem(QQuickItem* parent) : QQuickPaintedItem(parent), m_running(true), m_timeLine{0,0,0} , m_widthStep(-1) {
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
    m_timeLine.x = 0;
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
    auto height = boundingRect().height();

    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(Qt::NoPen);
    painter->setBrush(backgroundColor());
    painter->drawRect(boundingRect());

    painter->setPen(m_sectionPen);

    auto start = QPointF(leftMargin, height - bottomMargin);
    for(int i = 0; i < SECTION_MAX; i++) {
        start = drawTimeSection(painter, start, i);
    }

    drawTimeLine(painter);
}

QPointF BreathingGraphItem::drawTimeSection(QPainter* painter, QPointF start, int section) {
    auto circle = QRect{0,0, lineWidth(), lineWidth()};
    auto target = QPointF(0, 0);
    auto halfTarget = QPointF(0, 0);
    auto penColor = QColor();
    switch (section) {
    case INHALE_SECTION:
        target.ry() = topMargin;
        target.rx() = m_widthStep * inhaleTime();
        penColor = inhaleColor();
        break;
    case INHALE_HOLD_SECTION:
        target.ry() = topMargin;
        target.rx() = m_widthStep * inhaleHoldTime();
        penColor = inhaleHoldColor();
        break;
    case EXHALE_SECTION:
        target.ry() = boundingRect().height() - bottomMargin;
        target.rx() = m_widthStep * exhaleTime();
        penColor = exhaleColor();
        break;
    case EXHALE_HOLD_SECTION:
        target.ry() = boundingRect().height() - bottomMargin;
        target.rx() = m_widthStep * exhaleHoldTime();
        penColor = exhaleHoldColor();
        break;
    }

    if (m_timeLine.section== section) {
        m_sectionPen.setColor(penColor.lighter());
        painter->setPen(m_sectionPen);
        halfTarget.rx() = start.x() + target.x() - m_timeLine.currentSectionPos;
        double yStep = (start.y() - target.ry()) / target.x();
        halfTarget.ry() = target.y() + (yStep * m_timeLine.currentSectionPos);
        painter->drawLine(start, halfTarget);
    } else if (m_timeLine.section > section) {
        penColor = penColor.lighter();
        m_sectionPen.setColor(penColor);
        halfTarget = start;
    } else {
        m_sectionPen.setColor(penColor);
        halfTarget = start;
    }

    painter->setPen(m_sectionPen);
    circle.moveCenter(start.toPoint());
    painter->drawEllipse(circle);

    m_sectionPen.setColor(penColor);
    painter->setPen(m_sectionPen);
    target.rx() += start.x();
    painter->drawLine(halfTarget, target);
    circle.moveCenter(target.toPoint());
    painter->drawEllipse(circle);

    if (m_timeLine.section == section) {
        m_sectionPen.setColor(timeLineColor());
        painter->setPen(m_sectionPen);
        circle.moveCenter(halfTarget.toPoint());
        painter->drawEllipse(circle);
    }
    return target;
}

void BreathingGraphItem::drawTimeLine(QPainter* painter) {
    const qreal delta = m_time.msecsTo(QTime::currentTime()) / 1000.0;
    m_timeLine.x = m_timeLine.x+delta*m_widthStep;
    if (m_timeLine.x >= m_width)
        m_timeLine.x -= m_width;
    xPointToSection(m_timeLine.x);

    QPen pen{Qt::SolidLine};
    pen.setWidth(lineWidth());
    pen.setCapStyle(Qt::RoundCap);

    pen.setWidth(2);
    pen.setColor(timeLineColor());
    painter->setPen(pen);
    painter->drawLine(m_timeLine.x+leftMargin,0.0, m_timeLine.x+leftMargin, boundingRect().height());
    m_time = QTime::currentTime();
}

void BreathingGraphItem::xPointToSection(float xPos) {
    auto pos = 0;
    m_timeLine.section = -1;
    if (xPos < pos)
        return;
    for (int i = 0; i < 4; i++ ) {
        pos += m_sequencesWidth[i];
        if (xPos < pos) {
            m_timeLine.currentSectionPos = pos - m_timeLine.x;
            m_timeLine.section = i;
            return;
        }
    }
    assert(false);
    return;
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
QX_PROPERTY_IMPL(BreathingGraphItem, timeLineColor, setTimeLineColor)
QX_PROPERTY_IMPL(BreathingGraphItem, lineWidth, setLineWidth)
