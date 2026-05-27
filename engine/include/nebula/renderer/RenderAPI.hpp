#pragma once
#include "nebula/renderer/VertexArray.hpp"
#include <glm/glm.hpp> // 建议引入 GLM 处理向量
#include <memory>

namespace nebula
{

class RenderAPI
{
  public:
    // 定义支持的 API 类型
    enum class API
    {
        None = 0,
        OpenGL = 1
    };

  public:
    virtual ~RenderAPI() = default;

    virtual void Init() = 0;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
    virtual void SetClearColor(const glm::vec4& color) = 0;
    virtual void Clear() = 0;

    // 核心：根据 VertexArray 里的索引数量执行绘制
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

    inline static API GetAPI() { return s_API; }

  private:
    static API s_API; // 全局当前的 API 类型
};
} // namespace nebula