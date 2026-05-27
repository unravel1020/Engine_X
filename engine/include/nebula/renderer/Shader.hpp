#pragma once
#include <cstdint>
#include <glm/glm.hpp>
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

    void SetMat4(const std::string& name, const glm::mat4& matrix) const; // 设置 4x4 矩阵 uniform

  private:
    uint32_t m_RendererID; // GPU 给我们的程序 ID
};
} // namespace nebula