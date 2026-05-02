#pragma once

#include "Random/Core/App/Layer.hpp"
#include "Random/Debug/Profiler.hpp"

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
                    ImGui::Text("%.3fms %s", time, name.c_str());
                }
            }
            ImGui::End();
        }

        void pushResult(const Profiler::Result& result)
        {
            m_ProfilerResults[result.Name] = (result.End - result.Start) * 0.001f;
        }

      private:
        std::map<std::string, float> m_ProfilerResults;
    };
} // namespace Rand
