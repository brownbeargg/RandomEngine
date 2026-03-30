#include "Random/Application.hpp"

#include "Random/RandomPch.hpp"

namespace Rand
{
    Application::Application() { std::cout << "APPLICATION CREATED!\n"; }

    Application::~Application() {}

    void Application::run() { std::cout << "RANDOM ENGINE IS RUNNING!\n"; }
} // namespace Rand
