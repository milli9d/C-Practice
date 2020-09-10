#pragma once

#include <chrono>
#include <thread>

/*
        Scoped Timer Library , instantiate this in any function to benchmark
   portions of code
*/
class SmartTimer {
private:
  std::chrono::steady_clock::time_point start, end, lap;
  std::chrono::duration<float> duration, lapduration;

public:
  SmartTimer(const char *str) {
    lap = std::chrono::high_resolution_clock::now();
    start = std::chrono::high_resolution_clock::now();
    printf("Process Timer Started for %s \n", str);
  }

  // Returns the time from Timer Object Instantiation
  void currentTime() {
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    printf("Current Time = %.02lf ms\n", duration.count() * 1000.0f);
  }

  // Returns time between current time and last lap time
  void lapTime() {
    std::chrono::steady_clock::time_point temp = lap;
    lap = std::chrono::high_resolution_clock::now();
    lapduration = lap - temp;
    printf("Lap Time = %.02lf ms\n", lapduration.count() * 1000.0f);
  }

  void currentTime(const char *str) {
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    printf("%s = %.02lf ms\n", str, duration.count() * 1000.0f);
  }

  // Returns time between current time and last lap time
  void lapTime(const char *str) {
    std::chrono::steady_clock::time_point temp = lap;
    lap = std::chrono::high_resolution_clock::now();
    lapduration = lap - temp;
    printf("%s = %.02lf ms\n", str, lapduration.count() * 1000.0f);
  }

  // Destructor calls the end time automatically
  ~SmartTimer() {
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    printf("Process Timer Ended after %.02lf ms\n ",
           duration.count() * 1000.0f);
  }
};
