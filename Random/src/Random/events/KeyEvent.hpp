#pragma once

#include "Random/Events/Event.hpp"

namespace Rand
{
    class RAND_API KeyEvent : public Event
    {
      public:
        RAND_EVENT_CLASS_CATEGORY((int)EventCategory::Input | (int)EventCategory::Keyboard)

        int getKeyCode() const { return m_KeyCode; }

      protected:
        explicit KeyEvent(uint16_t keyCode) : m_KeyCode(keyCode) {}

      private:
        uint16_t m_KeyCode;
    };

    class RAND_API KeyPressedEvent : public KeyEvent
    {
      public:
        explicit KeyPressedEvent(uint16_t keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

        RAND_EVENT_CLASS_TYPE(EventType::KeyPressed)

        virtual std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << getKeyCode() << " (" << m_RepeatCount << " repeat)";
            return ss.str();
        }

      private:
        int m_RepeatCount;
    };

    class RAND_API KeyReleasedEvent : public KeyEvent
    {
      public:
        explicit KeyReleasedEvent(uint16_t keyCode) : KeyEvent(keyCode) {}

        RAND_EVENT_CLASS_TYPE(EventType::KeyReleased)

        virtual std::string toString()
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << getKeyCode();
            return ss.str();
        }
    };
} // namespace Rand
