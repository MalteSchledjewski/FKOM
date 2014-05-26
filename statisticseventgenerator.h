#ifndef STATISTICSEVENTGENERATOR_H
#define STATISTICSEVENTGENERATOR_H


#include "event.h"

class StatisticsEventGenerator
{
public:
  StatisticsEventGenerator(double lambda);
  Event getNextStatisticsEvent(double time);
private:
  const double lambda;
};

#endif // STATISTICSEVENTGENERATOR_H
