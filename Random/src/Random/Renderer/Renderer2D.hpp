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
        static void flush();

        static void drawQuad(const glm::vec3& position, const glm::vec2& scale = glm::vec2(1.0f),
            const glm::mat4& rotation = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));
        static void drawQuad(const glm::vec3& position, const Ref<Texture2D> texture,
            const float textureScale = 1.0f, const glm::vec4& color = glm::vec4(1.0f),
            const glm::vec2& scale = glm::vec2(1.0f), const glm::mat4& rotation = glm::mat4(1.0f));
    };
} // namespace Rand
