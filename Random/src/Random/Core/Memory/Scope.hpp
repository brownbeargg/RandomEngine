#pragma once

#include <memory>

namespace Rand
{
    template <typename T>
    using Scope = std::unique_ptr<T>;
}
