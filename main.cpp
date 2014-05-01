#include "distributedsimulation.h"
#include "erlangc.h"

#include <iostream>
#include <thread>
bool earlier(Packet& a, Packet& b){
  return a.getArrivalTime() < b.getArrivalTime();
}

short whichFree(std::vector<Worker>& workers,Packet& packet)
{
  for(short i=0;i<workers.size();++i)
    {
      if(! workers[i].isWorking())
        {
          return i;
        }
    }
  return -1;
}

int main()
{
  std::cout << std::thread::hardware_concurrency() << std::endl;
  PacketGenerator packGen = PacketGenerator(80.0/60,Priority::LOW);
  std::vector<PacketGenerator> vecPackGen = {packGen};
//  vecPackGen.insert(packGen);
  Worker worker = Worker(2);
  std::vector<Worker> vecWorker = {worker};
//  vecWorker.insert(worker);
  std::function<bool(Packet&, Packet&)> earlierFun = earlier;
  std::function<short(std::vector<Worker>&,Packet&)> which = whichFree;
  DistributedSimulation sim(vecPackGen,vecWorker,false,1,earlierFun,which,0.0001);
  sim.run();
  ErlangC stats(80.0/60,2,1);
  std::cout << "dropped\t Nqueue\t  N\t   Nwork    Tqueue   Tqonly   T\t\tTwork\n" <<
               std::fixed << stats.statPacketDropped <<" " <<
               std::fixed << stats.statPacketsInQueue <<" " <<
               std::fixed << stats.statPacketsInSystem <<" " <<
               std::fixed << stats.statPacketsInWorker <<" " <<
               std::fixed << stats.statTimeInQueue <<" " <<
               std::fixed << stats.statTimeInQueueIfWaited <<" " <<
               std::fixed << stats.statTimeInSystem <<" " <<
               std::fixed << stats.statTimeInWorker <<"\n" <<
               std::endl;
  return 0;
}
