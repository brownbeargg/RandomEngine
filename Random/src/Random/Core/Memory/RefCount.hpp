#pragma once

namespace Rand
{
    class RefCount
    {
      public:
        RefCount() = default;
        virtual ~RefCount() = default;

        RefCount(const RefCount& other)
        {
            m_RefCounted = other.m_RefCounted;
            m_WeakCounted = other.m_WeakCounted;
        }

        RefCount(RefCount&& rhs) noexcept
        {
            m_RefCounted = std::move(rhs.m_RefCounted);
            m_WeakCounted = std::move(rhs.m_WeakCounted);
        }

        RefCount& operator=(const RefCount& other)
        {
            m_RefCounted = other.m_RefCounted;
            m_WeakCounted = other.m_WeakCounted;
            return *this;
        }

        RefCount& operator=(RefCount&& rhs) noexcept
        {
            if (this == &rhs)
                return *this;

            m_RefCounted = std::move(rhs.m_RefCounted);
            m_WeakCounted = std::move(rhs.m_WeakCounted);
            return *this;
        }

        uint32_t getRefCount() const { return m_RefCounted; }
        uint32_t getWeakCount() const { return m_WeakCounted; }

      private:
        void incRefCount() const { ++m_RefCounted; }
        void decRefCount() const { --m_RefCounted; }

        void incWeakCount() const { ++m_WeakCounted; }
        void decWeakCount() const { --m_WeakCounted; }

      private:
        mutable uint32_t m_RefCounted{};
        mutable uint32_t m_WeakCounted{};

        template <typename T>
            requires std::derived_from<T, RefCount>
        friend class Ref;

        template <typename T>
            requires std::derived_from<T, RefCount>
        friend class Weak;
    };
} // namespace Rand
