#include "eventqueue.h"

EventQueue::EventQueue():eventQueue()
{
}


void EventQueue::addEvent(Event newEvent) {
    for(auto iter = eventQueue.begin();iter != eventQueue.end(); ++iter) {
        if(newEvent.time < (*iter).time) {
            eventQueue.insert(iter,newEvent);
            return;
        }
    }
    eventQueue.push_back(newEvent);
}

Event EventQueue::getNextEvent() {
    Event event = eventQueue.front();
    eventQueue.pop_front();
    return event;
}

void EventQueue::resetWorker(std::size_t ind) {
    for(auto iter = eventQueue.begin();iter != eventQueue.end(); ++iter) {
        if((*iter).index == ind && (*iter).eventType == EventType::PACKET_FINISHED) {
            eventQueue.erase(iter);
            return;
        }
    }
}
