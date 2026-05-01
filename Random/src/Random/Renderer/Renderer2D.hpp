#pragma once

#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Graphics/OrthographicCamera.hpp"
#include "Random/Renderer/Graphics/Texture.hpp"

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
        static void drawQuad(const glm::mat4& transform, const Ref<Texture2D> texture,
            const int textureScale = 1, const glm::vec4& tint = glm::vec4(1.0f));
    };
} // namespace Rand
