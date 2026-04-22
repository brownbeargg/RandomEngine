#pragma once

#include <memory>

namespace Rand
{
    template <typename T>
    using Weak = std::weak_ptr<T>;
}
