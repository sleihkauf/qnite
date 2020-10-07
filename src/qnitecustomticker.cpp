#include "qnitecustomticker.h"

QniteCustomTicker::QniteCustomTicker(QObject *parent) : QniteTicker(parent) {}

void QniteCustomTicker::buildTicks() {

  QList<qreal> majors;
  QList<qreal> mins;

  // set tick series
  // setMinorTicks(mins);
  // setMajorTicks(majors);
}

void QniteCustomTicker::reset() { QniteTicker::reset(); }

void QniteCustomTicker::setNumSteps(int steps) {
  if (steps < 2) {
    return;
  }

  QniteTicker::setNumSteps(steps);
}
