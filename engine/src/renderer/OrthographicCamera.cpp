#include "nebula/renderer/OrthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace nebula
{
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
{
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthographicCamera::RecalculateViewMatrix()
{
    // 摄像机的 View 矩阵 = 摄像机位移矩阵的逆矩阵
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
} // namespace nebula