#include "erlangc.h"

#include <cmath>
#include <iostream>

ErlangC::ErlangC(double lambda, double m, int numberOfWorkers) :
  statPacketDropped(0),statPacketsInWorker(lambda/m),statTimeInWorker(1/m),
  statFinishedWithoutWaiting(1.0 - [&lambda,&m,&numberOfWorkers]()->double{
    double a = lambda/m;
    double upper = (std::pow(a,numberOfWorkers))/(std::tgammal(numberOfWorkers+1))*((numberOfWorkers)/(numberOfWorkers-a));
    double lower1 = 0;
    for(int i = 0;i< numberOfWorkers;++i)
{
lower1+= std::pow(a,i)/std::tgammal(i+1);
}
return upper/(lower1+upper);
}()),
  statPacketsInQueue((1.0-statFinishedWithoutWaiting) * (lambda/m/(numberOfWorkers-lambda/m))),
statTimeInQueue(statPacketsInQueue/lambda),statTimeInQueueIfWaited((lambda/m/(numberOfWorkers-lambda/m))/lambda),
statPacketsInSystem(statPacketsInQueue+statPacketsInWorker),statTimeInSystem(statTimeInQueue+statTimeInWorker)
{

}


void ErlangC::printStatistics()
{
  std::cout << "dropped\t Nqueue\t  N\t   Nwork    Tqueue   Tqonly   T\t\tTwork\n" <<
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
