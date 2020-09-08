#pragma once

template<typename T>
class ArrayList {

public:
	#define MEM_BLOCK 100

	ArrayList() {
		m_Data = (T*)malloc(Capacity * sizeof(T));
	}

	size_t size() {
		return Top;
	}

	void push_back(T obj) {
		if (this->isFull()) {
			expand();
		}
		m_Data[Top++] = obj;
	}

	bool isEmpty() {
		return (Top == 0) ? true : false;
	}

	bool isFull() {
		return (Top == Capacity) ? true : false;
	}

	T& operator[](int idx) {
		return m_Data[idx];
	}

	const T& operator[](int idx) const {
		return m_Data[idx];
	}

	// This is expensive takes O(CAPACITY) time
	void resize(size_t newCap) {
		if (size > newCap) {
			return;
		}
		T* temp = m_Data;
		m_Data = (T*)calloc(newCap, sizeof(T));

		for (int i = 0; i < Capacity; i++) {
			m_Data[i] = temp[i];
		}

		free(temp);
		Capacity = newCap;
	}

private:

	// This is expensive takes O(CAPACITY) time
	void expand() {
		T* temp = m_Data;
		m_Data = (T*)calloc(Capacity + MEM_BLOCK, sizeof(T));

		for (int i = 0; i < Capacity; i++) {
			m_Data[i] = temp[i];
		}

		free(temp);
		Capacity += MEM_BLOCK;
	}

	T* m_Data = nullptr;
	size_t Top = 0;
	size_t Capacity = MEM_BLOCK;

};
