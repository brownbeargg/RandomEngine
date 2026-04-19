#pragma once

namespace Rand
{
    /**
     * @brief Possible renderAPI's
     */
    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1
    };

    class Renderer
    {
      public:
        /**
         * @return The currently used RenderAPI
         */
        static RendererAPI getAPI() { return s_RendererAPI; }

      private:
        static RendererAPI s_RendererAPI;
    };
} // namespace Rand
