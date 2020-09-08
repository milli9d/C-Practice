/* MilindSTL.cpp :
	1. Array
	2. Stack

*/

#include <iostream>
#include "Dynamic.h"

#define wait() std::cin.get()

int main()
{

	ArrayList<int> arr;

	for (size_t i = 0; i < 10; i++) {
		arr.push_back(i);
	}

	for (size_t i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << std::endl;
	}

}
