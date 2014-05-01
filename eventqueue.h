#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H


#include "deque"
#include "event.h"


class EventQueue
{
public:
    EventQueue();
    void addEvent(Event newEvent);
    Event getNextEvent();
    void resetWorker(std::size_t ind);
private:
    std::deque<Event> eventQueue;
};

#endif // EVENTQUEUE_H
