#include "distributedsimulation.h"

#include <iostream>
#include <chrono>

DistributedSimulation::DistributedSimulation(std::vector<PacketGenerator> packGen, std::vector<Worker> workers,
                                             bool limited, size_t limit, std::function<bool(Packet&,Packet&)> earlier,
                                             std::function<short(std::vector<Worker>&, Packet&)> whichWorker, const double precision) :
  precission(precision),statPacketDropped(precission),statPacketsInWorker(precission),statPacketsInQueue(precission),
  statPacketsInSystem(precission),statTimeInSystem(precission),statTimeInQueue(precission),statTimeInQueueIfWaited(precission),
  statTimeInWorker(precission),simulationThreads(),_packGen(packGen),_workers(workers),_limited(limited),_limit(limit),
  _earlier(earlier),_whichWorker(whichWorker)
{
  simulationThreads.reserve(numberOfThreads);

}

void DistributedSimulation::printStatistics()
{
  std::cout << "dropped\t Nqueue\t  N\t   Nwork    Tqueue   Tqonly   T\t\tTwork\n" <<
               std::fixed << statPacketDropped.getStandardDeviation() <<" " <<
               std::fixed << statPacketsInQueue.getStandardDeviation() <<" " <<
               std::fixed << statPacketsInSystem.getStandardDeviation() <<" " <<
               std::fixed << statPacketsInWorker.getStandardDeviation() <<" " <<
               std::fixed << statTimeInQueue.getStandardDeviation() <<" " <<
               std::fixed << statTimeInQueueIfWaited.getStandardDeviation() <<" " <<
               std::fixed << statTimeInSystem.getStandardDeviation() <<" " <<
               std::fixed << statTimeInWorker.getStandardDeviation() << "\n" <<
               std::fixed << statPacketDropped.getExpectedValue() <<" " <<
               std::fixed << statPacketsInQueue.getExpectedValue() <<" " <<
               std::fixed << statPacketsInSystem.getExpectedValue() <<" " <<
               std::fixed << statPacketsInWorker.getExpectedValue() <<" " <<
               std::fixed << statTimeInQueue.getExpectedValue() <<" " <<
               std::fixed << statTimeInQueueIfWaited.getExpectedValue() <<" " <<
               std::fixed << statTimeInSystem.getExpectedValue() <<" " <<
               std::fixed << statTimeInWorker.getExpectedValue() <<"\n" <<
               std::endl;

  //TODO


}


bool DistributedSimulation::precissionSatisfied()
{
  return statPacketDropped.precissionSatisfied() &&
      statPacketsInQueue.precissionSatisfied() &&
      statPacketsInSystem.precissionSatisfied() &&
      statPacketsInWorker.precissionSatisfied() &&
      statTimeInQueue.precissionSatisfied() &&
      statTimeInQueueIfWaited.precissionSatisfied() &&
      statTimeInSystem.precissionSatisfied() &&
      statTimeInWorker.precissionSatisfied();
}


void startSimulation(std::vector<PacketGenerator> packGen, std::vector<Worker> workers,
                     bool limited, size_t limit, std::function<bool(Packet&,Packet&)> earlier,
                     std::function<short(std::vector<Worker>&, Packet&)> whichWorker,
                     StatisticsAggregate& statPacketDroppedAgg,
                     StatisticsAggregate& statPacketsInWorkerAgg,
                     StatisticsAggregate& statPacketsInQueueAgg,
                     StatisticsAggregate& statPacketsInSystemAgg,
                     StatisticsAggregate& statTimeInSystemAgg,
                     StatisticsAggregate& statTimeInQueueAgg,
                     StatisticsAggregate& statTimeInQueueIfWaitedAgg,
                     StatisticsAggregate& statTimeInWorkerAgg,
                     DistributedSimulation* parent)
{
  Simulation sim(packGen,workers,limited,limit,earlier,whichWorker,statPacketDroppedAgg,statPacketsInWorkerAgg,statPacketsInQueueAgg,
                 statPacketsInSystemAgg,statTimeInSystemAgg,statTimeInQueueAgg,statTimeInQueueIfWaitedAgg,statTimeInWorkerAgg,parent);
  sim.run();
}

void DistributedSimulation::run()
{
  for(size_t index = 0; index < numberOfThreads;++index)
    {
      std::cout << "starting worker " << index << std::endl;
      simulationThreads.emplace_back(startSimulation,_packGen,_workers,_limited,_limit,_earlier,_whichWorker,std::ref(statPacketDropped),
                                     std::ref(statPacketsInWorker), std::ref(statPacketsInQueue), std::ref(statPacketsInSystem),
                                     std::ref(statTimeInSystem), std::ref(statTimeInQueue), std::ref(statTimeInQueueIfWaited),
                                     std::ref(statTimeInWorker),this);

    }

  do
    {
      std::this_thread::sleep_for(std::chrono::seconds(5));
      printStatistics();
    }
  while(!precissionSatisfied());

  for(size_t index = 0; index < numberOfThreads;++index)
    {
      simulationThreads[index].join();
      std::cout << "stopped worker "<< index << std::endl;
    }
  printStatistics();

}
