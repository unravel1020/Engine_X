#pragma once
#include <cstdint>

// 参考 GLFW 的定义
namespace nebula
{
using KeyCode = uint16_t;

namespace Key
{
enum : KeyCode
{
    Space = 32,
    A = 65,
    D = 68,
    S = 83,
    W = 87,
    Left = 263,
    Right = 262,
    Up = 265,
    Down = 264,
    Escape = 256,
    Control = 341,
    Shift = 340
};
}
} // namespace nebula