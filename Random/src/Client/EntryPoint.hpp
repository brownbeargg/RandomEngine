#include "Random/Core/Application.hpp"
#include "Random/Core/Log.hpp"

extern Rand::Application* Rand::createApplication();

namespace Rand
{
    /**
     * @brief The main entry point of Random Engine
     */
    int main(int argc, char* argv[])
    {
        Log::init();
        Ref<Application> app = createApplication();
        app->run();

        return 0;
    }
} // namespace Rand

int main(int argc, char* argv[])
{
    return Rand::main(argc, argv);
}
