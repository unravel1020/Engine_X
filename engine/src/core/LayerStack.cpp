#include "../include/nebula/core/LayerStack.hpp"

namespace nebula
{

LayerStack::~LayerStack()
{
    for (Layer* layer : m_Layers)
    {
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer)
{
    m_Layers.emplace_back(layer);

    layer->OnAttach();
}

void LayerStack::PopLayer(Layer* layer) {}

} // namespace nebula