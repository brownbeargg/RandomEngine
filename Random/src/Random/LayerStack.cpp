#include "Random/LayerStack.hpp"

namespace Rand
{
    LayerStack::LayerStack() : m_LayerInsert(m_Layers.begin()) {}

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
            delete layer;
    }

    void LayerStack::popLayer(Layer* const layer)
    {
        auto it = std::find(m_Layers.begin(), m_LayerInsert, layer);
        if (it != m_LayerInsert)
        {
            m_Layers.erase(it);
            --m_LayerInsert;
        }
    }

    void LayerStack::popOverlay(Layer* const overlay)
    {
        auto it = std::find(m_Layers.begin(), m_LayerInsert, overlay);
        if (it != m_LayerInsert)
        {
            m_Layers.erase(it);
            --m_LayerInsert;
        }
    }
} // namespace Rand
