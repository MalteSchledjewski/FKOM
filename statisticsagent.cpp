#include "statisticsagent.h"

StatisticsAgent::StatisticsAgent(StatisticsAggregate &aggregate): statAggregate(aggregate)
{

}


void StatisticsAgent::log(double value)
{
  sum += value;
  sumSquare += value*value;
  ++numberOfElements;
  if(numberOfElements == BLOCK_SIZE)
    {
      statAggregate.log(sum/BLOCK_SIZE,sumSquare/BLOCK_SIZE);
      sum = 0.0;
      sumSquare = 0.0;
      numberOfElements = 0;
    }
}
