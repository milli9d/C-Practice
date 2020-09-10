#pragma once

// FIFO POP from TOP , PUSH from TOP
template<typename T, size_t S>
class StaticQueue {
public:
	StaticQueue() {
		memset(m_Data, NULL, S * sizeof(T));
	}

	void push(T obj) {
		m_Data[++TOP] = T;

	}

	T pop() {

	}

	~StaticQueue() {
		delete[] this;
	}
private:
	int TOP = -1;
	const int BOTTOM = 0;
	T m_Data[S];

};

/*	Stack allocated on the Program Stack (static)
	1.POP/PUSH/isEmpty/PEEK in O(1) time
	2.LIFO order
*/
template<typename T, size_t S>
class StaticStack {
public:

	StaticStack() {
		TOP = -1;
		memset(m_Data, NULL, S * sizeof(T));
	}

	size_t size() { return S; }

	bool isEmpty() {
		if (TOP == -1) {
			return true;
		}
		return false;
	}

	void push(T val) {
		m_Data[++TOP] = val;
	}

	T pop() {
		T obj = m_Data[TOP];
		memset(&m_Data[TOP], NULL, sizeof(T));
		TOP--;
		return obj;
	}

	const T peek() const {
		return m_Data[TOP];
	}

	~StaticStack() {

		//free(m_Data);
	}

private:

	T m_Data[S];
	int TOP = -1;
};

/*	Array allocated on the Program Stack (static)
	1.arr[n] O(n) time
	2.fixed size
	3. StaticArray<int , 10> nums; <- Declaration
*/
template<typename T, size_t S>
class StaticArray {
public:

	// Default Constructor , Initialize to Zero
	StaticArray() {
		memset(m_Data, NULL, S * sizeof(T));
	}

	// [] Operator Overloads to return proper reference and values
	T& operator[](size_t idx) {
		if (idx >= 0 && idx < S) {
			return m_Data[idx];
		}
	}

	const T& operator[] (size_t idx) const {
		if (idx >= 0 && idx < S) {
			return m_Data[idx];
		}
	}

	constexpr size_t size() const {
		return S;
	}

	~StaticArray() {
		delete[] this;
	}

private:
	T m_Data[S] = {};
};
