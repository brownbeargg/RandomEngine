#pragma once

#include "Random/Core/Layer.hpp"
#include "RandomPch.hpp"

#include <glm/vec2.hpp>

namespace Rand
{
    class InputLayer : public Layer
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
