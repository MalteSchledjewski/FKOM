#include "statisticsaggregate.h"

#include <cmath>

const size_t BLOCK_SIZE = 100000;

StatisticsAggregate::StatisticsAggregate(double precission): precission(precission),standardDeviation(0.0)
{
}

void StatisticsAggregate::log(double sum, double sumOfSquares)
{
  std::lock_guard<std::mutex> lock(_mutex);
  _sum += sum;
  _sumSquare += sumOfSquares;
  ++count;
  double avgSum = _sum/count;
  double avgSumSquares = _sumSquare/count;
  double totalVariance = (avgSumSquares - avgSum*avgSum)/(BLOCK_SIZE * count);
  standardDeviation = std::sqrt(totalVariance);
}

double StatisticsAggregate::getExpectedValue()
{
  std::lock_guard<std::mutex> lock(_mutex);
  double expectedValue{0};
  if(count!=0)
    {
      expectedValue = _sum/count;
    }
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
