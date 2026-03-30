#include "EntryPoint.hpp"
#include "Random.hpp"
#include "Sandbox.hpp"

std::unique_ptr<Rand::Application> Rand::createApplication() { return std::make_unique<Sandbox>(); }
