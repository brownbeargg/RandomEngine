#include "Random/Layers/ImGuiLayer.hpp"

#include "Random/Core/App/Application.hpp"
#include "Random/Debug/Instrumentor.hpp"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

namespace Rand
{
    ImGuiLayer::ImGuiLayer(const Application& app) : Layer("ImGuiLayer", app) {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach()
    {
        RAND_PROFILE_FUNCTION();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplOpenGL3_Init("#version 410");
        ImGui_ImplGlfw_InitForOpenGL(
            static_cast<GLFWwindow*>(const_cast<void*>(m_App.getWindow()->getNativeWindow())), true);
    }

    void ImGuiLayer::onDetach()
    {
        RAND_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onEvent(Event& event) {}

    void ImGuiLayer::onImGuiRender()
    {
        RAND_PROFILE_FUNCTION();

        ImGui::ShowDemoWindow();
        ImGui::ShowDebugLogWindow();
    }

    void ImGuiLayer::begin()
    {
        RAND_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_App.getWindow()->getWidth(), m_App.getWindow()->getHeight());

        float dt = (float)glfwGetTime();
        io.DeltaTime = m_Time ? dt - m_Time : 1.0f / 60.0f;
        m_Time = dt;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        RAND_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
} // namespace Rand
