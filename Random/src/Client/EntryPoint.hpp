#include "Random/Core/App/Application.hpp"
#include "Random/Core/Log.hpp"

#include "Random/Debug/Instrumentor.hpp"

extern Rand::Application* Rand::createApplication();

namespace Rand
{
    /**
     * @brief The main entry point of Random Engine
     */
    class Main
    {
      public:
        static void main(int argc, char* argv[])
        {
            RAND_PROFILE_BEGIN_SESSION("Startup", "RandomProfile-Startup.json");
            Log::init();
            Application* app = createApplication();
            RAND_PROFILE_END_SESSION();

            RAND_PROFILE_BEGIN_SESSION("Runtime", "RandomProfile-Runtime");
            app->run();
            RAND_PROFILE_END_SESSION();

            RAND_PROFILE_BEGIN_SESSION("Shutdown", "RandomProfile-Shutdown");
            delete app;
            RAND_PROFILE_END_SESSION();
        }
    };
} // namespace Rand
