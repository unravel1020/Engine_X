#pragma once
#include <glm/glm.hpp>

namespace nebula
{
class OrthographicCamera
{
  public:
    // 参数通常是：左、右、下、上（对应屏幕比例）
    OrthographicCamera(float left, float right, float bottom, float top);

    void SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }
    const glm::vec3& GetPosition() const { return m_Position; }

    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

  private:
    void RecalculateViewMatrix();

  private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix; // 缓存：Projection * View

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
};
} // namespace nebula