#include "Random/Core/LayerStack.hpp"

namespace Rand
{
    LayerStack::LayerStack(const Application& app) : m_Layers() {}

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_Layers)
            delete layer;
    }

    void LayerStack::pushLayer(Layer* const layer)
    {
        layer->onAttach();
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
        ++m_LayerInsertIndex;
    }

    void LayerStack::pushOverlay(Layer* const overlay)
    {
        overlay->onAttach();
        m_Layers.push_back(overlay);
    }

    void LayerStack::popLayer(Layer* const layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (it != m_Layers.end())
        {
            (*it)->onDetach();
            m_Layers.erase(it);
            --m_LayerInsertIndex;
        }
    }

    void LayerStack::popOverlay(Layer* const overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (it != m_Layers.end())
        {
            (*it)->onDetach();
            m_Layers.erase(it);
        }
    }
} // namespace Rand
