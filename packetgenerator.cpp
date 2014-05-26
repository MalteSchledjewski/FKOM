#include "packetgenerator.h"

PacketGenerator::PacketGenerator(double lambda,Priority priority):lambda(lambda),priority(priority),rd(),gen(rd()),dist(lambda)
{
}


PacketGenerator::PacketGenerator(const PacketGenerator& otherPacketGenerator):lambda(otherPacketGenerator.lambda),priority(otherPacketGenerator.priority),rd(),gen(otherPacketGenerator.gen),dist(otherPacketGenerator.dist) {

}

PacketGenerator::PacketGenerator(PacketGenerator&& otherPacketGenerator):lambda(otherPacketGenerator.lambda),priority(otherPacketGenerator.priority),rd(),gen(otherPacketGenerator.gen),dist(otherPacketGenerator.dist) {

}

//PacketGenerator& PacketGenerator::operator= (PacketGenerator otherPacketGenerator) {
//    priority = otherPacketGenerator.priority;
//    gen = otherPacketGenerator.gen;
//    dist = otherPacketGenerator.dist;
//    return *this;
//}

//PacketGenerator& PacketGenerator::operator= (PacketGenerator&& otherPacketGenerator) {
//    priority = otherPacketGenerator.priority;
//    gen = otherPacketGenerator.gen;
//    dist = otherPacketGenerator.dist;
//    return *this;
//}


Packet PacketGenerator::getPacket(double time) {
    return Packet(priority,time);
}

Event PacketGenerator::getNextPacketEvent(double time,size_t index) {
    return Event(EventType::NEW_PACKET,time + dist(gen),index);
}
