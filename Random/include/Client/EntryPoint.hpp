#include "Random/Application.hpp"
#include "Random/Log.hpp"
#include "Random/RandomPch.hpp"

extern std::unique_ptr<Rand::Application> Rand::createApplication();

int main()
{
    Rand::Log::init();
    auto app = Rand::createApplication();
    app->run();
}
