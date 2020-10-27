#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "NonCopyable.h"
#include "NonMovable.h"

class Timer : public NonCopyable, public NonMovable
{
public:
    Timer();
    ~Timer() = default;

    float getDelta();
    float getFPS(const float deltaTime) const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_timePrev;
};

#endif /* end TIMER_H_INCLUDED */