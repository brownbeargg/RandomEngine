#include "Random/Application.hpp"

#include "Random/Log.hpp"
#include "Random/RandomPch.hpp"

namespace Rand
{
    Application::Application() {}

    Application::~Application() {}

    void Application::run()
    {
        RAND_CORE_WARN("RANDOM ENGINE IS RUNNING!");
        RAND_TRACE("APPLICATION IS RUNNING");
    }
} // namespace Rand
