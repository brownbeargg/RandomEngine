#pragma once

#include "Random/Renderer/Buffer/VertexArray.hpp"

#include <glm/glm.hpp>

namespace Rand
{
    class RendererAPI
    {
      public:
        /**
         * @brief Possible renderAPI's
         */
        enum class API
        {
            None = 0,
            OpenGL = 1
        };

      public:
        virtual void init() = 0;

        /**
         * @brief Clears the screen to specified color
         *
         * @param color The color the screen should clear to
         */
        virtual void clearColor(const glm::vec4& color) = 0;

        /**
         * @brief Clears the buffers that manage renderer e.g. color buffer
         */
        virtual void clear() = 0;

        /**
         * @brief Draws from specified VertexArray object
         *
         * @param vertexArray The VertexArray object which holds the state of what you want to draw
         */
        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        /**
         * @return The currently used RenderAPI
         */
        static API getAPI() { return s_API; }

      private:
        static API s_API;
    };
} // namespace Rand
