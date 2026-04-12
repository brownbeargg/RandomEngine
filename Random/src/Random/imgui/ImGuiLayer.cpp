#include "Random/imgui/ImguiLayer.hpp"

#include "Random/Application.hpp"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Platform/OpenGL/ImGuiGLFWWindow.h"

#include <GLFW/glfw3.h>

namespace Rand
{
    ImGuiLayer::ImGuiLayer(const Application& app) : Layer("ImGuiLayer", app) {}

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        // TODO: add keymaps here

        ImGui_ImplOpenGL3_Init("#version 410");
        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(m_App.getWindow().getNativeWindow()), true);
    }

    void ImGuiLayer::onDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::onUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(m_App.getWindow().getWidth(), m_App.getWindow().getHeight());

        float dt = (float)glfwGetTime();
        io.DeltaTime = m_Time ? dt - m_Time : 1.0f / 60.0f;
        m_Time = dt;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& event) {}
} // namespace Rand
