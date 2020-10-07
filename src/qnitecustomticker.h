#ifndef QNITECUSTOMTICKER_H
#define QNITECUSTOMTICKER_H

#include "qniteticker.h"

class QniteCustomTicker : public QniteTicker
{
  Q_OBJECT

public:
  QniteCustomTicker(QObject *parent = 0);
  virtual ~QniteCustomTicker() {}

  virtual void reset();
  virtual void setNumSteps(int);

protected:
  virtual void buildTicks();
};

#endif // QNITECUSTOMTICKER_H
