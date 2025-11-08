#ifndef BONUS_HPP
#define BONUS_HPP

////////////////////////////////////////////////////////////////////////////////
#include <vector>

#include "point.hpp"

//------------------------------------------------------------------------------
struct InteractiveObj {
    virtual ~InteractiveObj(){};
    virtual void effect() = 0;                                  // TODO: Добавить бонусы с замедлением и x2
    virtual bool isInteractiveObj(const Point& p) const = 0;
};

////////////////////////////////////////////////////////////////////////////////
struct Bonus : public InteractiveObj {
    explicit Bonus();

    bool isInteractiveObj(const Point &p) const override;
    void startBonusGen();
    void effect() override {};

    Point bonusPoint() const noexcept {
        return m_point;
    }

private:
    Point m_point;
};

////////////////////////////////////////////////////////////////////////////////
struct SuperBonus : public InteractiveObj {
    explicit SuperBonus();

    bool isInteractiveObj(const Point &p) const override;
    void startSuperBonusGen();
    void effect() override {};

    void clearSuperBonus() {
        m_points.clear();
    }
    std::vector<Point> superBonusPoints() const noexcept {
        return m_points;
    }

private:
    std::vector<Point> m_points;
};

#endif // BONUS_HPP
