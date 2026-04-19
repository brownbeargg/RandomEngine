#pragma once

#include "Random/Core/Core.hpp"

namespace Rand
{
#define RAND_BIND_EVENT_FN(eventFn) std::bind(&eventFn, this, std::placeholders::_1)

    /**
     * @brief the type of an event e.g. WindowClose
     */
    enum class EventType
    {
        None = 0,

        KeyPressed,
        KeyReleased,

        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled,

        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        AppTick,
        AppUpdate,
        AppRender,
    };

    /**
     * @brief A broader category of the event e.g. Application
     */
    enum class EventCategory
    {
        None = 0,
        Application = BIT(0),
        Input = BIT(1),
        Keyboard = BIT(2),
        Mouse = BIT(3),
    };

#define RAND_EVENT_CLASS_TYPE(type)                                                                                    \
    static EventType getStaticType()                                                                                   \
    {                                                                                                                  \
        return type;                                                                                                   \
    }                                                                                                                  \
    virtual EventType getEventType() const override                                                                    \
    {                                                                                                                  \
        return getStaticType();                                                                                        \
    }                                                                                                                  \
    virtual const char* getName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

#define RAND_EVENT_CLASS_CATEGORY(category)                                                                            \
    virtual int getCategoryFlags() const override                                                                      \
    {                                                                                                                  \
        return category;                                                                                               \
    }

    class Event
    {
      public:
        inline virtual EventType getEventType() const = 0;
        inline virtual const char* getName() const = 0;
        inline virtual int getCategoryFlags() const = 0;
        inline virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category) const
        {
            return getCategoryFlags() & static_cast<int>(category);
        }

        bool isHandled() { return m_Handled; }

        void operator<<(std::ostream& os) const { os << toString(); }

      private:
        bool m_Handled;

        friend class EventDispatcher;
    };

    class EventDispatcher
    {
      private:
        template <typename T>
            requires std::derived_from<T, Event>
        using EventFn = std::function<bool(T&)>;

      public:
        explicit EventDispatcher(Event& event) : m_Event(event) {}

        /**
         * @brief Tries to handle an event by calling the function param if the type of m_Event == the type of T
         *
         * @param func A function that returns a bool and has a T, which is an Event, param
         */
        template <typename T>
            requires std::derived_from<T, Event>
        bool dispatch(EventFn<T> func)
        {
            if (m_Event.getEventType() == T::getStaticType())
            {
                return m_Event.m_Handled = func(static_cast<T&>(m_Event));
                return true;
            }

            return false;
        }

      private:
        Event& m_Event;
    };
} // namespace Rand

inline std::ostream& operator<<(std::ostream& os, const Rand::Event& event)
{
    return os << event.toString();
}
