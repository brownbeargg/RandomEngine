#pragma once

#include "Random/Core/Memory/RefCount.hpp"
#include "Random/Core/Assert.hpp"

namespace Rand
{
    template <typename T>
        requires std::derived_from<T, RefCount>
    class Ref
    {
      public:
        Ref() = default;
        Ref(T* obj) { reset(obj); }
        Ref(const Ref& other) { reset(other.m_Data); }
        Ref(Ref&& rhs) noexcept { move(std::move(rhs)); }
        Ref& operator=(T* obj) { return reset(obj); }
        Ref& operator=(const Ref& other) { return reset(other.m_Data); }
        Ref& operator=(Ref&& rhs) noexcept { return move(std::move(rhs)); }
        ~Ref() { destroy(); }

        const T& operator*() const { return dereference(); }
        T& operator*() { return dereference(); }
        const T* operator->() const { return get(); }
        T* operator->() { return get(); }

        operator bool() const { return m_Data != nullptr; }

        Ref& reset(T* obj);

        /**
         * @brief Removes the current reference and checks if it should be deleted
         */
        void destroy();

        const T* get() const { return m_Data; }
        T* get() { return m_Data; }

      private:
        const T& dereference() const;
        T& dereference() { return const_cast<T&>(std::as_const(*this).dereference()); }

        Ref& move(Ref&& rhs) noexcept;

      private:
        T* m_Data = nullptr;

        template <typename U>
            requires std::derived_from<U, RefCount>
        friend class Weak;
    };

    template <typename T>
        requires std::derived_from<T, RefCount>
    Ref<T>& Ref<T>::reset(T* obj)
    {
        if (m_Data == obj)
            return *this;

        destroy();

        m_Data = obj;
        if (m_Data)
            m_Data->incRefCount();

        return *this;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    const T& Ref<T>::dereference() const
    {
        RAND_CORE_RELEASE_ASSERT(m_Data, "Reference to nullptr");
        return *m_Data;
    }

    template <typename T>
        requires std::derived_from<T, RefCount>
    Ref<T>& Ref<T>::move(Ref&& rhs) noexcept
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
    void Ref<T>::destroy()
    {
        if (m_Data)
        {
            m_Data->decRefCount();

            if (!m_Data->getRefCount())
                delete m_Data;
        }

        m_Data = nullptr;
    }
} // namespace Rand
