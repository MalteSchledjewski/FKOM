#include "distributedsimulation.h"

#include <iostream>
#include <chrono>

DistributedSimulation::DistributedSimulation(std::vector<PacketGenerator> packGen, std::vector<Worker> workers,
                                             bool limited, size_t limit, std::function<bool(Packet&,Packet&)> earlier,
                                             std::function<short(std::vector<Worker>&, Packet&)> whichWorker,size_t thresh, const double precision) :
  precission(precision),statPacketDropped(precision),statMoreThanNPackets(precision),statPacketsInWorker(precision),statPacketsInQueue(precision),
  statPacketsInSystem(precision),statTimeInSystem(precision),statTimeInQueue(precision),statTimeInQueueIfWaited(precision),
  statTimeInWorker(precision),statFinishedWithoutWating(precision),simulationThreads(),threshold(thresh),_packGen(packGen),_workers(workers),_limited(limited),_limit(limit),
  _earlier(earlier),_whichWorker(whichWorker)
{
  simulationThreads.reserve(numberOfThreads);

}

void DistributedSimulation::printStatistics()
{
  std::cout << "dropped   P>n     Nqueue   Nsystem  Nwork    Tqueue   Tqonly   Tsystem  Twork    P!waited\n" <<
               std::fixed << statPacketDropped.getStandardDeviation() <<" " <<
               std::fixed << statMoreThanNPackets.getStandardDeviation() <<" " <<
               std::fixed << statPacketsInQueue.getStandardDeviation() <<" " <<
               std::fixed << statPacketsInSystem.getStandardDeviation() <<" " <<
               std::fixed << statPacketsInWorker.getStandardDeviation() <<" " <<
               std::fixed << statTimeInQueue.getStandardDeviation() <<" " <<
               std::fixed << statTimeInQueueIfWaited.getStandardDeviation() <<" " <<
               std::fixed << statTimeInSystem.getStandardDeviation() <<" " <<
               std::fixed << statTimeInWorker.getStandardDeviation()<<" " <<
               std::fixed << statFinishedWithoutWating.getStandardDeviation() << "\n" <<
               std::fixed << statPacketDropped.getExpectedValue() <<" " <<
               std::fixed << statMoreThanNPackets.getExpectedValue() <<" " <<
               std::fixed << statPacketsInQueue.getExpectedValue() <<" " <<
               std::fixed << statPacketsInSystem.getExpectedValue() <<" " <<
               std::fixed << statPacketsInWorker.getExpectedValue() <<" " <<
               std::fixed << statTimeInQueue.getExpectedValue() <<" " <<
               std::fixed << statTimeInQueueIfWaited.getExpectedValue() <<" " <<
               std::fixed << statTimeInSystem.getExpectedValue() <<" " <<
               std::fixed << statTimeInWorker.getExpectedValue()<<" " <<
               std::fixed << statFinishedWithoutWating.getExpectedValue() <<"\n" <<
               std::endl;

  //TODO


}


bool DistributedSimulation::precissionSatisfied()
{
  return statPacketDropped.precissionSatisfied() &&
      statMoreThanNPackets.precissionSatisfied() &&
      statPacketsInQueue.precissionSatisfied() &&
      statPacketsInSystem.precissionSatisfied() &&
      statPacketsInWorker.precissionSatisfied() &&
      statTimeInQueue.precissionSatisfied() &&
      statTimeInQueueIfWaited.precissionSatisfied() &&
      statTimeInSystem.precissionSatisfied() &&
      statTimeInWorker.precissionSatisfied() &&
      statFinishedWithoutWating.precissionSatisfied();
}


void startSimulation(std::vector<PacketGenerator> packGen, std::vector<Worker> workers,
                     bool limited, size_t limit, std::function<bool(Packet&,Packet&)> earlier,
                     std::function<short(std::vector<Worker>&, Packet&)> whichWorker,
                     StatisticsAggregate& statPacketDroppedAgg,
                     StatisticsAggregate& statMoreThanNPacketsAgg,
                     StatisticsAggregate& statPacketsInWorkerAgg,
                     StatisticsAggregate& statPacketsInQueueAgg,
                     StatisticsAggregate& statPacketsInSystemAgg,
                     StatisticsAggregate& statTimeInSystemAgg,
                     StatisticsAggregate& statTimeInQueueAgg,
                     StatisticsAggregate& statTimeInQueueIfWaitedAgg,
                     StatisticsAggregate& statTimeInWorkerAgg,
                     StatisticsAggregate& statFinishedWithoutWaitingAgg,
                     size_t threshold,
                     DistributedSimulation& parent)
{
  Simulation sim(packGen,workers,limited,limit,earlier,whichWorker,statPacketDroppedAgg,statMoreThanNPacketsAgg,statPacketsInWorkerAgg,statPacketsInQueueAgg,
                 statPacketsInSystemAgg,statTimeInSystemAgg,statTimeInQueueAgg,statTimeInQueueIfWaitedAgg,statTimeInWorkerAgg,statFinishedWithoutWaitingAgg,threshold,parent);
  sim.run();
}

void DistributedSimulation::run()
{
  for(size_t index = 0; index < numberOfThreads;++index)
    {
      std::cout << "starting worker " << index << std::endl;
      simulationThreads.emplace_back(startSimulation,_packGen,_workers,_limited,_limit,_earlier,_whichWorker,std::ref(statPacketDropped),
                                     std::ref(statMoreThanNPackets),
                                     std::ref(statPacketsInWorker), std::ref(statPacketsInQueue), std::ref(statPacketsInSystem),
                                     std::ref(statTimeInSystem), std::ref(statTimeInQueue), std::ref(statTimeInQueueIfWaited),
                                     std::ref(statTimeInWorker),std::ref(statFinishedWithoutWating),threshold,std::ref(*this));

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
