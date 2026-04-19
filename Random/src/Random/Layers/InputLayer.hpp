#pragma once

#include "Random/Core/Layer.hpp"
#include "RandomPch.hpp"

#include <glm/vec2.hpp>

namespace Rand
{
    /**
     * @brief Layer to handle input
     *
     * This class should mostly be defined in a compiled c++ in the Platform directory so it's implementation will
     * always be cross-platform
     */
    class InputLayer final : public Layer
    {
      public:
        InputLayer(const Application& app) : Layer("InputLayer", app) {}

        bool isKeyPressed(int key) const;
        bool isMouseButtonPressed(int key) const;

        glm::vec2 getMousePos() const;
        float getMouseX() const { return getMousePos().x; }
        float getMouseY() const { return getMousePos().y; }
    };
} // namespace Rand
