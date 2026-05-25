#pragma once

#include "Window.hpp"
#include "core/LayerStack.hpp"
#include <memory>

namespace nebula
{
class Application
{
  public:
    Application();
    virtual ~Application(); // 记得加析构

    void Run();
    void PushLayer(Layer* layer);

    // 新增：获取原生窗口的接口
    inline Window& GetWindow() { return *m_Window; }

    // 新增：全局访问单例
    inline static Application& Get() { return *s_Instance; }

  private:
    bool m_Running = true;
    std::unique_ptr<Window> m_Window;
    LayerStack m_LayerStack;

    static Application* s_Instance; // 静态实例指针
};
} // namespace nebula