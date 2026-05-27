#include "nebula/renderer/RenderCommand.hpp"
#include "nebula/renderer/OpenGL/OpenGLRenderAPI.hpp" // 包含具体的实现类

namespace nebula
{
// 简单工厂模式：根据 RenderAPI::GetAPI() 返回对应的实例
// 目前直接 new 一个 OpenGL 实例
// 未来可以根据需要扩展其他 API（如 DirectX、Vulkan 等）
RenderAPI* RenderCommand::s_RendererAPI = new OpenGLRenderAPI();
} // namespace nebula