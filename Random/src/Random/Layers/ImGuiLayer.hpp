#pragma once

#include "Random/Core/App/Layer.hpp"

#include <imgui.h>

namespace Rand
{
    class ImGuiLayer final : public Layer
    {
      public:
        explicit ImGuiLayer(const Application&);
        ~ImGuiLayer();

        /**
         * @brief Initializes ImGui with the params of the engine
         */
        void onAttach() override;

        /**
         * @brief Shuts down ImGui
         */
        void onDetach() override;

        void onEvent(Event& event) override;
        void onImGuiRender() override;

        /**
         * @brief Starts an ImGui frame
         */
        void begin();

        /**
         * @brief Ends an ImGui frame and renders it
         */
        void end();

        void blockEvents(bool blockEvents) { m_BlockEvents = blockEvents; }

      private:
        float m_Time{};
        bool m_BlockEvents = false;
    };
} // namespace Rand
