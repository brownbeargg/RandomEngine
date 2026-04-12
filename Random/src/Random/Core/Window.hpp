#pragma once

#include "Random/Core/Core.hpp"
#include "Random/Events/Event.hpp"

namespace Rand
{
    struct WindowProps
    {
        std::string Title{};
        uint32_t Width{}, Height{};
        int XPos{}, YPos{};
        bool Focus{};

        explicit WindowProps(const std::string_view title = "RANDOM ENGINE", const size_t width = 1280,
            const size_t height = 720, const int xPos = 0, const int yPos = 0, const bool focus = true)
            : Title(title), Width(width), Height(height), XPos(xPos), YPos(yPos), Focus(focus)
        {
        }
    };

    class RAND_API Window
    {
      protected:
        using EventCallbackFn = std::function<void(Event&)>;

      public:
        virtual ~Window() {}

        virtual void onUpdate() = 0;

        inline virtual uint32_t getWidth() const = 0;
        inline virtual uint32_t getHeight() const = 0;

        inline virtual void setEventCallback(const EventCallbackFn& func) = 0;
        inline virtual void setVSync(const bool enabled) = 0;
        inline virtual bool isVSync() const = 0;
        inline virtual void* getNativeWindow() const = 0;

        static Window* create(const WindowProps& props = WindowProps());
    };
} // namespace Rand
