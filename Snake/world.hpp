#ifndef WORLD_HPP
#define WORLD_HPP

#include <chrono>
#include <thread>

#include "bonus.hpp"
#include "snake.hpp"
#include "timer.hpp"

////////////////////////////////////////////////////////////////////////////////
#define M_ROW 16
#define M_COLUMN 16

#define CURS_UP -1
#define CURS_LEFT 0
#define CURS_DOWN 1

////////////////////////////////////////////////////////////////////////////////
class World {
public:
    World(size_t column = M_COLUMN, size_t row = M_ROW);
    ~World();

    size_t column() const noexcept {
        return m_column;
    }

    size_t row() const noexcept {
        return m_row;
    }

    int score() const noexcept{
        return m_score;
    }

    long long currTime(){
        return m_timer.currTime();
    }

public:
    bool isActiveTimer() const noexcept;
    bool isBonus(const Point &) const noexcept;
    bool isEndAnimation() const noexcept;
    bool isSuperBonus(const Point&) const noexcept;
    bool isHeadSnake(const Point&) const noexcept;
    bool isSnake(const Point&) const noexcept;


private:
    void addSnake() noexcept;
    void addNumSuperBonus();
    void createThread();
    void checkGetBonus();
    void checkIsSnake();
    void moveSnake();

private:
    size_t m_column;
    size_t m_row;
    int m_score;
    bool m_isRun;
    Bonus m_bonus;
    SuperBonus m_superBonus;
    uint8_t m_numGive = 0;
    std::unique_ptr<Snake> m_snakeS;
    std::thread m_thread;
    Timer m_timer;
};

#endif // WORLD_HPP
