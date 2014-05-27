#include "statisticsaggregate.h"

#include <cmath>

const size_t BLOCK_SIZE = 100000;

StatisticsAggregate::StatisticsAggregate(double precission): precission(precission),standardDeviation(0.0)
{
}

void StatisticsAggregate::log(double sum, double sumOfSquares)
{
  _mutex.lock();
  _sum += sum;
  _sumSquare += sumOfSquares;
  ++count;
  double avgSum = _sum/count;
  double avgSumSquares = _sumSquare/count;
  double totalVariance = (avgSumSquares - avgSum*avgSum)/(BLOCK_SIZE * count);
  _mutex.unlock();
  standardDeviation = std::sqrt(totalVariance);
}

double StatisticsAggregate::getExpectedValue()
{
  _mutex.lock();
  double expectedValue{0};
  if(count!=0)
    {
      expectedValue = _sum/count;
    }
  _mutex.unlock();
  return expectedValue;
}


double StatisticsAggregate::getStandardDeviation()
{
  return standardDeviation;
}

bool StatisticsAggregate::precissionSatisfied()
{
  return standardDeviation < precission;
}
