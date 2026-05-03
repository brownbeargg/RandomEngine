#pragma once

#include "Random/Core/Assert.hpp"
#include "Random/Core/Memory/RefCount.hpp"

namespace Rand
{
    template <typename T>
        requires std::derived_from<T, RefCount>
    class Ref;

    template <typename T>
        requires std::derived_from<T, RefCount>
    class Weak
    {
      public:
        Weak() = default;
        Weak(T* obj) { reset(obj); }
        Weak(const Ref<T>& ref) { reset(ref.m_Data); }
        Weak(const Weak& other) { reset(other.m_Data); }
        Weak(Weak&& rhs) noexcept { move(std::move(rhs)); }
        Weak& operator=(T* obj) { return reset(obj); }
        Weak& operator=(const Ref<T>& ref) { return reset(ref.m_Data); }
        Weak& operator=(const Weak& other) { return reset(other.m_Data); }
        Weak& operator=(Weak&& rhs) { return move(std::move(rhs)); }
        ~Weak() { destroy(); }

        const T& operator*() const { return dereference(); }
        T& operator*() { return dereference(); }
        const T* operator->() const { return get(); }
        T* operator->() { return get(); }

        Ref<T> lock() { return m_Data; };

        Weak& reset(T* obj);
        void destroy();

        const T* get() const { return m_Data; }
        T* get() { return m_Data; }

        bool expired() { return m_Data->getRefCount(); }

      private:
        const T& dereference() const;
        T& dereference() { return const_cast<T&>(std::as_const(*this).dereference()); }

        Weak& move(Weak&& rhs) noexcept;

      private:
        T* m_Data = nullptr;

        template <typename U>
            requires std::derived_from<U, RefCount>
        friend class Ref;
    };

    template <typename T>
        requires std::derived_from<T, RefCount>
    Weak<T>& Weak<T>::reset(T* obj)
    {
        if (m_Data == obj)
            return *this;

        destroy();

        m_Data = obj;
        if (m_Data)
            m_Data->incWeakCount();

        return *this;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    const T& Weak<T>::dereference() const
    {
        RAND_CORE_RELEASE_ASSERT(m_Data, "Reference to nullptr");
        return *m_Data;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    Weak<T>& Weak<T>::move(Weak&& rhs) noexcept
    {
        if (this == &rhs)
            return *this;

        destroy();

        m_Data = rhs.m_Data;
        rhs.m_Data = nullptr;

        return *this;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    void Weak<T>::destroy()
    {
        if (m_Data)
        {
            m_Data->decWeakCount();

            if (!m_Data->getRefCount() && !m_Data->getWeakCount())
                delete m_Data;
        }

        m_Data = nullptr;
    }
} // namespace Rand
