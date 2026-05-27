#include "nebula/renderer/Renderer.hpp"
#include "nebula/renderer/RenderCommand.hpp"

namespace nebula
{
Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();

void Renderer::BeginScene(OrthographicCamera& camera)
{
    s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
{
    shader->Bind();
    // 自动为当前 Shader 设置 VP 矩阵
    shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Renderer::EndScene() {}
} // namespace nebula