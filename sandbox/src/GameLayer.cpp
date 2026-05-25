#include "GameLayer.hpp"
#include "nebula/core/Layer.hpp"
#include "nebula/core/Log.hpp"
#include "nebula/core/Timestamp.hpp"
#include "nebula/event/Event.hpp"
#include <glad/glad.h> // 为下一步渲染做准备

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> // 需要这个来获取时间戳

// 1. 构造函数实现
GameLayer::GameLayer() : Layer("GameLayer") {}
// 顶点着色器：将坐标传给 GPU
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// 片段着色器：输出橙色
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)";
// 2. OnAttach 实现
void GameLayer::OnAttach()
{
    NEBULA_INFO("GameLayer Attached");

    // 1. 编译顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // 2. 编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 3. 链接着色器程序
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 释放着色器源码资源
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 4. 定义三角形顶点（NDC 坐标系：-1 到 1）
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 左下角
        0.5f,  -0.5f, 0.0f, // 右下角
        0.0f,  0.5f,  0.0f  // 顶部
    };

    // 5. 创建缓冲区对象
    glGenVertexArrays(1, &VAO); // VAO：顶点数组对象（说明书）
    glGenBuffers(1, &VBO);      // VBO：顶点缓冲对象（仓库）

    // 绑定 VAO
    glBindVertexArray(VAO);

    // 绑定 VBO 并填充数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 告诉 GPU 怎么解析这些数据：位置 0，3 个浮点数，不归一化，步长 3*float，偏移 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
// 3. OnDetach 实现 (之前报错找不到这个)
void GameLayer::OnDetach() { NEBULA_INFO("GameLayer Detached"); }

// 4. OnUpdate 实现
void GameLayer::OnUpdate(nebula::Timestamp ts)
{
    // 1. 清屏
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // 深灰色背景
    glClear(GL_COLOR_BUFFER_BIT);

    // 2. 绑定着色器
    glUseProgram(shaderProgram);

    // 3. 绑定 VAO 并绘制
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3); // 画三角形，从第 0 个点开始，共 3 个点
}

// 5. OnEvent 实现 (之前报错找不到这个)
void GameLayer::OnEvent(nebula::Event& event)
{
    // NEBULA_TRACE("Event received: {0}", event.GetName());
}