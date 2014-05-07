bool earlier(Packet& a, Packet& b){
  return a.getArrivalTime() < b.getArrivalTime();
}

short whichFree(std::vector<Worker>& workers,Packet& packet)
{
  for(short i=0;i<workers.size();++i)
    {
      if(! workers[i].isWorking())
        {
          return i;
        }
    }
  return -1;
}
