#include <chrono>
#include <iostream>

#include "widget.hpp"

//------------------------------------------------------------------------------
int main()
{
    Widget widget{std::make_unique<World>()};
    return 0;
}
