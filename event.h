#ifndef EVENT_H
#define EVENT_H
#include <cstdlib>

enum EventType {
    NEW_PACKET, PACKET_FINISHED, COUNT
};

class Event
{
public:
    Event(EventType type, double time, std::size_t ind);
    Event(const Event& otherEvent) = default;
    Event(Event&& otherEvent) = default;
    Event& operator= (const Event& otherEvent) = default;
    Event& operator= (Event&& otherEvent) = default;
    EventType eventType;
    double time;
    std::size_t index;
};

#endif // EVENT_H
