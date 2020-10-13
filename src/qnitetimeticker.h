#ifndef QNITETIMETICKER_H
#define QNITETIMETICKER_H

#include "qniteticker.h"
#include <QDateTime>
#include <QList>

class QniteTimeTicker : public QniteTicker {
  Q_OBJECT

public:
  QniteTimeTicker(QObject *parent = 0);
  virtual ~QniteTimeTicker() {}

  int visibleTimeSpan() const;
  void setVisibleTimeSpan(int sec);

  const QDateTime &currentTime() const;
  void setCurrentTime(const QDateTime &time);

  const QList<QDateTime> &sourceTimes() const { return m_sourceTimes; };

  int tickSpanSec() const;
  void setTickSpanSec(int sec);

protected:
  virtual void buildTicks();

private:
  static constexpr int VisibleTimeSpanDefault = 1800;
  int m_visibleTimeSpan{VisibleTimeSpanDefault};

  static constexpr int TickSpanDefault = 300;
  int m_tickSpanSec{TickSpanDefault};

  QDateTime m_currentTime;
  QList<QDateTime> m_sourceTimes;
};

#endif // QNITETIMETICKER_H
