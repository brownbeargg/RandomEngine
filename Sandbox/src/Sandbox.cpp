#include "Sandbox.hpp"

SandboxLayer::SandboxLayer(const Rand::Application& app) : Layer("SandboxLayer", app) {}

void SandboxLayer::onUpdate()
{
    RAND_CORE_INFO("SandboxLayer::OnUpdate");
}

void SandboxLayer::onEvent(Rand::Event& event)
{
    RAND_INFO("event is {0}", event.toString());
}

Sandbox::Sandbox()
{
    pushLayer(new SandboxLayer(*this));
    pushOverlay(new Rand::ImGuiLayer(*this));
}

Sandbox::~Sandbox() {}
