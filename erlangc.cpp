#include "erlangc.h"

#include <cmath>

ErlangC::ErlangC(double lambda, double m, int numberOfWorkers) :
  statPacketDropped(0),statPacketsInWorker(lambda/m),statTimeInWorker(1/m),
  statPacketsInQueue([&lambda,&m,&numberOfWorkers]()->double{
                     double a = lambda/m;
                     double upper = (std::pow(a,numberOfWorkers))/(std::tgammal(numberOfWorkers+1))*((numberOfWorkers)/(numberOfWorkers-a));
                     double lower1 = 0;
                     for(int i = 0;i< numberOfWorkers;++i)
{
  lower1+= std::pow(a,i)/std::tgammal(i+1);
}
return upper/(lower1+upper);
}() * (lambda/m/(numberOfWorkers-lambda/m))),
statTimeInQueue(statPacketsInQueue/lambda),statTimeInQueueIfWaited((lambda/m/(numberOfWorkers-lambda/m))/lambda),
statPacketsInSystem(statPacketsInQueue+statPacketsInWorker),statTimeInSystem(statTimeInQueue+statTimeInWorker)
{

}
