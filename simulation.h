#ifndef SIMULATION_H
#define SIMULATION_H

#include "vector"
#include "memory"
#include "functional"


#include "worker.h"
#include "service.h"
#include "packetgenerator.h"
#include "packetqueue.h"
#include "packet.h"
#include "event.h"
#include "eventqueue.h"
#include "statisticsaggregate.h"
#include "statisticsagent.h"

class DistributedSimulation;

class Simulation
{

public:
    Simulation(std::vector<PacketGenerator> packGen, std::vector<Worker> workers,
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
               DistributedSimulation *parent);
    void run();


private:
    DistributedSimulation* _parent;
    EventQueue eventQueue;
    std::vector<PacketGenerator> packetGenerators;
    PacketQueue packetQueue;
    Service service;

    StatisticsAgent statPacketDropped;
    StatisticsAgent statPacketsInWorker;
    StatisticsAgent statPacketsInQueue;
    StatisticsAgent statPacketsInSystem;
    StatisticsAgent statTimeInSystem;
    StatisticsAgent statTimeInQueue;
    StatisticsAgent statTimeInQueueIfWaited;
    StatisticsAgent statTimeInWorker;


    Event getNextEvent(); // get event from eventQueue
    Event createNextNewPacketEvent(size_t index, double time); // create the new event for the next package
    void registerEvent(Event event); // register the event in the eventQueue
    Packet getNewPacket(Event event); // get the new packet
    void removePacketEvent(size_t index);
    Packet abortWorker(size_t index, double currentTime);
    Packet finishWorker(size_t index, double currentTime);
    short whoCanWorkOnPacket(Packet packet); //check whether a worker could abort the current packet for the new one - -1 for not possible
    Event workOnPacket(size_t index, Packet packet, double currentTime); // send the packet to the service
    bool queueCanTake(Packet packet);
    std::shared_ptr<Packet> enqueue(Packet packet, double currentTime);
    std::shared_ptr<Packet> assign(Packet packet, double currentTime);
    Packet getNextFromQueue(double currentTime);
};

#endif // SIMULATION_H
