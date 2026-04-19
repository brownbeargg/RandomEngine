#pragma once

#include "Random/Core/Event.hpp"
#include "Random/Core/App/Input.hpp"
#include "Random/Core/Memory/Ref.hpp"
#include "Random/Renderer/Graphics/GraphicsContext.hpp"

namespace Rand
{
    /**
     * @brief a struct that contains information about the window
     */
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

    class Window : public RefCount
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

        const Input& getInput() const { return *m_Input.get(); }

        /**
         * @brief Gets the window object
         *
         * This function should be used with caution because if the platform / graphicsAPI isn't clear you will read
         * from memory wrong (because void* is used), which is ofcourse unsafe
         *
         * @return A handle to the window object
         */
        inline virtual const void* getNativeWindow() const = 0;

        /**
         * @brief Creates a window object
         *
         * This function should be defined in other compiled c++ files instead of here because it is made to be a
         * cross-platform alternative instead of a lot of #ifdefs
         *
         * @param props The properties of the window
         */
        static Window* create(const WindowProps& props = WindowProps());

      protected:
        GraphicsContext* m_Context;
        Ref<Input> m_Input;
    };
} // namespace Rand
