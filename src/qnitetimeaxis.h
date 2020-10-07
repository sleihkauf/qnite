#ifndef QNITE_TIME_AXIS_H
#define QNITE_TIME_AXIS_H

#include "qnitelinearaxis.h"
#include <QDateTime>

class QniteTimeAxis : public QniteLinearAxis {

  Q_OBJECT
  Q_PROPERTY(QDateTime currentTime READ currentTime WRITE setCurrentTime NOTIFY
                 currentTimeChanged)

public:
  explicit QniteTimeAxis(QQuickItem *parent = 0);
  virtual ~QniteTimeAxis() {}

  QDateTime currentTime() const;
  void setCurrentTime(const QDateTime &time);

Q_SIGNALS:
  void currentTimeChanged();

public Q_SLOTS:
  virtual void processData();
  void timeChanged();

private:
  QDateTime m_currentTime;
};

#endif // QNITE_TIME_AXIS_H
