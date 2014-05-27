#include "erlangb.h"

#include <cmath>
#include <iostream>

ErlangB::ErlangB(double lambda, double m, int numberOfWorkers) :
  statPacketDropped([&lambda,&m,&numberOfWorkers]()->double{
    double a = lambda/m;
    double upper = (std::pow(a,numberOfWorkers))/(std::tgammal(numberOfWorkers+1));
    double lower = 0;
    for(int i = 0;i<= numberOfWorkers;++i)
{
lower+= std::pow(a,i)/std::tgammal(i+1);
}
return upper/(lower);
}()),
  statFinishedWithoutWaiting(1.0 - statPacketDropped),
  statPacketsInWorker(lambda/m*statFinishedWithoutWaiting),statTimeInWorker(1/m),
  statPacketsInQueue(0.0),
statTimeInQueue(0.0),statTimeInQueueIfWaited(0.0),
statPacketsInSystem(statPacketsInWorker),statTimeInSystem(statTimeInWorker)
{

}


void ErlangB::printStatistics()
{
  std::cout << "dropped   Nqueue   Nsystem  Nwork    Tqueue   Tqonly   Tsystem  Twork    P!waited\n" <<
             std::fixed << statPacketDropped <<" " <<
             std::fixed << statPacketsInQueue <<" " <<
             std::fixed << statPacketsInSystem <<" " <<
             std::fixed << statPacketsInWorker <<" " <<
             std::fixed << statTimeInQueue <<" " <<
             std::fixed << statTimeInQueueIfWaited <<" " <<
             std::fixed << statTimeInSystem <<" " <<
             std::fixed << statTimeInWorker <<" " <<
             std::fixed << statFinishedWithoutWaiting <<"\n" <<
             std::endl;
}
