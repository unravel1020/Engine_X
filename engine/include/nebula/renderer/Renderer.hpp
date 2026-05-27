#include "nebula/renderer/OrthographicCamera.hpp"

#include "nebula/renderer/Shader.hpp"
#include "nebula/renderer/VertexArray.hpp"
#include <glm/glm.hpp>

namespace nebula
{
class Renderer
{
  public:
    // 开始渲染场景，存下摄像机的矩阵
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    // 提交绘制物体
    static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

  private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };
    static SceneData* s_SceneData;
};
} // namespace nebula