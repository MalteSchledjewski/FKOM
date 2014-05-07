#ifndef PACKETQUEUE_H
#define PACKETQUEUE_H

#include "deque"
#include "functional"
#include "memory"

#include "packet.h"

class PacketQueue
{
public:
    PacketQueue(bool limited, size_t limit,std::function<bool(Packet&,Packet&)> earlier);
    std::shared_ptr<Packet> addPacket(Packet packet, double currentTime);
    Packet getNextPacket(double currentTime);
    bool hasWork();
    bool canTake(Packet packet);
    size_t numberOfPacketsInQueue();
private:
    const bool limited;
    const size_t limit;
    std::deque<Packet> packetQueue;
    std::function<bool(Packet&,Packet&)> earlier;
};

#endif // PACKETQUEUE_H
