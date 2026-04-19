#include "Random/Core/Memory/Ref.hpp"

namespace Rand
{
    RefCount::RefCount(const RefCount& other)
    {
        m_RefCounted.store(other.m_RefCounted);
    }

    RefCount::RefCount(RefCount&& rhs) noexcept
    {
        m_RefCounted.store(std::move(rhs.m_RefCounted));
    }

    RefCount& RefCount::operator=(const RefCount& other)
    {
        m_RefCounted.store(other.m_RefCounted);
        return *this;
    }

    RefCount& RefCount::operator=(RefCount&& rhs) noexcept
    {
        if (this == &rhs)
            return *this;

        m_RefCounted.store(std::move(rhs.m_RefCounted));
        return *this;
    }
} // namespace Rand
