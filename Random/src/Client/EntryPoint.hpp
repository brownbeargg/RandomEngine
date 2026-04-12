#include "Random/Core/Application.hpp"
#include "Random/Core/Log.hpp"
#include "RandomPch.hpp"

extern std::unique_ptr<Rand::Application> Rand::createApplication();

int main()
{
    Rand::Log::init();
    auto app = Rand::createApplication();
    app->run();
}
