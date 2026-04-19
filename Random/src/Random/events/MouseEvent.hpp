#pragma once

#include "Random/Core/Event.hpp"

namespace Rand
{
    class MouseButtonEvent : public Event
    {
      public:
        ~MouseButtonEvent() {}

        RAND_EVENT_CLASS_CATEGORY((int)EventCategory::Input | (int)EventCategory::Mouse)

        int getMouseButton() const { return m_Button; }

      protected:
        MouseButtonEvent(int button) : m_Button(button) {}

      private:
        int m_Button;
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent
    {
      public:
        explicit MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        RAND_EVENT_CLASS_TYPE(EventType::MouseButtonPressed)

        virtual inline std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << getMouseButton();
            return ss.str();
        }
    };

    class MouseButtonReleasedEvent final : public MouseButtonEvent
    {
      public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        RAND_EVENT_CLASS_TYPE(EventType::MouseButtonReleased)

        virtual inline std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << getMouseButton();
            return ss.str();
        }
    };

    class MouseMovedEvent final : public Event
    {
      public:
        explicit MouseMovedEvent(int xPos, int yPos) : m_XPos(xPos), m_YPos(yPos) {}

        RAND_EVENT_CLASS_TYPE(EventType::MouseMoved)
        RAND_EVENT_CLASS_CATEGORY((int)EventCategory::Input | (int)EventCategory::Mouse)

        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_XPos << ", " << m_YPos;
            return ss.str();
        }

        float getX() const { return m_XPos; }
        float getY() const { return m_YPos; }

      private:
        int m_XPos, m_YPos;
    };

    class MouseScrolledEvent final : public Event
    {
      public:
        explicit MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

        RAND_EVENT_CLASS_TYPE(EventType::MouseScrolled)
        RAND_EVENT_CLASS_CATEGORY((int)EventCategory::Input | (int)EventCategory::Mouse)

        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

      private:
        float m_XOffset, m_YOffset;
    };
} // namespace Rand
