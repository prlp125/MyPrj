#include <algorithm>
#include <iostream>

#include "widget.hpp"

//------------------------------------------------------------------------------
Widget::Widget(std::unique_ptr<World> world) : m_world(std::move(world))
{
    size_t row {m_world->row()};
    size_t col {m_world->column()};

    m_mas = new char*[row];
    for (int i = 0; i < row; ++i) {
        m_mas[i] = new char[col];
    }

    while(!m_world->isEndAnimation()){
        system("CLS");
        showScore();
        showMas();
        showTimer();
    }

    deathScreen();
}

//------------------------------------------------------------------------------
Widget::~Widget() {
    delete [] m_mas;
}

//------------------------------------------------------------------------------
void Widget::showScore() const noexcept{
    std::cout << "Score: " << m_world->score() << "\n" << std::endl;
}

//------------------------------------------------------------------------------
void Widget::showTimer() const noexcept{
    if(m_world->isActiveTimer()){
        std::cout << "Time: ";

        int koef = TIMER_SB_MS / SPEED_TIMER_MS - static_cast<int>(TIMER_SB_MS - m_world->currTime()) / SPEED_TIMER_MS;
        for(int i = 0; i != koef; ++i) {
            std::cout << "#";
        }
    }
}


//------------------------------------------------------------------------------
void Widget::deathScreen() const noexcept
{
    system("CLS");
    std::cout << "          You DEAD             " << std::endl;
    std::cout << "                               " << std::endl;
    std::cout << "        1 1     1 1            " << std::endl;
    std::cout << "      1 1 1 1 1 1 1 1          " << std::endl;
    std::cout << "      1   1 1 1 1   1          " << std::endl;
    std::cout << "      1     1 1     1          " << std::endl;
    std::cout << "      1 1 1 1 1 1 1 1          " << std::endl;
    std::cout << "          1 1 1 1              " << std::endl;
    std::cout << "           1   1               " << std::endl;
    std::cout << "                               " << std::endl;


    int numText = 0 + rand()%((5 +1) -0);
    std::string textDeath;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    switch (numText) {
        case 0 :
            textDeath = "   AND REMEMBER GAS ON 12 RUB  ";
            break;
        case 1 :
            textDeath = "  NEVER GONNA GIVE YOU UP      ";
            break;
        case 2 :
            textDeath = "    DON'T EAT YELLOW SNOW      ";
            break;
        case 3 :
            textDeath = "          PRESS F              ";
            break;
        default:
            textDeath = "       APPLE IS LIE            ";
    }

    std::cout << textDeath.c_str() << std::endl;
}

//------------------------------------------------------------------------------
void Widget::showMas() {
    size_t row {m_world->row()};
    size_t col {m_world->column()};

    Point currentPoint {};
    for(int i = 0; i != col; ++i) {
        for (int j = 0; j != row; ++j) {
            currentPoint.m_x = i;
            currentPoint.m_y = j;
            if(m_world->isHeadSnake(currentPoint)) {
                m_mas[i][j] = '@';
            } else if(m_world->isSnake(currentPoint)) {
                m_mas[i][j] = 'O';
            } else if(m_world->isBonus(currentPoint)) {
                m_mas[i][j] = '*';
            } else if(m_world->isSuperBonus(currentPoint)) {
                m_mas[i][j] = '?';
            } else {
                m_mas[i][j] = '.';
            }
            std::cout << " " << m_mas[i][j];
        }
        std::cout << "\n";
    }
}
