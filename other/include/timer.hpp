#pragma once

#include <chrono>

#ifdef USE_NEW_CODE //新代码在下面

namespace sp
{

class timer
{
public:
    using clk_t = std::chrono::high_resolution_clock;
    timer() : m_tp(clk_t::now()){}
    void reset()
    {
        m_tp = clk_t::now();
    }
    template <typename T = std::milli>
    double get() //ms
    {
        return std::chrono::duration<double, T>(clk_t::now() - m_tp).count();
    }
    std::time_t getTimeStamp()
    {
        std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        auto tmp=std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
        std::time_t timestamp = tmp.count();
        return timestamp;
    }
private:
    clk_t::time_point m_tp;
}; //class timer
}

#else //旧代码在下面



#endif
