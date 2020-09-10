#pragma once

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