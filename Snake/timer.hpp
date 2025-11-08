#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
public:
    explicit Timer(int endTime) :
        m_startTime {std::chrono::milliseconds(0)},
        m_endTime {endTime},
        m_activate{false}
    {}

    void start() noexcept {
        m_activate = true;
        m_startTime = std::chrono::high_resolution_clock::now();
    }

    void reset() noexcept {
        m_activate = false;
    }

    long long currTime() {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime);
        long long remainingTime = m_endTime - elapsed.count();

        if (remainingTime >= 0) {
            return  remainingTime;
        } else {
            m_activate = false;
            return 0;
        }
    }

    bool isActivate() const noexcept {
        return m_activate;
    }


private:
    std::chrono::high_resolution_clock::time_point m_startTime;
    int m_endTime;
    bool m_activate;
};

#endif // TIMER_HPP
