#pragma once

#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Graphics/OrthographicCamera.hpp"
#include "Random/Renderer/Graphics/SubTexture2D.hpp"
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

        static void startBatch();
        static void nextBatch();

        static void flush();

        static void drawQuad(
            const glm::mat4& transform = glm::mat4(1.0f), const glm::vec4& color = glm::vec4(1.0f));
        static void drawQuad(const glm::mat4& transform, const Ref<Texture2D> texture,
            const float textureScale = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
        static void drawQuad(const glm::mat4& transform, const Ref<SubTexture2D> subTexture,
            const float textureScale = 1.0f, const glm::vec4& color = glm::vec4(1.0f));

        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t getTotalVertexCount() { return QuadCount * 4; }
            uint32_t getTotalIndexCount() { return QuadCount * 6; }
        };

        static Statistics getStats();
        static void resetStats();
    };
} // namespace Rand
