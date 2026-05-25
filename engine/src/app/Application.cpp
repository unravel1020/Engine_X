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
    m_Window->SetEventCallback(
        [this](Event& event)
        {
            EventDispatcher dispatcher(event);

            dispatcher.Dispatch<WindowCloseEvent>(
                [this](WindowCloseEvent&)
                {
                    m_Running = false;

                    return true;
                });

            for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
            {
                (*--it)->OnEvent(event);

                if (event.Handled)
                {
                    break;
                }
            }

            NEBULA_INFO("Event: {}", event.GetName());
        });

    NEBULA_INFO("Application created");
}

void Application::Run()
{
    float m_LastFrameTime = (float)glfwGetTime();
    while (m_Running)
    {
        // 1. calculate timestep
        float time = (float)glfwGetTime();
        Timestamp timestamp = time - m_LastFrameTime;
        m_LastFrameTime = time;
        // 2. update layers with timestamp
        for (Layer* layer : m_LayerStack)
        {
            layer->OnUpdate(timestamp);
        }

        m_Window->OnUpdate();
    }
}

void Application::PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

Application::~Application() {}
} // namespace nebula