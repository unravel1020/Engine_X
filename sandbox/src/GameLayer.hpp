#pragma once
#include "nebula/core/Layer.hpp"
#include "nebula/renderer/Buffer.hpp"
#include "nebula/renderer/OrthographicCamera.hpp" // 必须包含摄像机头文件
#include "nebula/renderer/Shader.hpp"
#include "nebula/renderer/VertexArray.hpp"
#include <memory>


class GameLayer : public nebula::Layer
{
  public:
    GameLayer();
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(nebula::Timestep ts) override;
    virtual void OnEvent(nebula::Event& event) override;

  private:
    std::shared_ptr<nebula::Shader> m_Shader;
    std::shared_ptr<nebula::VertexArray> m_VertexArray;

    // --- 新增：声明摄像机 ---
    // 假设窗口比例是 16:9，设置范围为左 -1.6, 右 1.6, 下 -0.9, 上 0.9
    nebula::OrthographicCamera m_Camera;

    // 如果需要移动，可以再加一个位置变量
    glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
};