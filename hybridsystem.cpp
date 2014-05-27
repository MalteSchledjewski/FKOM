#include "distributedsimulation.h"
#include "scheduling.cpp"

#include <iostream>


int main()
{
  double lambda = 2.1;
  double m = 2;
  short numberOfWorker = 1;
  size_t limit = 10;
  PacketGenerator packGen = PacketGenerator(lambda,Priority::LOW);
  std::vector<PacketGenerator> vecPackGen {packGen};
  std::vector<Worker> vecWorker{};
  for(short index = 0; index < numberOfWorker;++index)
    {
      vecWorker.emplace_back(m);
    }
  std::function<bool(Packet&, Packet&)> earlierFun = earlier;
  std::function<short(std::vector<Worker>&,Packet&)> which = whichFree;
  DistributedSimulation sim(vecPackGen,vecWorker,true,limit,earlierFun,which,5,0.00001);
  sim.run();
  return 0;
}

