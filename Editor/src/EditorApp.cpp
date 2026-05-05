#include "EditorApp.hpp"

#include <EntryPoint.hpp>

namespace Rand
{
    Application* createApplication()
    {
        WindowProps windowProps = {.Title = "Random Editor", .HasTitleBar = true};
        EditorApp* app = new EditorApp(windowProps);

        app->getWindow()->setVSync(false);
        app->runWhileMinimized(false);

        return app;
    }
} // namespace Rand

int main(int argc, char* argv[])
{
    Rand::Main::main(argc, argv);
}
