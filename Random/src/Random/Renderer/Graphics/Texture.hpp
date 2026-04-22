#pragma once

#include "Random/Core/Memory/RefCount.hpp"

namespace Rand
{
    class Texture : public RefCount
    {
      public:
        virtual ~Texture() = default;

        virtual void bind(uint32_t slot = 0) const = 0;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
    };

    class Texture2D : public Texture
    {
      public:
        virtual ~Texture2D() = default;

        static Texture2D* create(const std::string& path);
    };
} // namespace Rand
