#include "packetqueue.h"

PacketQueue::PacketQueue(bool limited, size_t limit, std::function<bool(Packet &,Packet &)> earlier): limited(limited),limit(limit),packetQueue{},earlier(earlier)
{
}

std::shared_ptr<Packet> PacketQueue::addPacket(Packet packet, double currentTime) {
  //iterate
  packet.enqueue(currentTime);
  auto iterator = packetQueue.begin();
  while(iterator != packetQueue.end() && (!(earlier(packet,*iterator))))
    {
      ++iterator;
    }
  packetQueue.insert(iterator,packet);
  if(limited && packetQueue.size()>limit)
    {
      Packet packet = packetQueue.back();
      packet.dequeue(currentTime);
      packet.drop();
      packetQueue.pop_back();
      return std::make_shared<Packet>(packet);
    }
  else
    {
      return std::shared_ptr<Packet>();
    }

}

Packet PacketQueue::getNextPacket(double currentTime) {
  Packet packet = packetQueue.front();
  packet.dequeue(currentTime);
  packetQueue.pop_front();
  return packet;
}

bool PacketQueue::hasWork() {
  return !packetQueue.empty();
}

bool PacketQueue::canTake(Packet packet) {
  return !limited || (packetQueue.size() < limit) || (limit != 0 && earlier(packet,packetQueue.back()));
}

size_t PacketQueue::numberOfPacketsInQueue()
{
  return packetQueue.size();
}
