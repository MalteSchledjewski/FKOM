#ifndef ERLANGC_H
#define ERLANGC_H

class ErlangC
{
public:
  ErlangC(double lambda, double m, int numberOfWorkers);
  const double statPacketDropped;
  const double statPacketsInWorker;
  const double statTimeInWorker;
  const double statPacketsInQueue;
  const double statTimeInQueue;
  const double statTimeInQueueIfWaited;
  const double statPacketsInSystem;
  const double statTimeInSystem;
};

#endif // ERLANGC_H
