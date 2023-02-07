#include "Time.h"
#include <chrono>

double _deltaTime = 0;
std::chrono::system_clock::time_point lastTime;

using namespace Core;

double Time::deltaTime()
{
    return _deltaTime;
}

void Time::initTime()
{
    lastTime = std::chrono::system_clock::now();
}

void Time::updateTime()
{
    auto now = std::chrono::system_clock::now();

    _deltaTime = ((std::chrono::duration<double>) (now - lastTime)).count();

    lastTime = now;
}
