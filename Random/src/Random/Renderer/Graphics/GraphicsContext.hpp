#pragma once

namespace Rand
{
    class GraphicsContext
    {
      public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };
} // namespace Rand
