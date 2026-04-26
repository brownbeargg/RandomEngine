#pragma once

#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Rand
{
    class RenderCommand
    {
      public:
        static void init() { s_RendererAPI->init(); }

        /**
         * @brief Clears the screen to specified color
         *
         * @param color The color the screen should clear to
         */
        static void clearColor(const glm::vec4& color)
        {
            s_RendererAPI->clearColor({color.r, color.g, color.b, color.a});
        }

        /**
         * @brief Clears the buffers that manage renderer e.g. color buffer
         */
        static void clear() { s_RendererAPI->clear(); }

        /**
         * @brief Draws from specified VertexArray object
         *
         * @param vertexArray The VertexArray object which holds the state of what you want to draw
         */
        static void drawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_RendererAPI->drawIndexed(vertexArray);
        }

        static void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_RendererAPI->setViewPort(x, y, width, height);
        }

      private:
        static RendererAPI* s_RendererAPI;
    };
} // namespace Rand
