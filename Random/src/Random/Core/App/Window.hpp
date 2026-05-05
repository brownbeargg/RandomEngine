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
        std::string Title = "RANDOM ENGINE";
        uint32_t Width = 1280, Height = 720;
        int XPos{}, YPos{};
        bool Focus = true;
        bool HasTitleBar = true;
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

        Ref<Input> input() const { return m_Input; }

        /**
         * @brief Gets the window object
         *
         * This function should be used with caution because if the platform / graphicsAPI isn't clear you
         * will read from memory wrong (because void* is used), which is ofcourse unsafe
         *
         * @return A handle to the window object
         */
        inline virtual const void* getNativeWindow() const = 0;

        /**
         * @brief Creates a window object
         *
         * This function should be defined in other compiled c++ files instead of here because it is made to
         * be a cross-platform alternative instead of a lot of #ifdefs
         *
         * @param props The properties of the window
         */
        static Window* create(const WindowProps& props = WindowProps());

      protected:
        GraphicsContext* m_Context;
        Ref<Input> m_Input = new Input(this);
    };
} // namespace Rand
