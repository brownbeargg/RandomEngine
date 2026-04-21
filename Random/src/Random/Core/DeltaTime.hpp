#pragma once

namespace Rand
{
    class DeltaTime
    {
      public:
        void recalculate(float& lastTime);

        float getTime() { return m_Time; }
        operator float() { return m_Time; }

      private:
        float m_Time{};
    };
} // namespace Rand
