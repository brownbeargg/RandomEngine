#pragma once

#include "Random/Core/Codes/KeyCodes.hpp"
#include "Random/Core/Codes/MouseCodes.hpp"

#include "Random/Core/Memory/RefCount.hpp"

#include <glm/glm.hpp>

namespace Rand
{
    class Window;

    /**
     * @brief Class to handle input
     *
     * This class should mostly be defined in a compiled c++ in the Platform directory so it's implementation
     * will always be cross-platform
     */
    class Input final : public RefCount
    {
      public:
        Input(Window* window) : m_Window(window) {}
        ~Input() = default;

        bool isKeyPressed(const Key key) const;
        bool isMouseButtonPressed(const Mouse button) const;

        glm::vec2 getMousePos() const;
        float getMouseX() const { return getMousePos().x; }
        float getMouseY() const { return getMousePos().y; }

      private:
        Window* const m_Window;
    };
} // namespace Rand
