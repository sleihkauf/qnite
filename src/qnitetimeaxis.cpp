#include "qnitetimeaxis.h"
#include "qniteclipper.h"
#include "qnitecustomticker.h"
#include "qnitelinearmapper.h"
#include "qnitelinearticker.h"
#include "qniteaxes.h"

QniteTimeAxis::QniteTimeAxis(QQuickItem *parent) : QniteAxis(parent) {
  setMapper(new QniteLinearMapper(this));
  setTicker(new QniteCustomTicker(this));

  connect(this, &QniteTimeAxis::currentTimeChanged, this,
          &QniteTimeAxis::timeChanged);
}

void QniteTimeAxis::processData() {
  // avoid ticker initialization when mapper is invalid
  if (m_mapper == nullptr) {
    m_ticker->reset();
  } else {
    m_ticker->setBoundaries(m_lowerBound, m_upperBound);

    m_majorTicks.clear();
    m_minorTicks.clear();
    m_labels.clear();

    // clip ticks
    QList<qreal> maj;
    QniteClipper clipper;
    clipper.clip(m_ticker->majorTicks(), m_lowerBound, m_upperBound, maj);

    // map to display
    for (auto v : maj) {
      m_majorTicks << m_mapper->mapTo(m_lowerBound, m_upperBound, 0, m_size, v,
                                      m_flip);
    }

    QniteCustomTicker* pTicker = dynamic_cast<QniteCustomTicker*>(m_ticker);

    m_labels.push_back("");
    for (auto i = 1; i < maj.size() - 1; ++i) {
      if(pTicker->sourceTimes().size()) {
        QString strLabel = pTicker->sourceTimes()[i].toString("hh:mm");
        m_labels.push_back(strLabel);
      }
    }
    m_labels.push_back("");

    // maps the axis position
    m_position =
        m_mapper->mapTo(m_lowerBound, m_upperBound, 0., m_size, 0., m_flip);
  }

  emit labelsChanged();
  emit majorTicksChanged();
}

void QniteTimeAxis::timeChanged() {
  if(m_ticker != nullptr) {
      dynamic_cast<QniteCustomTicker*>(m_ticker)->setCurrentTime(m_currentTime);
      processData();
    }
}

QDateTime QniteTimeAxis::currentTime() const { return m_currentTime; }

void QniteTimeAxis::setCurrentTime(const QDateTime &time) {
  if (m_currentTime != time) {
    m_currentTime = time;

    emit currentTimeChanged();
  }
}

int QniteTimeAxis::visibleTimeSpan() const
{
  return m_visibleTimeSpan;
}

void QniteTimeAxis::setVisibleTimeSpan(int sec)
{
  if(m_visibleTimeSpan != sec)
  {
    m_visibleTimeSpan = sec;

    if(m_ticker != nullptr) {
      dynamic_cast<QniteCustomTicker*>(m_ticker)->setVisibleTimeSpan(m_visibleTimeSpan);
    }

    emit visibleTimeSpanChanged();
  }
}
