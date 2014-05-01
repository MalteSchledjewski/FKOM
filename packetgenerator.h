#ifndef PACKETGENERATOR_H
#define PACKETGENERATOR_H

#include "random"

#include "event.h"
#include "packet.h"
#include "packetqueue.h"

class PacketGenerator
{
public:
    PacketGenerator(double lambda,Priority priority);
    PacketGenerator(const PacketGenerator& otherPacketGenerator);
    PacketGenerator(PacketGenerator&& otherPacketGenerator);
    PacketGenerator& operator= (PacketGenerator otherPacketGenerator);
    PacketGenerator& operator= (PacketGenerator&& otherPacketGenerator);
    Packet getPacket(double time);
    Event getNextPacketEvent(double time, size_t index);
private:
    Priority priority;
    std::random_device rd;
    std::mt19937_64 gen;
    std::exponential_distribution<> dist;
};

#endif // PACKETGENERATOR_H
