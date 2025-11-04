#include <algorithm>
#include <iostream>
#include <random>

#include "snake.hpp"
//------------------------------------------------------------------------------
Snake::Snake()
    : m_posHead {2,2},
     m_snakeTail {m_posHead},
     m_death {false},
     m_endAnimation {false},
     m_firstStepCurs {true},
     m_course {2},
     m_numGive {0}
{
    createThread();
}

//------------------------------------------------------------------------------
Snake::~Snake()
{
    if(m_thread.joinable()) {
        m_thread.join();
    }
}

//------------------------------------------------------------------------------
void Snake::createThread()
{
    if(m_thread.joinable()) {
        m_thread.join();
    }

    m_thread = std::thread(&Snake::changeСourse, this);
}


//------------------------------------------------------------------------------
bool Snake::isSnakeHead(const Point &p) const noexcept
{
    return p == m_posHead;
}

//------------------------------------------------------------------------------
bool Snake::isSnakeTail(const Point &p) const noexcept
{
    return std::find_if(m_snakeTail.begin(), m_snakeTail.end(),
            [&p](auto&& vec) { return p == vec; }) != m_snakeTail.end();
}

//------------------------------------------------------------------------------
Point Snake::snakeHead() const noexcept{
    return m_posHead;
}

//------------------------------------------------------------------------------
void Snake::moveSnake()
{
    if(m_course == CURS_DOWN) {
        m_posHead.m_x ++;
    }else if(m_course == CURS_UP) {
        m_posHead.m_x --;
    }else if (m_course == CURS_LEFT){
        m_posHead.m_y --;
    }else {
        m_posHead.m_y ++;
    }
    m_firstStepCurs = true;

    if (m_posHead.m_x >= M_COLUMN) {
        m_posHead.m_x = 0;
    }
    if (m_posHead.m_x < 0) {
        m_posHead.m_x = M_COLUMN;
    }
    if (m_posHead.m_y >= M_ROW) {
        m_posHead.m_y = 0;
    }
    if (m_posHead.m_y < 0) {
        m_posHead.m_y = M_ROW;
    }

    moveTail();
    isStartAnimation();
    if(m_death) {
        startAnimation();
     }
}

//------------------------------------------------------------------------------
void Snake::moveTail()
{
    m_firstStepCurs = true;
    checkGetBonus();
    tailSnake();
}

//------------------------------------------------------------------------------
void Snake::addSnake() noexcept
{
    m_snakeTail.push_back(m_posHead);
}

//------------------------------------------------------------------------------
void Snake::checkGetBonus()
{
    if(m_posHead == m_bonusPoint) {
        addSnake();
    }
}

//------------------------------------------------------------------------------
void Snake::changeСourse()
{
    while (!m_death) {
        int ch = _getch_nolock();

        if((ch == BUTTON_W || ch == BUTTON_UP) && m_course != CURS_DOWN && m_firstStepCurs) {
            m_course = CURS_UP;
            m_firstStepCurs = false;
        } else if ((ch == BUTTON_A || ch == BUTTON_LEFT) && m_course != CURS_RIGHT && m_firstStepCurs) {
            m_course = CURS_LEFT;
            m_firstStepCurs = false;
        } else if ((ch == BUTTON_D || ch == BUTTON_RIGHT) && m_course != CURS_LEFT && m_firstStepCurs) {
            m_course = CURS_RIGHT;
            m_firstStepCurs = false;
        } else if ((ch == BUTTON_S || ch == BUTTON_DOWN) && m_course != CURS_UP && m_firstStepCurs) {
            m_course = CURS_DOWN;
            m_firstStepCurs = false;
        }
    }
}

//------------------------------------------------------------------------------
void Snake::isStartAnimation()
{
    for(size_t i = 1; i != m_snakeTail.size(); ++i) {
        if(m_snakeTail[i] == m_posHead) {
            m_death = true;
        }
    }
}

//------------------------------------------------------------------------------
void Snake::startAnimation() {
    if(m_death) {
        while (!m_snakeTail.empty()){
            std::this_thread::sleep_for(std::chrono::milliseconds(SPEED_TIMER_MS));
            m_snakeTail.pop_back();
        }
        m_endAnimation = true;
    }
}

//------------------------------------------------------------------------------
void Snake::tailSnake()
{
    std::vector<Point> prewVec = m_snakeTail;
    if(!m_snakeTail.empty()) {
        for (size_t i = 1; i != m_snakeTail.size(); ++i) {
            m_snakeTail[i] = prewVec[i-1];
        }
        m_snakeTail.front() = m_posHead;
    }
}
