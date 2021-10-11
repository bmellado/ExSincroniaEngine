/**
 * @file simple_timer.h
 * @brief Some functionality to implement a basic profiler
 *
 * @author Daniel Calderón
 * @license MIT
*/
#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <thread>

namespace Sincronia
{
    template <typename LogProfileFunction>
    
    class Timer
    {
    public:
        Timer(const char* name, LogProfileFunction&& logProfileFunction, bool stabilize = false) :
            _name(name),
            _logProfileFunction(logProfileFunction),
            _stopped(false),
            _stabilize(stabilize),
            _FPS(60),
            _frameDelay(1000.0 / _FPS)


        {
            _startTime = std::chrono::steady_clock::now();
        }

        ~Timer()
        {
            if (!_stopped)
            {
                stop();
            }
        };

        void stop() {
            
                std::chrono::time_point<std::chrono::steady_clock> endTime = std::chrono::steady_clock::now();
                std::chrono::duration<float, std::milli> duration = endTime - _startTime;
                float durationAsFloat = duration.count();

                _stopped = true;
                

                if (_stabilize) {

                    if (_frameDelay > durationAsFloat) {
                        
                        //Try better options, this is not accurate
                        std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(_frameDelay - durationAsFloat));
                    }

                    
                    endTime = std::chrono::steady_clock::now();
                    duration = endTime - _startTime;
                    durationAsFloat = duration.count();
                    
                    
                }

                _logProfileFunction({ _name , durationAsFloat });
            
        }

        void interrupt();


    private:
        const char* _name;
        LogProfileFunction _logProfileFunction;
        bool _stopped;
        std::chrono::time_point<std::chrono::steady_clock> _startTime;
        int _FPS;
        float _frameDelay;
        bool _stabilize;
    };

    struct ProfileResult
    {
        std::string timerName;
        float duration;
    };



    std::ostream& operator<<(std::ostream& os, const ProfileResult& result)
    {
        return os << std::fixed << std::setprecision(3) << std::setw(2) << result.duration << "ms " << result.timerName;
    }

} // Sincronia

#define PROFILE_SCOPE(name, stats) Sincronia::Timer timer##__LINE__(name, [&stats](const Sincronia::ProfileResult& profileResult) { stats.push_back(profileResult); })
#define PROFILE_SCOPE_STABLE(name, stats) Sincronia::Timer timer##__LINE__(name, [&stats](const Sincronia::ProfileResult& profileResult) { stats.push_back(profileResult); }, true)