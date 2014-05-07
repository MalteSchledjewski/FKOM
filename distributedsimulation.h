#ifndef DISTRIBUTEDSIMULATION_H
#define DISTRIBUTEDSIMULATION_H

#include <thread>
#include <vector>
#include <functional>

#include "simulation.h"
#include "statisticsaggregate.h"
#include "packetgenerator.h"
#include "worker.h"
#include "packet.h"

class DistributedSimulation
{
public:
  DistributedSimulation(std::vector<PacketGenerator> packGen,std::vector<Worker> workers,
                        bool limited, size_t limit,std::function<bool(Packet&,Packet&)> earlier,
                        std::function<short(std::vector<Worker>&, Packet&)> whichWorker,size_t thresh,const double precision = 0.0001);
  void run();
  bool precissionSatisfied();
  void printStatistics();
private:
  const double precission;
  const size_t numberOfThreads {std::thread::hardware_concurrency()};
  StatisticsAggregate statPacketDropped;
  StatisticsAggregate statMoreThanNPackets;
  StatisticsAggregate statPacketsInWorker;
  StatisticsAggregate statPacketsInQueue;
  StatisticsAggregate statPacketsInSystem;
  StatisticsAggregate statTimeInSystem;
  StatisticsAggregate statTimeInQueue;
  StatisticsAggregate statTimeInQueueIfWaited;
  StatisticsAggregate statTimeInWorker;
  StatisticsAggregate statFinishedWithoutWating;
  std::vector<std::thread> simulationThreads;

  size_t threshold;

  std::vector<PacketGenerator> _packGen;
  std::vector<Worker> _workers;
  bool _limited;
  size_t _limit;
  std::function<bool(Packet&,Packet&)> _earlier;
  std::function<short(std::vector<Worker>&, Packet&)> _whichWorker;

//  void startSimulation(std::vector<PacketGenerator> packGen, std::vector<Worker> workers,
//                       bool limited, size_t limit, std::function<bool(Packet&,Packet&)> earlier,
//                       std::function<short(std::vector<Worker>&, Packet&)> whichWorker,
//                       const StatisticsAggregate& statPacketDroppedAgg,
//                       const StatisticsAggregate& statPacketsInWorkerAgg,
//                       const StatisticsAggregate& statPacketsInQueueAgg,
//                       const StatisticsAggregate& statPacketsInSystemAgg,
//                       const StatisticsAggregate& statTimeInSystemAgg,
//                       const StatisticsAggregate& statTimeInQueueAgg,
//                       const StatisticsAggregate& statTimeInQueueIfWaitedAgg,
//                       const StatisticsAggregate& statTimeInWorkerAgg, DistributedSimulation *parent);
};

#endif // DISTRIBUTEDSIMULATION_H
