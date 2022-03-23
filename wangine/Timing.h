#pragma once
#include <chrono>
#include <iostream>
#include "SDL/SDL.h"

namespace wangine {
    class timer
    {
    public:
        timer()
        {
            m_start_timepoint = std::chrono::high_resolution_clock::now();
        }

        ~timer()
        {
            stop();
        }

        void stop()
        {
            auto end_timepoint = std::chrono::high_resolution_clock::now();

            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_timepoint).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

            auto duration = end - start;
            double duration_ms = duration * 0.001;
            double duration_s = duration_ms * 0.001;

            std::cout << duration_s << std::endl;
        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start_timepoint;
    };

    class FPSLimiter 
    {
    public:
        FPSLimiter();
        void init(float maxFPS);

        void begin();

        //setter
        void setMaxFPS(float maxFPS) { _maxFPS = maxFPS; }

        //returns current FPS
        float end();

    private:
        void calculateFPS();

        float _FPS;
        float _frameTime;
        float _maxFPS;
        unsigned int _startTicks;
    };
}