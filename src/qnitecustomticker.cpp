#include "qnitecustomticker.h"

QniteCustomTicker::QniteCustomTicker(QObject *parent) : QniteTicker(parent) {}

qreal mapTo(qreal value, qreal srcMin, qreal srcMax, qreal dstMin, qreal dstMax) {

  qreal sourceSize = qAbs(srcMax - srcMin);
  qreal destSize = qAbs(dstMax - dstMin);

  qreal f = destSize / sourceSize;
  qreal v = f * qAbs(srcMin - value);

  if (value < srcMin)
    v *= -1;

  return dstMin + v;
}

void QniteCustomTicker::buildTicks() {

  if(m_currentTime.isValid()) {
    QList<qreal> majors{0};

    m_sourceTimes.clear();

    constexpr qreal tickSpanSec = 300;

    QDateTime timeUpper = m_currentTime;
    QDateTime timeLower = m_currentTime.addSecs(-m_visibleTimeSpan);

    qreal upperValue = upper();
    qreal lowerValue = lower();

    // build tick from 0 to "visible timespan" every "tick span" including left and right bounds
    qreal tick = (5 - (timeLower.time().minute() % 5)) * 60;
    tick -= timeLower.time().second();

    while(tick < m_visibleTimeSpan) {
      majors.push_back(tick);
      tick += tickSpanSec;
    }
    majors.push_back(m_visibleTimeSpan);

    for(auto v : majors) {
      m_sourceTimes.push_back(timeLower.addSecs(v));
    }

    // scale to lower/upper
    for(int i = 0; i < majors.size(); i++) {
      majors[i] = mapTo(majors[i], 0, m_visibleTimeSpan, lower(), upper());
    }

    // set tick series
    setMajorTicks(majors);
  }
}

int QniteCustomTicker::visibleTimeSpan() const
{
  return m_visibleTimeSpan;
}

void QniteCustomTicker::setVisibleTimeSpan(int sec)
{
  if(m_visibleTimeSpan != sec)
  {
    m_visibleTimeSpan = sec;
  }
}

const QDateTime& QniteCustomTicker::currentTime() const
{
  return m_currentTime;
}

void QniteCustomTicker::setCurrentTime(const QDateTime& time)
{
  if(m_currentTime != time)
  {
    m_currentTime = time;
    buildTicks();
  }
}
