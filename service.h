#ifndef SERVICE_H
#define SERVICE_H

#include "vector"
#include "functional"
#include "worker.h"
#include "packet.h"

class Service
{
public:
  Service(std::vector<Worker> worker, std::function<short(std::vector<Worker> &,Packet&)> wWorker);
  bool isWorkerReady(size_t index);
  short whoCanWorkOn(Packet packet);
  Packet finish(size_t index, double currentTime);
  Packet abortPacket(size_t index,double currentTime);
  Event workOn(size_t index, Packet packet, double currentTime);
  size_t countActive();
  size_t countIdle();
  const double maxLambda;
private:
  std::vector<Worker> workers;
  std::function<short(std::vector<Worker> &,Packet&)> whichWorkerFun;

};

#endif // SERVICE_H
