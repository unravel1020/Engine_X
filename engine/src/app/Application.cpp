#include "nebula/Application.hpp"

#include "nebula/core/Layer.hpp"
#include "nebula/core/LayerStack.hpp"
#include "nebula/core/Log.hpp"
#include "nebula/event/ApplicationEvent.hpp"
#include "nebula/event/Event.hpp"
#include <GLFW/glfw3.h>

#include <memory>

namespace nebula
{
Application* Application::s_Instance = nullptr;

Application::Application() : m_Window(Window::Create(1280, 720, "Nebula Engine"))
{
    s_Instance = this;
    m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });

    NEBULA_INFO("Application created");
}

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return OnWindowClose(e); });

    // 将事件传递给 LayerStack 中的每一层
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(event);
        if (event.Handled)
            break;
    }
}

bool Application::OnWindowClose(WindowCloseEvent& event)
{
    m_Running = false;
    return true;
}

void Application::Run()
{
    float m_LastFrameTime = (float)glfwGetTime();
    while (m_Running)
    {
        // 1. calculate timestep
        float time = (float)glfwGetTime();
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;
        // 2. update layers with timestep
        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate(timestep);
        }

        m_Window->OnUpdate();
    }
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

Application::~Application() {}
} // namespace nebula