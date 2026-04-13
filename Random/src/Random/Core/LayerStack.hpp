#pragma once

#include "Random/Core/Layer.hpp"

namespace Rand
{
    class LayerStack final
    {
      public:
        LayerStack(const Application& app);
        ~LayerStack();

        void pushLayer(Layer* const layer);
        void pushOverlay(Layer* const overlay);

        void popLayer(Layer* const layer);
        void popOverlay(Layer* const overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

        std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

      private:
        std::vector<Layer*> m_Layers{};
        size_t m_LayerInsertIndex{};
    };
} // namespace Rand
