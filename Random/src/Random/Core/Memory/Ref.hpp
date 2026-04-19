#pragma once

namespace Rand
{
    class RefCount;

    template <typename T>
        requires std::derived_from<T, RefCount>
    class Ref;

    class RefCount
    {
      public:
        RefCount() = default;
        RefCount(const RefCount& other);
        RefCount(RefCount&& rhs) noexcept;
        RefCount& operator=(const RefCount& other);
        RefCount& operator=(RefCount&& rhs) noexcept;
        virtual ~RefCount() = default;

        uint32_t getRefCount() const { return m_RefCounted; }

      private:
        void incRefCount() const { ++m_RefCounted; }
        void decRefCount() const { --m_RefCounted; }

      private:
        mutable std::atomic<uint32_t> m_RefCounted{};

        template <typename T>
            requires std::derived_from<T, RefCount>
        friend class Ref;
    };

    template <typename T>
        requires std::derived_from<T, RefCount>
    class Ref
    {
      public:
        Ref() = default;
        Ref(T* obj);
        Ref(const Ref& other) { reset(other.m_Ref); }
        Ref(Ref&& rhs) noexcept { move(std::move(rhs)); }
        Ref(const std::shared_ptr<T>& shared_ptr) { return reset(*shared_ptr); }
        Ref& operator=(const Ref& other) { return reset(other.m_Ref); }
        Ref& operator=(Ref&& rhs) noexcept { return move(rhs); };
        Ref& operator=(const T* const obj) { return reset(obj); }
        Ref& operator=(T* obj) { return reset(obj); }
        Ref& operator=(const std::shared_ptr<T>& shared_ptr) { return reset(*shared_ptr); }
        ~Ref() { destroy(); }

        const std::optional<T&> operator*() const { return dereference(); }
        std::optional<T&> operator*() { return const_cast<T&>(dereference()); }
        const T* operator->() const { return get(); }
        T* operator->() { return get(); }

        Ref& reset(T* obj);
        Ref& reset(const std::shared_ptr<T>& shared_ptr);

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
    Ref<T>& Ref<T>::reset(const std::shared_ptr<T>& shared_ptr)
    {
        destroy();

        m_Ref = new T(*shared_ptr);
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
