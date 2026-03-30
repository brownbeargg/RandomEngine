#pragma once

#include "Random/Core.hpp"

namespace Rand
{
    class RAND_API Application
    {
      public:
        Application();
        virtual ~Application();

        void run();
    };

    std::unique_ptr<Application> createApplication();
} // namespace Rand
