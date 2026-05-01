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
                for (auto& [name, value] : m_ProfilerResults)
                    ImGui::Value(name, value);
            }
            ImGui::End();
        }

        void pushResult(const Profiler::Result& result) { m_ProfilerResults[result.Name] = result.Value; }

      private:
        std::map<const char*, float> m_ProfilerResults;
    };
} // namespace Rand
