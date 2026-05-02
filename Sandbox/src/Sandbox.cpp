#include "Sandbox.hpp"

#include "ExampleLayer.hpp"
#include <Random.hpp>

Sandbox::Sandbox()
{
    RAND_PROFILE_FUNCTION();

    getWindow()->setVSync(false);
    pushLayer(new SandboxLayer(*this));
}

Sandbox::~Sandbox() {}
