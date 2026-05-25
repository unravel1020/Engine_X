#pragma once

#include "Event.hpp"

namespace nebula
{

class WindowCloseEvent : public Event
{
  public:
    EventType GetEventType() const override { return EventType::WindowClose; }

    const char* GetName() const override { return "WindowClose"; }
};

} // namespace nebula