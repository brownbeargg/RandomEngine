#include "Random/Core/Application.hpp"
#include "Random/Core/Log.hpp"

extern Rand::Application* Rand::createApplication();

int main()
{
    using namespace Rand;

    Log::init();
    auto app = std::unique_ptr<Application>(createApplication());
    app->run();
}
