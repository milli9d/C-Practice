#pragma once

template <typename T> class ArrayList {
private:
	// Minimum vector size in Bytes (Resizes are also in same Block Size) , bigger
	// blocks are faster
	#define MEM_BLOCK 10
	T* m_Data = nullptr;
	size_t Top = 0;
	size_t Capacity = MEM_BLOCK;

public:
	// Default Constructor
	ArrayList() {
		// Allocate memory to store initial capacity elements (WARNING : Unitialized
		// memory)
		m_Data = (T*)malloc(Capacity * sizeof(T));
	}

	//	Return the size of the Stack , not related to capacity of array.
	//	Size is current number of elements present in the ArrayList
	size_t size() { return Top; }

	// Standard push_back , if enough capacity avaialble , then write , else
	// resize and then write
	void push_back(T obj) {
		if (this->isFull()) {
			expand();
		}
		m_Data[Top++] = obj;
	}

	// Check if no elements present
	bool isEmpty() { return (Top == 0) ? true : false; }

	// Check if capacity is fully occupied by elements
	bool isFull() { return (Top == Capacity) ? true : false; }

	// Return Element , Operator [] overload
	T& operator[](int idx) { return m_Data[idx]; }

	// Return const Element , Operator [] overload
	const T& operator[](int idx) const { return m_Data[idx]; }

	// This is expensive takes O(CAPACITY) time
	void resize(size_t newCap) {
		// If number of elements are greater than new capacity , do not change
		// anything , will add useful funciton here later
		if (Top > newCap) {
			return;
		}

		// Store orignal array pointer in a temp location
		T* temp = m_Data;

		// Allocate new memory(initialized) , write pointer to m_Data
		m_Data = (T*)calloc(newCap, sizeof(T));

		// Copy all elements from old array to new array
		for (int i = 0; i < Capacity; i++) {
			m_Data[i] = temp[i];
		}

		// Free memory of old array
		free(temp);

		// Update Capacity
		Capacity = newCap;
	}

	// This is expensive takes O(CAPACITY) time
	void expand() { resize(Capacity + MEM_BLOCK); }
};
