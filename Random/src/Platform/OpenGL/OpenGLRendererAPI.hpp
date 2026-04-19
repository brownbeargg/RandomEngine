#pragma once

#include "Random/Renderer/RendererAPI.hpp"

namespace Rand
{
    class OpenGLRendererAPI final : public RendererAPI
    {
      public:
        void clearColor(const glm::vec4& color) override { glClearColor(color.r, color.g, color.b, color.a); }
        void clear() override { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

        void drawIndexed(const Ref<VertexArray>& vertexArray) override
        {
            glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
        }
    };
} // namespace Rand
