#pragma once

// FIFO POP from TOP , PUSH from TOP
template <typename T, size_t S> class StaticQueue {
public:
  StaticQueue() { memset(m_Data, NULL, S * sizeof(T)); }

  void push(T obj) { m_Data[++TOP] = T; }

  T pop() {}

  ~StaticQueue() { delete[] this; }

private:
  int TOP = -1;
  const int BOTTOM = 0;
  T m_Data[S];
};
