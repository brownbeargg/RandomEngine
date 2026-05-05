#pragma once

#include "EditorLayer.hpp"

#include <Random.hpp>
#include <RandomPch.hpp>

namespace Rand
{
    class EditorApp : public Application
    {
      public:
        EditorApp(const WindowProps& windowProps) : Application(windowProps)
        {
            getWindow()->setVSync(false);
            pushLayer(new EditorLayer(*this));
        }

        ~EditorApp() {}
    };
} // namespace Rand
