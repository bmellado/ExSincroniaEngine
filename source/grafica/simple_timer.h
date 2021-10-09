/**
 * @file simple_timer.h
 * @brief Some functionality to implement a basic profiler
 * 
 * @author Daniel Calderón
 * @license MIT
*/

#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>

namespace Grafica
{

template <typename LogProfileFunction>
class Timer
{
public:
    Timer(const char* name, LogProfileFunction&& logProfileFunction)
        : _name(name), _logProfileFunction(logProfileFunction),
        _stopped(false)

    {
        _startTime = std::chrono::steady_clock::now();
        _FPS = 360;
        _frameDelay = 1000.0 / _FPS;
    }

    ~Timer()
    {
        if (!_stopped)
        {
            stop();
        }
    }

    void stop()
    {
        std::chrono::time_point<std::chrono::steady_clock> endTime = std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> duration = endTime - _startTime;
        float durationAsFloat = duration.count();

        _stopped = true;

        //std::cout << _name << ": "<< durationAsFloat << "ms" << std::endl;
        if (_frameDelay > durationAsFloat) {
            //std::cout << _frameDelay << " " << durationAsFloat << "\n";
            Sleep((_frameDelay - durationAsFloat));
        }

        endTime = std::chrono::steady_clock::now();
        duration = endTime - _startTime;
        durationAsFloat = duration.count();

        _logProfileFunction({ _name , durationAsFloat });
        
    }

private:
    const char* _name;
    LogProfileFunction _logProfileFunction;
    bool _stopped;
    std::chrono::time_point<std::chrono::steady_clock> _startTime;
    int _FPS;
    float _frameDelay;
};

struct ProfileResult
{
    std::string timerName;
    float duration;
};

ProfileResult res("h", 2.0f);



std::ostream& operator<<(std::ostream& os, const ProfileResult& result)
{
    return os << std::fixed << std::setprecision(3) << std::setw(2) << result.duration << "ms " << result.timerName;
}

} // Grafica

#define PROFILE_SCOPE(name, stats) Grafica::Timer timer##__LINE__(name, [&stats](const Grafica::ProfileResult& profileResult) { stats.push_back(profileResult); })
