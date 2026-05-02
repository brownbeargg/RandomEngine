#pragma once

#include "Random/Renderer/RendererAPI.hpp"

namespace Rand
{
    class OpenGLRendererAPI final : public RendererAPI
    {
      public:
        void init() override
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glEnable(GL_DEPTH_TEST);
        }

        void clearColor(const glm::vec4& color) override { glClearColor(color.r, color.g, color.b, color.a); }
        void clear() override { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

        void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override
        {
            uint32_t count = indexCount ? vertexArray->getIndexBuffer()->getCount() : indexCount;
            glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        }

        void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override
        {
            glViewport(x, y, width, height);
        }
    };
} // namespace Rand
