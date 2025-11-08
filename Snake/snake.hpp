#ifndef SNAKE_HPP
#define SNAKE_HPP

////////////////////////////////////////////////////////////////////////////////
#include <conio.h>
#include <vector>
#include <thread>

#include "point.hpp"

//------------------------------------------------------------------------------
class Snake {
public:
     Snake();
     ~Snake();

     int course() const noexcept {
         return m_course;
     }

     void death() {
         m_death = true;
     }

     bool isDeath() const noexcept {
         return m_death;
     }

     bool isEndAnimation() const noexcept {
         return m_endAnimation;
     }

public:
     void addSnake() noexcept;
     void createThread();
     double getTime() const noexcept;
     bool isSnakeHead(const Point &) const noexcept;
     bool isSnakeTail(const Point &) const noexcept;
     Point snakeHead() const noexcept;
     void moveSnake();

private:
    void moveTail();
    void checkGetBonus();
    void changeСourse();
    void DeathScreen();
    void isStartAnimation();
    void startAnimation();
    void startTimer();
    void tailSnake();

private:
    Point m_posHead;
    std::vector<Point> m_snakeTail;
    std::thread m_thread;
    Point m_bonusPoint;
    std::vector<Point> m_superBonus;

    bool m_death;
    bool m_endAnimation;
    bool m_firstStepCurs;
    int m_course;
    uint8_t m_numGive;
};

#endif // SNAKE_HPP
