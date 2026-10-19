//Stopwatch.h
#include <chrono>
struct Stopwatch {
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    void reset(){
        t = std::chrono::steady_clock::now();
    }
    double Ms() {
        double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t).count();
        t = std::chrono::steady_clock::now();
        return ms;
    }
};