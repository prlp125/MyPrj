#ifndef POINT_HPP
#define POINT_HPP

////////////////////////////////////////////////////////////////////////////////
#define M_ROW 16
#define M_COLUMN 16

#define CURS_UP -1
#define CURS_DOWN 1
#define CURS_LEFT 0
#define CURS_RIGHT 2

#define BUTTON_W 119
#define BUTTON_A 97
#define BUTTON_S 115
#define BUTTON_D 100

#define BUTTON_UP 72
#define BUTTON_LEFT 75
#define BUTTON_DOWN 80
#define BUTTON_RIGHT 77

#define TIMER_SB_MS 5000
#define SPEED_TIMER_MS 250

////////////////////////////////////////////////////////////////////////////////
struct Point
{
    Point(int x = 0,int y = 0)
        : m_x{x},
          m_y{y}
    {}

    bool operator==(const Point &p) const {
        return m_x == p.m_x && m_y == p.m_y;
    }

    int m_x;
    int m_y;
};

#endif // POINT_HPP
