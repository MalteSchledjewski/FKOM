#include "event.h"
#include <utility>

Event::Event(EventType type, double time, size_t ind): eventType(type), time(time), index(ind)
{
}

