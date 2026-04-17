#include <EntryPoint.hpp>
#include <Random.hpp>
#include "Sandbox.hpp"

Rand::Application* Rand::createApplication()
{
    return new Sandbox;
}
