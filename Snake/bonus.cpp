#include <algorithm>
#include <random>

#include "bonus.hpp"

//------------------------------------------------------------------------------
Bonus::Bonus() : m_point{0,0}{
    startBonusGen();
}

//------------------------------------------------------------------------------
bool Bonus::isInteractiveObj(const Point &p) const
{
    return p == m_point;
}

//------------------------------------------------------------------------------
void Bonus::startBonusGen()
{
    int x{}, y{};
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dis_x {0, M_COLUMN - 1};
    std::uniform_int_distribution<> dis_y {0, M_ROW - 1};

    x = dis_x(gen);
    y = dis_y(gen);

    m_point = {x,y};
}

//------------------------------------------------------------------------------
SuperBonus::SuperBonus() : m_points{} {

}

//------------------------------------------------------------------------------
bool SuperBonus::isInteractiveObj(const Point &p) const
{
    for(auto &&pSB : m_points) {
        if(p == pSB) {
            return true;
        }
    }
    return false;
}
//------------------------------------------------------------------------------
void SuperBonus::startSuperBonusGen()
{
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dis_x {0, M_COLUMN - 2};
    std::uniform_int_distribution<> dis_y {0, M_ROW - 2};

    int x, y;
    x = dis_x(gen);
    y = dis_y(gen);

    m_points.push_back({x, y});
    m_points.push_back({x+1,y});
    m_points.push_back({x, y+1});
    m_points.push_back({x+1, y+1});
}
