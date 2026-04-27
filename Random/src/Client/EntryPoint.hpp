#include "Random/Core/App/Application.hpp"
#include "Random/Core/Log.hpp"

extern Rand::Application* Rand::createApplication();

namespace Rand
{
    /**
     * @brief The main entry point of Random Engine
     */
    class Main
    {
      public:
        static int main(int argc, char* argv[])
        {
            Log::init();
            Ref<Application> app = createApplication();
            app->run();

            return 0;
        }
    };
} // namespace Rand

int main(int argc, char* argv[])
{
    return Rand::Main::main(argc, argv);
}
