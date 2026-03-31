#pragma once

#include "Random/events/Event.hpp"

namespace Rand
{
    class RAND_API WindowCloseEvent : public Event
    {
      public:
        WindowCloseEvent() = default;

        RAND_EVENT_CLASS_TYPE(EventType::WindowClose)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        std::string toString() const override { return "WindowCloseEvent"; }
    };

    class RAND_API WindowResizeEvent : public Event
    {
      public:
        WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {}

        RAND_EVENT_CLASS_TYPE(EventType::WindowResize)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        virtual inline std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        uint32_t getWidth() { return m_Width; }
        uint32_t getHeight() { return m_Height; }

      private:
        uint32_t m_Width, m_Height;
    };

    class RAND_API WindowFocusEvent : public Event
    {
      public:
        WindowFocusEvent() = default;

        RAND_EVENT_CLASS_TYPE(EventType::WindowFocus)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        virtual inline std::string toString() const override { return "WindowFocusEvent"; }
    };

    class RAND_API WindowLostFocusEvent : public Event
    {
      public:
        WindowLostFocusEvent() = default;

        RAND_EVENT_CLASS_TYPE(EventType::WindowLostFocus)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        std::string toString() const override { return "WindowLostFocusEvent"; }
    };

    class RAND_API WindowMovedEvent : public Event
    {
      public:
        WindowMovedEvent(int xPos, int yPos) : m_XPos(xPos), m_YPos(yPos) {}

        RAND_EVENT_CLASS_TYPE(EventType::WindowMoved)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        virtual inline std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowMovedEvent: " << m_XPos << ", " << m_YPos;
            return ss.str();
        }

      private:
        int m_XPos, m_YPos;
    };

    class RAND_API AppTickEvent : public Event
    {
      public:
        AppTickEvent() = default;

        RAND_EVENT_CLASS_TYPE(EventType::AppTick)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        virtual inline std::string toString() const override { return "AppTickEvent"; }
    };

    class RAND_API AppUpdateEvent : public Event
    {
      public:
        AppUpdateEvent() = default;

        RAND_EVENT_CLASS_TYPE(EventType::AppTick)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        virtual inline std::string toString() const override { return "AppUpdateEvent"; }

      private:
    };

    class RAND_API AppRenderEvent : public Event
    {
      public:
        AppRenderEvent() = default;

        RAND_EVENT_CLASS_TYPE(EventType::AppRender)
        RAND_EVENT_CLASS_CATEGORY(EventCategory::Application)

        virtual inline std::string toString() const override { return "AppRenderEvent"; }
    };
} // namespace Rand
