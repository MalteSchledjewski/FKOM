#include "distributedsimulation.h"
#include "erlangc.h"
#include "scheduling.cpp"

#include <iostream>


int main()
{
  double lambda = 8./6;
  double m = 2;
  short numberOfWorker = 1;
  PacketGenerator packGen = PacketGenerator(lambda,Priority::LOW);
  std::vector<PacketGenerator> vecPackGen {packGen};
  std::vector<Worker> vecWorker{};
  for(short index = 0; index < numberOfWorker;++index)
    {
      vecWorker.emplace_back(m);
    }
  std::function<bool(Packet&, Packet&)> earlierFun = earlier;
  std::function<short(std::vector<Worker>&,Packet&)> which = whichFree;
  DistributedSimulation sim(vecPackGen,vecWorker,false,0,earlierFun,which,0,0.0001);
  sim.run();

  ErlangC stats(lambda,m,numberOfWorker);
  stats.printStatistics();
  return 0;
}

