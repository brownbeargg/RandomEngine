#pragma once

#include "Random/Core/Layer.hpp"
#include "RandomPch.hpp"

namespace Rand
{
    class RAND_API InputLayer : public Layer
    {
      public:
        InputLayer(const Application& app) : Layer("InputLayer", app) {}

        bool isKeyPressed(int key) const;
        bool isMouseButtonPressed(int key) const;

        inline std::pair<float, float> getMousePos() const;
        inline float getMouseX() const { return getMousePos().first; }
        inline float getMouseY() const { return getMousePos().second; }
    };
} // namespace Rand
