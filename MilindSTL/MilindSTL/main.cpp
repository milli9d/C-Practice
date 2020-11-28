#include <iostream>
#include <string>

#include "MilindSTL.h"

class MyHashSet {
private:
	size_t capacity;

public:
	/** Initialize your data structure here. */
	MyHashSet() {
		capacity = 0;
	}

	void add(int key) {
	}

	void remove(int key) {
	}

	/** Returns true if this set contains the specified element */
	bool contains(int key) {
	}
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

#include <stdio.h>
#include <iostream>

template<typename T>
class singlyList {
private:
	struct listNode {
		listNode* next;
		T val;
	};

	listNode* head;
	size_t size;

public:

	singlyList() {
		size = 0;
		head = NULL;
	}

	void insert(T val) {
		listNode temp = new listNode();
	}

	void printList() {
		listNode* ptr = head;
		for (int i = 0; i < size; i++) {
			std::cout << ptr->val << "|";
			ptr = ptr->next;
		}
	}
};

int main() {
	// Some compiler optimisations , (optional)
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	singlyList<int> list;

	list.printList();

	SmartTimer timer("Main Process");

	MyHashSet set = MyHashSet();
}