#include "packet.h"
#include <cassert>

Packet::Packet(Priority priority, double currentTime):priority(priority),state(State::ARRIVING),timesAborted(0),timeArrival(currentTime),timeInQueue(0),timeInWorker(0),inThisStateSince(currentTime)
{
}

Priority Packet::getPriority()
{
  return priority;
}

void Packet::abort(double currentTime)
{
  assert(state==State::WORKER);
  timeInWorker += currentTime - inThisStateSince;
  inThisStateSince = currentTime;
  ++timesAborted;
  state = State::UNKNOWN;
}

void Packet::work(double currentTime)
{
  assert(state==State::ARRIVING || state==State::UNKNOWN);
  inThisStateSince = currentTime;
  state = State::WORKER;
}

void Packet::enqueue(double currentTime)
{
  assert(state==State::ARRIVING || state==State::UNKNOWN);
  inThisStateSince = currentTime;
  state = State::QUEUE;
}

void Packet::dequeue(double currentTime)
{
  assert(state==State::QUEUE);
  timeInQueue += currentTime - inThisStateSince;
  inThisStateSince = currentTime;
  state = State::UNKNOWN;
}

void Packet::finish(double currentTime)
{
  assert(state==State::WORKER);
  timeInWorker += currentTime - inThisStateSince;
  inThisStateSince = currentTime;
  state = State::FINISHED;
}

double Packet::getArrivalTime()
{
  return timeArrival;
}

short Packet::getNumberAborted()
{
  return timesAborted;
}

double Packet::getTimeInQueue()
{
  return timeInQueue;
}

double Packet::getTimeInWorker()
{
  return timeInWorker;
}
void Packet::drop()
{
  assert(state == State::UNKNOWN);
  state = State::DROPED;
}

double Packet::getBeginOfState()
{
  return inThisStateSince;
}
