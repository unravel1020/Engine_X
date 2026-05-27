#pragma once

#include "nebula/renderer/RenderAPI.hpp"

namespace nebula
{
class OpenGLRenderAPI : public RenderAPI
{
  public:
    // 初始化 OpenGL 状态（开启混合、深度测试等）
    virtual void Init() override;

    // 设置视口大小
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    // 设置清屏颜色
    virtual void SetClearColor(const glm::vec4& color) override;

    // 执行清屏
    virtual void Clear() override;

    // 具体的绘制指令
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
};
} // namespace nebula