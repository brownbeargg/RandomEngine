#pragma once

#include "Random/Core/App/Layer.hpp"
#include "Random/Core/Profiler.hpp"

#include "imgui.h"

namespace Rand
{
    class ImGuiProfileLayer final : public Layer
    {
      public:
        ImGuiProfileLayer(const Application& app) : Layer("ImGuiProfilerLayer", app) {}
        ~ImGuiProfileLayer() = default;

        void onImGuiRender() override
        {
            ImGui::Begin("Profiler");
            {
                for (auto& [name, time] : m_ProfilerResults)
                {
                    char label[50];
                    strcpy_s(label, name);
                    strcat_s(label, "  %.3fms");
                    ImGui::Text(label, time);
                }
            }
            ImGui::End();
        }

        void pushResult(const Profiler::Result& result) { m_ProfilerResults[result.Time] = result.Value; }

      private:
        std::map<const char*, float> m_ProfilerResults;
    };
} // namespace Rand
