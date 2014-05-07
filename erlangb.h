#ifndef ERLANGB_H
#define ERLANGB_H

class ErlangB
{
public:
  ErlangB(double lambda, double m, int numberOfWorkers);
  const double statPacketDropped;
  const double statFinishedWithoutWaiting;
  const double statPacketsInWorker;
  const double statTimeInWorker;
  const double statPacketsInQueue;
  const double statTimeInQueue;
  const double statTimeInQueueIfWaited;
  const double statPacketsInSystem;
  const double statTimeInSystem;
  void printStatistics();
};



#endif // ERLANGB_H
