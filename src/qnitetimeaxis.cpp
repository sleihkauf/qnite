#include "qnitetimeaxis.h"
#include "qniteclipper.h"
#include "qnitecustomticker.h"
#include "qnitelinearmapper.h"
#include "qnitelinearticker.h"

QniteTimeAxis::QniteTimeAxis(QQuickItem *parent) : QniteLinearAxis(parent) {
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

    for (auto i = 0; i < maj.size(); ++i) {
      QString strLabel = m_currentTime.toString("hh:mm:ss");
      m_labels.push_back(strLabel);
    }

    // maps the axis position
    m_position =
        m_mapper->mapTo(m_lowerBound, m_upperBound, 0., m_size, 0., m_flip);
  }

  emit labelsChanged();
  emit majorTicksChanged();
}

void QniteTimeAxis::timeChanged() { processData(); }

QDateTime QniteTimeAxis::currentTime() const { return m_currentTime; }

void QniteTimeAxis::setCurrentTime(const QDateTime &time) {
  if (m_currentTime != time) {
    m_currentTime = time;
    emit currentTimeChanged();
  }
}
