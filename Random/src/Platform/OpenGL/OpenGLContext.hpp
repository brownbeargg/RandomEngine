#include "Random/Renderer/Graphics/GraphicsContext.hpp"

#include <GLFW/glfw3.h>

namespace Rand
{
    class OpenGLContext : public GraphicsContext
    {
      public:
        OpenGLContext(GLFWwindow* windowHandle);

        void init() override;
        void swapBuffers() override;

      private:
        GLFWwindow* m_Window;
    };
} // namespace Rand
