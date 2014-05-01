#include "worker.h"

Worker::Worker(double lambda, bool isPriority) :priorityWorker(isPriority),working(false),currentPacket(Priority::LOW,0),rd(),gen(rd()),dist(lambda),index(-1)
{
}


Worker::Worker(const Worker& otherWorker) : priorityWorker(otherWorker.priorityWorker),working(otherWorker.working),currentPacket(otherWorker.currentPacket),rd(),gen(otherWorker.gen),dist(otherWorker.dist),index(-1) {

}

Worker::Worker(Worker&& otherWorker) : priorityWorker(otherWorker.priorityWorker),working(otherWorker.working),currentPacket(otherWorker.currentPacket),rd(),gen(otherWorker.gen),dist(otherWorker.dist),index(-1) {

}


Worker& Worker::operator= (Worker otherWorker) {
    priorityWorker = otherWorker.priorityWorker;
    working = otherWorker.working;
    currentPacket = otherWorker.currentPacket;
    gen = otherWorker.gen;
    dist = otherWorker.dist;
    index = otherWorker.index;
    return *this;
}

Worker& Worker::operator= (Worker&& otherWorker) {
    priorityWorker = otherWorker.priorityWorker;
    working = otherWorker.working;
    currentPacket = otherWorker.currentPacket;
    gen = otherWorker.gen;
    dist = otherWorker.dist;
    index = otherWorker.index;
    return *this;
}


bool Worker::isWorking() {
    return working;
}

Packet Worker::abortPacket() {
    working = false;
    return currentPacket;
}

Packet Worker::finish() {
    working = false;
    return currentPacket;
}

int Worker::getCurrentPriority() {
    return currentPacket.getPriority();
}

bool Worker::isPriorityWorker() {
    return priorityWorker;
}

Event Worker::workOn(Packet packet) {
    currentPacket = packet;
    working = true;
    Event event(EventType::PACKET_FINISHED,packet.getBeginOfState()+dist(gen),index);
    return event;
}

void Worker::setIndex(size_t index) {
    this->index = index;
}
