#pragma once

/*	Stack allocated on the Program Stack (static)
        1.POP/PUSH/isEmpty/PEEK in O(1) time
        2.LIFO order
*/
template <typename T, size_t S> class StaticStack {
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

  void push(T val) { m_Data[++TOP] = val; }

  T pop() {
    T obj = m_Data[TOP];
    memset(&m_Data[TOP], NULL, sizeof(T));
    TOP--;
    return obj;
  }

  const T peek() const { return m_Data[TOP]; }

  ~StaticStack() {
    // free(m_Data);
  }

private:
  T m_Data[S];
  int TOP = -1;
};
