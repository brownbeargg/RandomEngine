#include "Sandbox.hpp"

SandboxLayer::SandboxLayer() : Layer("SandboxLayer") {}

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
    pushLayer(new SandboxLayer());
}

Sandbox::~Sandbox() {}
