/* MilindSTL.cpp :
	1. Array
	2. Stack

*/

#include <iostream>
#include <chrono>
#include "MilindSTL.h"
#include <string>

#define wait() std::cin.get()

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	ArrayList<int> arr;
	SmartTimer timer("Main Function");

	for (size_t i = 0; i < 100; i++) {
		arr.push_back(i);
	}

	timer.lapTime("Check 1");

	for (size_t i = 0; i < arr.size(); i++) {
		printf("%d\n", arr[i]);
	}

	timer.lapTime("Check 2");
}
