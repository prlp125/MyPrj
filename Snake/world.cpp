#include <random>

#include "world.hpp"

//------------------------------------------------------------------------------
World::World(size_t column, size_t row) : m_column {column},
    m_row {row},
    m_score  {0},
    m_isRun {false},
    m_timer {TIMER_SB_MS}
{
    m_snakeS = std::make_unique<Snake>();
    createThread();
}

//------------------------------------------------------------------------------
World::~World() {
    m_isRun = false;
    if(m_thread.joinable()) {
        m_thread.join();
    }
}

//------------------------------------------------------------------------------
bool World::isActiveTimer() const noexcept
{
    return m_timer.isActivate();
}

//------------------------------------------------------------------------------
bool World::isBonus(const Point &p) const noexcept
{
    return m_bonus.isInteractiveObj(p);
}

//------------------------------------------------------------------------------
bool World::isEndAnimation() const noexcept {
    return m_snakeS->isEndAnimation();
}


//------------------------------------------------------------------------------
bool World::isSuperBonus(const Point &p) const noexcept
{
    return m_superBonus.isInteractiveObj(p);
}

//------------------------------------------------------------------------------
bool World::isHeadSnake(const Point &p) const noexcept
{
    return m_snakeS->isSnakeHead(p);
}

//------------------------------------------------------------------------------
bool World::isSnake(const Point &p) const noexcept
{
    return m_snakeS->isSnakeTail(p);
}

//------------------------------------------------------------------------------
void World::checkGetBonus()
{
    if(isBonus(m_snakeS->snakeHead())) {
        m_score += 4;
        m_bonus.startBonusGen();

        while(m_snakeS->isSnakeTail(m_bonus.bonusPoint())){
            m_bonus.startBonusGen();
        }

        m_snakeS->addSnake();
        addNumSuperBonus();

    } else if(isSuperBonus(m_snakeS->snakeHead())) {
        const auto&& multScore = std::round(static_cast<double>(m_timer.currTime()) / 1000);
        m_timer.reset();
        m_superBonus.clearSuperBonus();
        m_score += (4*static_cast<int>(multScore+1));
    }

    if(!m_timer.isActivate() && m_timer.currTime() == 0){
        m_timer.reset();
        m_superBonus.clearSuperBonus();
    }
}

//------------------------------------------------------------------------------
void World::checkIsSnake() {
    if(isSnake(m_snakeS->snakeHead())) {
        m_isRun = false;

    }
}

//------------------------------------------------------------------------------
void World::addNumSuperBonus()
{
    if(++m_numGive == 5) {
        m_superBonus.startSuperBonusGen();
        const auto &&vec = m_superBonus.superBonusPoints();
        while(std::any_of(vec.begin(), vec.end(), [this](const Point& p){
            return m_snakeS->isSnakeTail(p);
        }) || isSuperBonus(m_bonus.bonusPoint())){
            m_superBonus.startSuperBonusGen();
        }

        m_numGive = 0;
        m_timer.start();
    }
}

//------------------------------------------------------------------------------
void World::createThread()
{
    if(m_thread.joinable()) {
        m_thread.join();
    }

    m_thread = std::thread(&World::moveSnake, this);
}


//------------------------------------------------------------------------------
void World::moveSnake()
{
    while(!m_snakeS->isDeath()){
        m_snakeS->moveSnake();
        checkGetBonus();
        std::this_thread::sleep_for(std::chrono::microseconds(100000));
    }
}
