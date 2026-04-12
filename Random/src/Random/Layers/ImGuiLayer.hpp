#pragma once

#include "Random/Core/Layer.hpp"

#include <imgui.h>

namespace Rand
{
    class RAND_API ImGuiLayer : public Layer
    {
      public:
        explicit ImGuiLayer(const Application&);
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;

        void onUpdate() override;
        void onEvent(Event& event) override;

      private:
        float m_Time;
    };
} // namespace Rand
