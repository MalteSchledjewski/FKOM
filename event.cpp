#include "event.h"
#include <utility>

Event::Event(EventType type, double time, size_t ind): eventType(type), time(time), index(ind)
{
}

//Event::Event(const Event& otherEvent): eventType(otherEvent.eventType), time(otherEvent.time), index(otherEvent.index) {
//}

//Event::Event(Event&& otherEvent): eventType(otherEvent.eventType), time(otherEvent.time), index(otherEvent.index) {
//}

//Event& Event::operator= (const Event& otherEvent) {
//    eventType = otherEvent.eventType;
//    time = otherEvent.time;
//    index = otherEvent.index;
//    return *this;
//}

//Event& Event::operator= (Event&& otherEvent) {
//    eventType = std::move(otherEvent.eventType);
//    time = std::move(otherEvent.time);
//    index = std::move(otherEvent.index);
//    return *this;
//}
