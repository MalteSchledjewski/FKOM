#ifndef STATISTICSAGENT_H
#define STATISTICSAGENT_H

#include "statisticsaggregate.h"

extern const size_t BLOCK_SIZE;
class StatisticsAgent
{
public:
  StatisticsAgent(StatisticsAggregate& aggregate);
  void log(double value);
private:
  double sum {0.0};
  double sumSquare {0.0};
  size_t numberOfElements  {0};
  StatisticsAggregate& statAggregate;
};

#endif // STATISTICSAGENT_H
