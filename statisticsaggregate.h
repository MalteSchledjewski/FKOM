#ifndef STATISTICSAGGREGATE_H
#define STATISTICSAGGREGATE_H
#include <cstdlib>
#include <mutex>
extern const size_t BLOCK_SIZE;
class StatisticsAggregate
{
public:
  StatisticsAggregate(double precission);
  void log(double sum, double sumOfSquares);
  bool precissionSatisfied();
  double getStandardDeviation();
  double getExpectedValue();
private:
  const double precission;
  double _sum {0};
  double _sumSquare {0};
  double standardDeviation;
  size_t count {0};
  std::mutex _mutex {};
};

#endif // STATISTICSAGGREGATE_H
