#include "Sandbox.hpp"

#include "SandboxLayer.hpp"

#include <EntryPoint.hpp>
#include <Random.hpp>

Sandbox::Sandbox()
{
    getWindow()->setVSync(false);
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
