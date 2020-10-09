#ifndef QNITE_TIME_AXIS_H
#define QNITE_TIME_AXIS_H

#include "qniteaxis.h"
#include <QDateTime>

class QniteTimeAxis : public QniteAxis {

  Q_OBJECT
  Q_PROPERTY(QDateTime currentTime READ currentTime WRITE setCurrentTime NOTIFY
                 currentTimeChanged)

  Q_PROPERTY(int visibleTimeSpan READ visibleTimeSpan WRITE setVisibleTimeSpan NOTIFY visibleTimeSpanChanged)

public:
  explicit QniteTimeAxis(QQuickItem *parent = 0);
  virtual ~QniteTimeAxis() {}

  QDateTime currentTime() const;
  void setCurrentTime(const QDateTime &time);

  int visibleTimeSpan() const;
  void setVisibleTimeSpan(int sec);

Q_SIGNALS:
  void currentTimeChanged();
  void visibleTimeSpanChanged();

public Q_SLOTS:
  virtual void processData() override;
  void timeChanged();

private:
  QDateTime m_currentTime;
  int m_visibleTimeSpan;
};

#endif // QNITE_TIME_AXIS_H
