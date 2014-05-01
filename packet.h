#ifndef PACKET_H
#define PACKET_H


enum Priority {
  LOW=0, HIGH=10
};

enum class State {
  ARRIVING,QUEUE,WORKER,FINISHED,UNKNOWN,DROPED
};

class Packet
{
public:
  Packet(Priority priority, double currentTime);
  Packet(const Packet& otherPacket) = default;
  Packet(Packet&& otherPacket) = default;
  Packet& operator= (const Packet& otherPacket) = default;
  Packet& operator= (Packet&& otherPacket) = default;
  Priority getPriority();
  void abort(double currentTime);
  void enqueue(double currentTime);
  void dequeue(double currentTime);
  void finish(double currentTime);
  void work(double currentTime);
  void drop();
  double getArrivalTime();
  short getNumberAborted();
  double getTimeInQueue();
  double getTimeInWorker();
  double getBeginOfState();
private:
  Priority priority;
  State state;
  short timesAborted;
  double timeArrival;
  double timeInQueue;
  double timeInWorker;
  double inThisStateSince;
};

#endif // PACKET_H
