#ifndef QNITECUSTOMTICKER_H
#define QNITECUSTOMTICKER_H

#include "qniteticker.h"
#include <QDateTime>
#include <QList>

class QniteCustomTicker : public QniteTicker
{
  Q_OBJECT

public:
  QniteCustomTicker(QObject *parent = 0);
  virtual ~QniteCustomTicker() {}

  int visibleTimeSpan() const;
  void setVisibleTimeSpan(int sec);

  const QDateTime& currentTime() const;
  void setCurrentTime(const QDateTime& time);

  const QList<QDateTime>& sourceTimes() const { return m_sourceTimes; };

protected:
  virtual void buildTicks();

private:
  static constexpr int VisibleTimeSpanDefault = 1800;
  int m_visibleTimeSpan{VisibleTimeSpanDefault};
  QDateTime m_currentTime;
  QList<QDateTime> m_sourceTimes;
};

#endif // QNITECUSTOMTICKER_H
