#pragma once

#include "Random/Core/Memory/RefCount.hpp"
#include "Random/Core/Assert.hpp"
#include "RandomPch.hpp"

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
        Ref& operator=(Ref&& rhs) noexcept { return move(std::move(rhs)); }
        Ref& operator=(T* obj) { return reset(obj); }
        ~Ref() { destroy(); }

        const T& operator*() const { return dereference(); }
        T& operator*() { return dereference(); }
        const T* operator->() const { return get(); }
        T* operator->() { return get(); }

        Ref& reset(T* obj);

        /**
         * @brief Removes the current reference and checks if it should be deleted
         */
        void destroy();

        const T* get() const { return m_Ref; }
        T* get() { return m_Ref; }

      private:
        const T& dereference() const;
        T& dereference() { return const_cast<T&>(std::as_const(*this).dereference()); }

        Ref& move(Ref&& rhs) noexcept;

      private:
        T* m_Ref = nullptr;
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
        if (m_Ref == obj)
            return *this;

        destroy();

        m_Ref = obj;
        if (m_Ref)
            m_Ref->incRefCount();

        return *this;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    const T& Ref<T>::dereference() const
    {
        RAND_CORE_RELEASE_ASSERT(m_Ref, "Reference to nullptr");
        return *m_Ref;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    Ref<T>& Ref<T>::move(Ref&& rhs) noexcept
    {
        if (this == &rhs)
            return *this;

        destroy();

        m_Ref = rhs.m_Ref;
        rhs.m_Ref = nullptr;

        return *this;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    void Ref<T>::destroy()
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
