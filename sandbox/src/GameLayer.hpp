#pragma once

#include "nebula/core/Layer.hpp"
// #include "nebula/core/Log.hpp"
#include "nebula/core/Timestamp.hpp"
#include "nebula/event/Event.hpp"

class GameLayer : public nebula::Layer
{
  public:
    GameLayer(); // 声明构造函数
    virtual ~GameLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override; // 声明
    virtual void OnUpdate(nebula::Timestamp ts) override;
    virtual void OnEvent(nebula::Event& event) override; // 声明

  private:
    unsigned int shaderProgram; // GPU 里的 ID
    unsigned int VAO, VBO;      // 顶点数组对象和顶点缓冲对象的 ID
};