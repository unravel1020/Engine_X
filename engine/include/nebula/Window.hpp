#pragma once

#include "event/Event.hpp"
#include "renderer/GraphicsContext.hpp"
#include <functional>
#include <memory>


namespace nebula
{
class Window
{
  public:
    using EventCallbackFn = std::function<void(Event&)>;

    // 1. 虚析构函数：确保删除指针时能调用到子类的析构函数
    virtual ~Window() {}

    // 2. 将所有操作声明为纯虚函数 (= 0)
    virtual void OnUpdate() = 0;
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void* GetNativeWindow() const = 0;

    // 3. 静态工厂方法：这是外部（Application）创建窗口的唯一途径
    static Window* Create(unsigned int width = 1280, unsigned int height = 720, const char* title = "Nebula Engine");

    std::unique_ptr<GraphicsContext> m_Context;

  protected:
    // 构造函数设为 protected，防止外部直接实例化 Window 对象
    Window() = default;
};

} // namespace nebula