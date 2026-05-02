#include <EntryPoint.hpp>
#include <Random.hpp>
#include "Sandbox.hpp"

Rand::Application* Rand::createApplication()
{
    RAND_PROFILE_FUNCTION();

    return new Sandbox;
}

int main(int argc, char* argv[])
{
    Rand::Main::main(argc, argv);
}
