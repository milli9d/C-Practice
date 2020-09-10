#include <iostream>
#include <string>

#include "MilindSTL.h"

int main() {
  // Some compiler optimisations , (optional)
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  SmartTimer timer("Main Process");

  StaticArray<int, 10> arr;

  arr.at(11);
  timer.lapTime("Begin");

  timer.lapTime("Insert 1");

  timer.lapTime("Insert 2");
}