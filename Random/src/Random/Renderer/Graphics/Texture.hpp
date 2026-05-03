#pragma once

#include "Random/Core/Memory/RefCount.hpp"

namespace Rand
{
    class Texture : public RefCount
    {
      protected:
        using RendererID = uint32_t;

      public:
        virtual ~Texture() = default;
        virtual bool operator==(const Texture& other) const = 0;
        virtual bool operator==(const RendererID otherID) const = 0;

        virtual void bind(uint32_t slot = 0) const = 0;

        virtual void setData(void* data, uint32_t size) = 0;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
    };

    class Texture2D : public Texture
    {
      public:
        virtual ~Texture2D() = default;

        static Texture2D* create(uint32_t width, uint32_t height);
        static Texture2D* create(const std::string& path);
    };
} // namespace Rand
