#pragma once

#include "Random/Core/Memory/Ref.hpp"

#include <glm/glm.hpp>

namespace Rand
{
    class Window;

    /**
     * @brief Class to handle input
     *
     * This class should mostly be defined in a compiled c++ in the Platform directory so it's implementation will
     * always be cross-platform
     */
    class Input final : public RefCount
    {
      public:
        Input(Window* const window) : m_Window(window) {}
        ~Input() = default;

        bool isKeyPressed(int key) const;
        bool isMouseButtonPressed(int key) const;

        glm::vec2 getMousePos() const;
        float getMouseX() const { return getMousePos().x; }
        float getMouseY() const { return getMousePos().y; }

      private:
        Window* const m_Window;
    };
} // namespace Rand
