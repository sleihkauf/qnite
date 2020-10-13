#include "qnitetimeticker.h"

QniteTimeTicker::QniteTimeTicker(QObject *parent) : QniteTicker(parent) {}

qreal mapTo(qreal value, qreal srcMin, qreal srcMax, qreal dstMin,
            qreal dstMax) {

  qreal sourceSize = qAbs(srcMax - srcMin);
  qreal destSize = qAbs(dstMax - dstMin);

  qreal f = destSize / sourceSize;
  qreal v = f * qAbs(srcMin - value);

  if (value < srcMin) {
    v *= -1;
  }

  return dstMin + v;
}

void QniteTimeTicker::buildTicks() {

  if (m_currentTime.isValid()) {
    QList<qreal> majors{0};

    m_sourceTimes.clear();

    QDateTime timeUpper = m_currentTime;
    QDateTime timeLower = m_currentTime.addSecs(-m_visibleTimeSpan);

    // build tick from 0 to "visible timespan" every "tick span" including left
    // and right bounds
    qreal tick =
        (m_tickSpanSec - ((timeLower.time().minute() * 60) % m_tickSpanSec));
    tick -= timeLower.time().second();

    while (tick < m_visibleTimeSpan) {
      majors.push_back(tick);
      tick += m_tickSpanSec;
    }
    majors.push_back(m_visibleTimeSpan);

    for (auto v : majors) {
      m_sourceTimes.push_back(timeLower.addSecs(v));
    }

    // scale to lower/upper
    for (int i = 0; i < majors.size(); i++) {
      majors[i] = mapTo(majors[i], 0, m_visibleTimeSpan, lower(), upper());
    }

    // set tick series
    setMajorTicks(majors);
  }
}

int QniteTimeTicker::visibleTimeSpan() const { return m_visibleTimeSpan; }

void QniteTimeTicker::setVisibleTimeSpan(int sec) {
  if (m_visibleTimeSpan != sec) {
    m_visibleTimeSpan = sec;
  }
}

const QDateTime &QniteTimeTicker::currentTime() const { return m_currentTime; }

void QniteTimeTicker::setCurrentTime(const QDateTime &time) {
  if (m_currentTime != time) {
    m_currentTime = time;
    buildTicks();
  }
}

int QniteTimeTicker::tickSpanSec() const { return m_tickSpanSec; }

void QniteTimeTicker::setTickSpanSec(int sec) {
  if (m_tickSpanSec != sec) {
    m_tickSpanSec = sec;
  }
}
