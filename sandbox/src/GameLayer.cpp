#include "GameLayer.hpp"
#include "../include/nebula/renderer/RenderCommand.hpp" // 引入渲染指令
#include "../include/nebula/renderer/Renderer.hpp"      // 引入渲染器
#include "nebula/core/Input.hpp"                        // 引入输入系统
#include "nebula/core/Log.hpp"
#include <GLFW/glfw3.h> // 引入 GLFW 键盘输入定义


GameLayer::GameLayer() : Layer("GameLayer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {}

void GameLayer::OnAttach()
{
    NEBULA_INFO("GameLayer Attached: Using Nebula Abstractions");

    // 1. 定义顶点数据 (位置)
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 左下角
        0.5f,  -0.5f, 0.0f, // 右下角
        0.0f,  0.5f,  0.0f  // 顶部
    };

    // 2. 创建 VAO
    m_VertexArray = std::make_shared<nebula::VertexArray>();

    // 3. 创建 VBO 并设置 Layout (这是你之前写的 BufferLayout 逻辑)
    auto vertexBuffer = std::make_shared<nebula::VertexBuffer>(vertices, sizeof(vertices));

    // 关键点：这里定义了 Shader 如何读取顶点数据
    nebula::BufferLayout layout = {{nebula::ShaderDataType::Float3, "a_Position"}};
    vertexBuffer->SetLayout(layout);

    // 将 VBO 放入 VAO
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    // 4. 创建 IBO (索引缓冲)
    uint32_t indices[3] = {0, 1, 2};
    auto indexBuffer = std::make_shared<nebula::IndexBuffer>(indices, 3);
    m_VertexArray->SetIndexBuffer(indexBuffer);

    // 5. 创建 Shader
    const std::string vertexSrc = R"(
        #version 330 core
        
        layout (location = 0) in vec3 a_Position;

        // 必须在这里定义
        uniform mat4 u_ViewProjection;

        void main() {
            // 必须在这里使用，否则会被编译器优化掉
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
        }
    )";

    const std::string fragmentSrc = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);
        }
    )";

    m_Shader = std::make_shared<nebula::Shader>(vertexSrc, fragmentSrc);
}

void GameLayer::OnUpdate(nebula::Timestep ts)
{
    // 摄像机移动逻辑
    float speed = 2.0f;
    if (nebula::Input::IsKeyPressed(GLFW_KEY_A))
        m_CameraPosition.x -= speed * ts;
    else if (nebula::Input::IsKeyPressed(GLFW_KEY_D))
        m_CameraPosition.x += speed * ts;

    if (nebula::Input::IsKeyPressed(GLFW_KEY_W))
        m_CameraPosition.y += speed * ts;
    else if (nebula::Input::IsKeyPressed(GLFW_KEY_S))
        m_CameraPosition.y -= speed * ts;

    m_Camera.SetPosition(m_CameraPosition);

    // 渲染
    nebula::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    nebula::RenderCommand::Clear();

    nebula::Renderer::BeginScene(m_Camera);
    nebula::Renderer::Submit(m_Shader, m_VertexArray);
    nebula::Renderer::EndScene();
}

void GameLayer::OnDetach() {}
void GameLayer::OnEvent(nebula::Event& event) {}