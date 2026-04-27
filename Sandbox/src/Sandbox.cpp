#include "Sandbox.hpp"

#include "ExampleLayer.hpp"

Sandbox::Sandbox()
{
    pushLayer(new SandboxLayer(*this));
}

Sandbox::~Sandbox() {}
