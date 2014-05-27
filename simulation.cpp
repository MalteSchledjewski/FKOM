#include "simulation.h"
#include "distributedsimulation.h"
#include <iostream>

Simulation::Simulation(std::vector<PacketGenerator> packGen, std::vector<Worker> workers,
                       bool limited, size_t limit,
                       std::function<bool(Packet&,Packet&)> earlier, std::function<short(std::vector<Worker>&,Packet&)> whichWorker,
                       StatisticsAggregate &statPacketDroppedAgg, StatisticsAggregate &statMoreThanNPacketsAgg,
                       StatisticsAggregate& statPacketsInWorkerAgg,
                       StatisticsAggregate& statPacketsInQueueAgg,
                       StatisticsAggregate& statPacketsInSystemAgg,
                       StatisticsAggregate& statTimeInSystemAgg,
                       StatisticsAggregate& statTimeInQueueAgg,
                       StatisticsAggregate& statTimeInQueueIfWaitedAgg,
                       StatisticsAggregate& statTimeInWorkerAgg, StatisticsAggregate &statFinishedWithoutWaitingAgg, size_t thresh,
                       DistributedSimulation& parent):
  _parent(parent),eventQueue(),packetGenerators(packGen),packetQueue(limited,limit,earlier),service(workers,whichWorker),threshold(thresh),
  statPacketDropped(statPacketDroppedAgg),statMoreThanNPackets(statMoreThanNPacketsAgg),
  statPacketsInWorker(statPacketsInWorkerAgg),statPacketsInQueue(statPacketsInQueueAgg),statPacketsInSystem(statPacketsInSystemAgg),
  statTimeInSystem(statTimeInSystemAgg),statTimeInQueue(statTimeInQueueAgg),statTimeInQueueIfWaited(statTimeInQueueIfWaitedAgg),
  statTimeInWorker(statTimeInWorkerAgg),statFinishedWithoutWaiting(statFinishedWithoutWaitingAgg),statisticsEventGenerator([&]()->double{
                                                                                                                           double maxLam = service.maxLambda;
                                                                                                                           for(size_t i = 0; i< packetGenerators.size();++i)
{
  if(packetGenerators[i].lambda > maxLam)
    {
      maxLam = packetGenerators[i].lambda;
    }
}
return 2*maxLam;
}())
{
for(size_t i = 0; i< packetGenerators.size();++i)
{
  Event event = Event(EventType::NEW_PACKET,0,i);
  eventQueue.addEvent(event);
}
Event event = Event(EventType::COUNT,0,0);
eventQueue.addEvent(event);
}

Packet Simulation::getNewPacket(Event event) {
  Packet newPacket = packetGenerators[event.index].getPacket(event.time);
  Event newPacketEvent = createNextNewPacketEvent(event.index,event.time);
  registerEvent(newPacketEvent);
  return newPacket;
}

Event Simulation::getNextEvent() {
  return eventQueue.getNextEvent();
}

Event Simulation::createNextNewPacketEvent(size_t index, double time) {
  return packetGenerators[index].getNextPacketEvent(time, index);
}

void Simulation::registerEvent(Event event) {
  eventQueue.addEvent(event);
}

void Simulation::removePacketEvent(size_t index) {
  eventQueue.resetWorker(index);
}

Packet Simulation::abortWorker(size_t index,double currentTime) {
  removePacketEvent(index);
  return service.abortPacket(index,currentTime);
}

Packet Simulation::finishWorker(size_t index, double currentTime) {
  return service.finish(index,currentTime);
}

short Simulation::whoCanWorkOnPacket(Packet packet) {
  return service.whoCanWorkOn(packet);
}

Event Simulation::workOnPacket(size_t index, Packet packet, double currentTime) {
  return service.workOn(index,packet,currentTime);
}

bool Simulation::queueCanTake(Packet packet) {
  return packetQueue.canTake(packet);
}

std::shared_ptr<Packet> Simulation::enqueue(Packet packet, double currentTime) {
  return packetQueue.addPacket(packet,currentTime);
}

void Simulation::logDroppedPacket(double currentTime, std::shared_ptr<Packet> lostPacket)
{
  statPacketDropped.log(1.0);
  statFinishedWithoutWaiting.log(0.0);
  if(currentTime != lostPacket->getArrivalTime())
    {
      double timeInWorker = lostPacket->getTimeInWorker();
      double timeInQueue = lostPacket->getTimeInQueue();
      statTimeInSystem.log(timeInWorker + timeInQueue);
      statTimeInQueue.log(timeInQueue);
      if(timeInQueue != 0.0)
        {
          statTimeInQueueIfWaited.log(timeInQueue);
        }
      statTimeInWorker.log(timeInWorker);
    }
}

