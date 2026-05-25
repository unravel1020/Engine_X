#pragma once
#include <cstdint>
#include <string>


namespace nebula
{
class Shader
{
  public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;   // 使用该着色器
    void Unbind() const; // 停用

  private:
    uint32_t m_RendererID; // GPU 给我们的程序 ID
};
} // namespace nebula