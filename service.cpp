#include "service.h"

Service::Service(std::vector<Worker> worker, std::function<short(std::vector<Worker> &,Packet&)> wWorker):
  maxLambda([&]()->double {
      double maxLam = 0;
      for(size_t i = 0; i<worker.size();++i)
        {
          if(worker[i].lambda > maxLam)
            {
              maxLam = worker[i].lambda;
            }
        }
    return maxLam;
  }()),
workers(worker),whichWorkerFun(wWorker)
{
  for(size_t i = 0; i<workers.size();++i)
    {
      workers[i].setIndex(i);
    }
}

bool Service::isWorkerReady(size_t index) {
  return !workers[index].isWorking();
}

short Service::whoCanWorkOn(Packet packet) {
  return whichWorkerFun(workers,packet);
}

Packet Service::finish(size_t index, double currentTime) {
  return workers[index].finish(currentTime);
}

Packet Service::abortPacket(size_t index, double currentTime) {
  return workers[index].abortPacket(currentTime);
}

Event Service::workOn(size_t index, Packet packet,double currentTime) {
  return workers[index].workOn(packet,currentTime);
}

size_t Service::countActive() {
  size_t count = 0;
  for(Worker& worker :  workers) {
      if(worker.isWorking()) {
          ++count;
        }
    }
  return count;
}

size_t Service::countIdle() {
  size_t count = 0;
  for(Worker& worker :  workers) {
      if(!worker.isWorking()) {
          ++count;
        }
    }
  return count;
}
