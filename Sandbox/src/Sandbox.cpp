#include "Sandbox.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app) : Layer("SandboxLayer", app) {}

void SandboxLayer::onUpdate() {}

void SandboxLayer::onEvent(Rand::Event& event)
{
    RAND_INFO("event is {0}", event.toString());
}

void SandboxLayer::onImGuiRender()
{
    ImGui::Begin("hello world");
    ImGui::Text("this is kind of a seperate window!");
    static float color = 0.5;
    ImGui::ColorEdit3("edit color", &color);
    ImGui::End();
}

Sandbox::Sandbox()
{
    pushLayer(new SandboxLayer(*this));
}

Sandbox::~Sandbox() {}
