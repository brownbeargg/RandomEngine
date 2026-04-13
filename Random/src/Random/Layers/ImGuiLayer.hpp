#pragma once

#include "Random/Core/Layer.hpp"

#include <imgui.h>

namespace Rand
{
    class ImGuiLayer final : public Layer
    {
      public:
        explicit ImGuiLayer(const Application&);
        ~ImGuiLayer();

        void onAttach() override;
        void onDetach() override;

        void onEvent(Event& event) override;
        void onImGuiRender() override;

        void begin();
        void end();

      private:
        float m_Time{};
    };
} // namespace Rand
