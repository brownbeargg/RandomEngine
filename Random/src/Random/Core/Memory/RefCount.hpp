#pragma once

namespace Rand
{
    class RefCount
    {
      public:
        RefCount() = default;
        virtual ~RefCount() = default;
        RefCount(const RefCount& other) { m_RefCounted = other.m_RefCounted; }
        RefCount(RefCount&& rhs) noexcept { m_RefCounted = std::move(rhs.m_RefCounted); }

        RefCount& operator=(const RefCount& other)
        {
            m_RefCounted = other.m_RefCounted;
            return *this;
        }

        RefCount& operator=(RefCount&& rhs) noexcept
        {
            if (this == &rhs)
                return *this;

            m_RefCounted = std::move(rhs.m_RefCounted);
            return *this;
        }

        uint32_t getRefCount() const { return m_RefCounted; }

      private:
        void incRefCount() const { ++m_RefCounted; }
        void decRefCount() const { --m_RefCounted; }

      private:
        mutable uint32_t m_RefCounted{};

        template <typename T>
            requires std::derived_from<T, RefCount>
        friend class Ref;
    };
} // namespace Rand
