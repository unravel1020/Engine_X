#pragma once

#include <string>

#include "nebula/core/Timestep.hpp"
#include "nebula/event/Event.hpp"

namespace nebula
{

class Layer
{
  public:
    Layer(const std::string& name = "Layer") : m_DebugName(name) {}

    virtual ~Layer() = default;

    virtual void OnAttach() {}

    virtual void OnDetach() {}

    virtual void OnUpdate(Timestep timestep) {}

    virtual void OnEvent(Event& event) {}

    const std::string& GetName() const { return m_DebugName; }

  protected:
    std::string m_DebugName;
};

} // namespace nebula