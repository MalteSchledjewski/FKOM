#include "statisticseventgenerator.h"

StatisticsEventGenerator::StatisticsEventGenerator(double lambda): lambda(lambda)
{

}

Event StatisticsEventGenerator::getNextStatisticsEvent(double time)
{
  return Event(EventType::COUNT,time + 1/lambda,0);
}
