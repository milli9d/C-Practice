#include <iostream>
#include "MilindSTL.h"
#include <string>

int main()
{
	// Some compiler optimisations , (optional)
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	ArrayList<int> arr;

	SmartTimer timer("Main Process");

	timer.lapTime("Check 1");

	for (size_t i = 0; i < 5000; i++) {
		arr.push_back(i);
	}

	timer.lapTime("Check 2");
	for (size_t i = 0; i < arr.size(); i++) {
		printf("%d\n", arr[i]);
	}

	timer.currentTime("End");

}
