#ifndef WORKER_H
#define WORKER_H


#include <random>

#include "event.h"
#include "packet.h"

class Worker
{
public:
    Worker(double lambda,bool isPriority = false);
    Worker(const Worker& otherWorker);
    Worker(Worker&& otherWorker);
    Worker& operator= (Worker& otherWorker) = default;
    Worker& operator= (Worker&& otherWorker) = default;
    bool isWorking();
    Packet abortPacket(double currentTime);
    Event workOn(Packet packet,double currentTime);
    Packet finish(double currentTime);
    int getCurrentPriority();
    bool isPriorityWorker();
    void setIndex(size_t index);
    const double lambda;
private:
    bool priorityWorker;
    bool working;
    Packet currentPacket;
    std::random_device rd;
    std::mt19937_64 gen;
    std::exponential_distribution<> dist;
    size_t index;
};

#endif // WORKER_H
