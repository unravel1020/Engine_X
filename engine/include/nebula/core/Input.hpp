#pragma once

#include "nebula/core/KeyCodes.hpp"
#include <glm/glm.hpp>
namespace nebula
{
class Input
{
  public:
    static bool IsKeyPressed(KeyCode key);
    static bool IsMouseButtonPressed(int button);
    static glm::vec2 GetMousePosition();
};
} // namespace nebula