void Simulation::logFinishedPacket(Packet finishedPacket)
{
  {
    statPacketDropped.log(0.0);
    double timeInWorker = finishedPacket.getTimeInWorker();
    double timeInQueue = finishedPacket.getTimeInQueue();
    statTimeInSystem.log(timeInWorker + timeInQueue);
    statTimeInQueue.log(timeInQueue);
    if(timeInQueue != 0.0)
      {
        statTimeInQueueIfWaited.log(timeInQueue);
        statFinishedWithoutWaiting.log(0.0);
      }
    else
      {
        statFinishedWithoutWaiting.log(1.0);
      }
    statTimeInWorker.log(timeInWorker);
  }
}

void Simulation::logCount()
{
  double packetsInWorker = service.countActive();
  double packetsInQueue = packetQueue.numberOfPacketsInQueue();
  if(packetsInQueue < threshold)
    {
      statMoreThanNPackets.log(0.);
    }
  else
    {
      statMoreThanNPackets.log(1.);
    }
  statPacketsInWorker.log(packetsInWorker);
  statPacketsInQueue.log(packetsInQueue);
  statPacketsInSystem.log(packetsInQueue + packetsInWorker);
}

void Simulation::handleNewPacketEvent(double currentTime, Event event)
{
  Packet packet = getNewPacket(event);
  short workerIndex = whoCanWorkOnPacket(packet);
  if(workerIndex == -1)
    {
      std::shared_ptr<Packet> lostPacket = enqueue(packet,currentTime);
      if(lostPacket != nullptr)
        {
          logDroppedPacket(currentTime, lostPacket);
        }
    }
  else
    {
      if(!service.isWorkerReady(workerIndex))
        {
          Packet oldPacket = abortWorker(workerIndex,currentTime);
          Event packetFinishedEvent = workOnPacket(workerIndex,packet,currentTime);
          registerEvent(packetFinishedEvent);
          std::shared_ptr<Packet> packetPointer = assign(oldPacket,currentTime);
          if(packetPointer!=nullptr)
            {
              oldPacket = *packetPointer;
              std::shared_ptr<Packet> lostPacket = enqueue(oldPacket,currentTime);
              if(lostPacket != nullptr)
                {
                  logDroppedPacket(currentTime, lostPacket);
                }
            }
        }
      else
        {
          Event packetFinishedEvent = workOnPacket(workerIndex,packet,currentTime);
          registerEvent(packetFinishedEvent);
        }
    }
}

void Simulation::handlePacketFinishedEvent(Event event, double currentTime)
{
  Packet finishedPacket = finishWorker(event.index,currentTime);
  logFinishedPacket(finishedPacket);
  if(packetQueue.hasWork())
    {
      Packet nextPacket = getNextFromQueue(currentTime);
      if(whoCanWorkOnPacket(nextPacket) == event.index)
        {
          Event nextEvent = workOnPacket(event.index,nextPacket,currentTime);
          registerEvent(nextEvent);
        }
      else
        {
          enqueue(nextPacket,currentTime);
        }
    }
}

void Simulation::handleCountEvent(Event event)
{
  logCount();
  Event newEvent = statisticsEventGenerator.getNextStatisticsEvent(event.time);
  registerEvent(newEvent);
}

void Simulation::run() {
  do {
      for(size_t numberOfIterations = 0;numberOfIterations<10000000;++numberOfIterations) {
          Event event = getNextEvent();
          double currentTime = event.time;
          if(event.eventType == EventType::NEW_PACKET)
            {
              handleNewPacketEvent(currentTime, event);
            }
          else {
              if(event.eventType == EventType::PACKET_FINISHED)
                {
                  handlePacketFinishedEvent(event, currentTime);
                }
              else
                {
                  handleCountEvent(event);
                }
            }
        }
    } while(!_parent.precissionSatisfied());
}

Packet Simulation::getNextFromQueue(double currentTime)
{
  return packetQueue.getNextPacket(currentTime);
}


std::shared_ptr<Packet> Simulation::assign(Packet packet,double currentTime)
{
  short workerIndex = whoCanWorkOnPacket(packet);
  if(workerIndex == -1)
    {
      return std::make_shared<Packet>(packet);
    }
  if(service.isWorkerReady(workerIndex))
    {
      Event packetFinishedEvent = workOnPacket(workerIndex,packet,currentTime);
      registerEvent(packetFinishedEvent);
    }
  else
    {
      Packet oldPacket = abortWorker(workerIndex,currentTime);
      Event packetFinishedEvent = workOnPacket(workerIndex,packet,currentTime);
      registerEvent(packetFinishedEvent);
      return assign(oldPacket,currentTime);
    }
  return std::shared_ptr<Packet>();
}
