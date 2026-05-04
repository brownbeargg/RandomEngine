#pragma once

#include "SceneLayer.hpp"

#include <Random.hpp>
#include <RandomPch.hpp>

namespace Rand
{
    class EditorApp : public Application
    {
      public:
        EditorApp(const WindowProps& windowProps) : Application(windowProps)
        {
            pushLayer(new SceneLayer(*this));
        }

        ~EditorApp() {}
    };
} // namespace Rand
