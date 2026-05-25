#include "nebula/core/Log.hpp"
#include "nebula/renderer/GraphicsContext.hpp"

// 在包含 GLFW 之前定义这个宏
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// 此时 glad 放在哪里都可以，格式化插件随便排
#include <glad/glad.h>

namespace nebula
{
class OpenGLContext : public GraphicsContext
{
  public:
    OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {}

    virtual void Init() override
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!status)
            NEBULA_ERROR("Failed to initialize GLAD!");

        NEBULA_INFO("OpenGL Info:");
        NEBULA_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        NEBULA_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        NEBULA_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    virtual void SwapBuffers() override { glfwSwapBuffers(m_WindowHandle); }

  private:
    GLFWwindow* m_WindowHandle;
};
} // namespace nebula