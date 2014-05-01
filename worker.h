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
    Worker& operator= (Worker otherWorker);
    Worker& operator= (Worker&& otherWorker);
    bool isWorking();
    Packet abortPacket();
    Event workOn(Packet packet);
    Packet finish();
    int getCurrentPriority();
    bool isPriorityWorker();
    void setIndex(size_t index);
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
