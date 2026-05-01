#pragma once

#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Graphics/OrthographicCamera.hpp"

namespace Rand
{
    class Renderer2D
    {
      public:
        static void init();
        static void shutdown();

        static void beginScene(OrthographicCamera* cam);
        static void endScene();

        static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
    };
} // namespace Rand
