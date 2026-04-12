#pragma once

#include "Random/Core/Layer.hpp"

namespace Rand
{
    class RAND_API LayerStack
    {
      public:
        LayerStack(const Application& app);
        ~LayerStack();

        void pushLayer(Layer* const layer)
        {
            layer->onAttach();
            m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
        }
        void pushOverlay(Layer* const overlay)
        {
            overlay->onAttach();
            m_Layers.push_back(overlay);
        }

        void popLayer(Layer* const layer);
        void popOverlay(Layer* const overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

        std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

      private:
        std::vector<Layer*> m_Layers{};
        std::vector<Layer*>::iterator m_LayerInsert{};
    };
} // namespace Rand
