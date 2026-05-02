#include "Sandbox.hpp"

#include "ExampleLayer.hpp"

#include <EntryPoint.hpp>
#include <Random.hpp>

Sandbox::Sandbox()
{
    pushLayer(new SandboxLayer(*this));
}

Sandbox::~Sandbox() {}

Rand::Application* Rand::createApplication()
{
    RAND_PROFILE_FUNCTION();

    return new Sandbox;
}

int main(int argc, char* argv[])
{
    Rand::Main::main(argc, argv);
}
