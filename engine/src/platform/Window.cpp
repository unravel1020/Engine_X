#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h> // 注意：GLAD 必须在 GLFW 之前包含！

#include "nebula/Window.hpp"
#include "nebula/core/Log.hpp"
#include "nebula/event/ApplicationEvent.hpp"

namespace nebula
{
// 1. 定义具体的实现类 WindowsWindow
class WindowsWindow : public Window
{
  public:
    WindowsWindow(unsigned int width, unsigned int height, const char* title);
    virtual ~WindowsWindow();

    virtual void OnUpdate() override;

    virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

    virtual void* GetNativeWindow() const override { return m_Window; }

  private:
    GLFWwindow* m_Window;

    struct WindowData
    {
        std::string Title;
        unsigned int Width, Height;
        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};

// 2. 静态工厂方法实现
Window* Window::Create(unsigned int width, unsigned int height, const char* title)
{
    return new WindowsWindow(width, height, title);
}

// 3. WindowsWindow 构造函数逻辑
WindowsWindow::WindowsWindow(unsigned int width, unsigned int height, const char* title)
{
    m_Data.Title = title;
    m_Data.Width = width;
    m_Data.Height = height;

    NEBULA_INFO("Creating window {0} ({1}, {2})", title, width, height);

    // --- GLFW 初始化 ---
    static bool s_GLFWInitialized = false;
    if (!s_GLFWInitialized)
    {
        int success = glfwInit();
        if (!success)
        {
            NEBULA_ERROR("Could not initialize GLFW!");
            return;
        }
        s_GLFWInitialized = true;
    }

    // 创建窗口
    m_Window = glfwCreateWindow((int)width, (int)height, m_Data.Title.c_str(), nullptr, nullptr);

    if (!m_Window)
    {
        NEBULA_ERROR("Failed to create GLFW window!");
        return;
    }

    // --- 核心：建立 OpenGL 上下文 ---
    glfwMakeContextCurrent(m_Window);

    // --- 核心：初始化 GLAD ---
    // gladLoadGLLoader 必须在 glfwMakeContextCurrent 之后调用
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!status)
    {
        NEBULA_ERROR("Failed to initialize GLAD!");
        return;
    }

    glfwSetWindowUserPointer(m_Window, &m_Data);

    // 打印显卡驱动信息（现在 GLAD 已初始化，调用这些 gl 函数不会崩溃了）
    NEBULA_INFO("OpenGL Info:");
    NEBULA_INFO("  Vendor:   {0}", (const char*)glGetString(GL_VENDOR));
    NEBULA_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
    NEBULA_INFO("  Version:  {0}", (const char*)glGetString(GL_VERSION));

    // 设置垂直同步 (V-Sync)
    glfwSwapInterval(1);

    // 设置 GLFW 事件回调
    glfwSetWindowCloseCallback(m_Window,
                               [](GLFWwindow* window)
                               {
                                   WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                                   WindowCloseEvent event;
                                   if (data.EventCallback)
                                   {
                                       data.EventCallback(event);
                                   }
                               });
}

// 4. 析构函数
WindowsWindow::~WindowsWindow()
{
    if (m_Window)
    {
        glfwDestroyWindow(m_Window);
    }
    // 只有当所有窗口都关闭时才 terminate，
    // 目前简单处理，直接在析构里关掉 GLFW
    glfwTerminate();
    NEBULA_INFO("Window destroyed");
}

// 5. 更新循环
void WindowsWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

} // namespace nebula