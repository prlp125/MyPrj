#ifndef WIDGET_HPP
#define WIDGET_HPP

////////////////////////////////////////////////////////////////////////////////
#include <thread>

#include "world.hpp"

class Widget {
public:
    Widget(std::unique_ptr<World>);
    ~Widget();
private:
    void deathScreen() const noexcept;
    void showMas();
    void showScore() const noexcept;
    void showTimer() const noexcept;

private:
    char **m_mas;
    std::unique_ptr<World> m_world;
};

#endif // WIDGET_HPP
