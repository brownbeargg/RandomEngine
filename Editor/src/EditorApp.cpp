#include "EditorApp.hpp"

#include <EntryPoint.hpp>

namespace Rand
{
    Application* createApplication()
    {
        WindowProps windowProps;
        windowProps.Title = "Random Editor";
        return new EditorApp(windowProps);
    }
} // namespace Rand

int main(int argc, char* argv[])
{
    Rand::Main::main(argc, argv);
}
