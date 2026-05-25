#include "nebula/renderer/Shader.hpp"
#include "nebula/core/Log.hpp"
#include <glad/glad.h>
#include <vector>


namespace nebula
{
Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vSrc = vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &vSrc, 0);
    glCompileShader(vertexShader);

    // 错误检查
    int isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        int maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        NEBULA_ERROR("Vertex Shader Compilation Failed: {0}", infoLog.data());
        glDeleteShader(vertexShader);
        return;
    }

    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fSrc = fragmentSrc.c_str();
    glShaderSource(fragmentShader, 1, &fSrc, 0);
    glCompileShader(fragmentShader);

    // 链接程序
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);
    glLinkProgram(m_RendererID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(m_RendererID); }
void Shader::Bind() const { glUseProgram(m_RendererID); }
void Shader::Unbind() const { glUseProgram(0); }
} // namespace nebula