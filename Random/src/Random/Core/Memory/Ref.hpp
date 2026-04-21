#pragma once

#include "Random/Core/Memory/RefCount.hpp"

namespace Rand
{
    template <typename T>
        requires std::derived_from<T, RefCount>
    class Ref
    {
      public:
        Ref() = default;
        Ref(T* obj);
        Ref(const Ref& other) { reset(other.m_Ref); }
        Ref(Ref&& rhs) noexcept { move(std::move(rhs)); }
        Ref& operator=(const Ref& other) { return reset(other.m_Ref); }
        Ref& operator=(Ref&& rhs) noexcept { return move(rhs); };
        Ref& operator=(const T* const obj) { return reset(obj); }
        Ref& operator=(T* obj) { return reset(obj); }
        ~Ref() { destroy(); }

        const std::optional<T&> operator*() const { return dereference(); }
        std::optional<T&> operator*() { return const_cast<T&>(dereference()); }
        const T* operator->() const { return get(); }
        T* operator->() { return get(); }

        Ref& reset(T* obj);

        /**
         * @brief Removes the current reference and checks if it should be deleted
         */
        void destroy() const;

        const T* get() const { return m_Ref; }
        T* get() { return m_Ref; }

      private:
        const std::optional<T&> dereference() const;
        std::optional<T&> dereference() { return const_cast<T&>(as_const(m_Ref).dereference()); }

        Ref& move(Ref&& rhs) noexcept;

      private:
        mutable T* m_Ref = nullptr;
    };

    template <typename T>
        requires std::derived_from<T, RefCount>
    Ref<T>::Ref(T* obj) : m_Ref(obj)
    {
        if (obj)
            m_Ref->incRefCount();
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    Ref<T>& Ref<T>::reset(T* obj)
    {
        destroy();

        m_Ref = obj;
        if (m_Ref)
            m_Ref->incRefCount();

        return *this;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    const std::optional<T&> Ref<T>::dereference() const
    {
        if (m_Ref)
            return *m_Ref;

        RAND_CORE_ASSERT("Reference to nullptr");
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    Ref<T>& Ref<T>::move(Ref&& rhs) noexcept
    {
        if (this == &rhs)
            return *this;

        m_Ref = std::move(rhs.m_Ref);
        return *this;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    void Ref<T>::destroy() const
    {
        if (m_Ref)
        {
            m_Ref->decRefCount();

            if (!m_Ref->getRefCount())
                delete m_Ref;
        }

        m_Ref = nullptr;
    }
} // namespace Rand
