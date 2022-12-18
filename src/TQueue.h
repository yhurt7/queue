#ifndef __TQueue_H__
#define __TQueue_H__

#include <iostream>

template <typename T>
class TQueue
{
protected:
  T* pMem;
  int size;
  int bot;
  int top;
  int dataCount;
public:
  TQueue();
  TQueue(int _size);
  TQueue(const TQueue& q);
  TQueue(TQueue&& q);
  TQueue& operator=(const TQueue& q);
  ~TQueue();

  bool IsEmpty() const;
  bool IsFull() const;

  void Push(const T& elem);
  T Top() const;
  void Pop();
  T TopPop();

  bool operator==(const TQueue& q) const;
  bool operator!=(const TQueue& q) const;

  void Free();
};

template<typename T>
TQueue<T>::TQueue()
{
  bot = NULL;
  top = NULL;
  size = NULL;
  dataCount = NULL;
  pMem = nullptr;
}

template<typename T>
TQueue<T>::TQueue(int _size)
{
  if (_size <= 0) { throw "TQueue init error"; }
  Free();
  size = _size;
  pMem = new T[size];
}

template<typename T>
TQueue<T>::TQueue(const TQueue<T>& q)
{
  if (q.pMem == nullptr)
  {
	size = 0;
	pMem = nullptr;
	Free();
  }
  else
  {
	size = q.size;
	bot = q.bot;
	top = q.top;
	dataCount = q.dataCount;
	pMem = new T[size];
	if (!(q.IsEmpty()))
	{
	  int j = bot;
	  for (int i = 0; i < dataCount; i++)
	  {
		pMem[j] = q.pMem[j];
		j--;
		if (j < 0) { j = size - 1; }
	  }
	}
  }
}

template<typename T>
TQueue<T>::TQueue(TQueue<T>&& q)
{
  if (pMem != nullptr) { delete[] pMem; }
  pMem = nullptr;
  size = 0;
  Free();
  std::swap(pMem, q.pMem);
  std::swap(size, q.size);
  std::swap(bot, q.bot);
  std::swap(top, q.top);
  std::swap(dataCount, q.dataCount);
}

template<typename T>
TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q)
{
  if (this != &q)
  {
	if (pMem != nullptr) { delete[] pMem; }
	size = q.size;
	pMem = new T[size];
	bot = q.bot;
	top = q.top;
	dataCount = q.dataCount;
	if (!(q.IsEmpty()))
	{
	  int j = bot;
	  for (int i = 0; i < dataCount; i++)
	  {
		pMem[j] = q.pMem[j];
		j--;
		if (j < 0) { j = size - 1; }
	  }
	}
  }
  return *this;
}

template<typename T>
TQueue<T>::~TQueue()
{
  delete[] pMem;
  size = 0;
  Free();
}

template<typename T>
bool TQueue<T>::IsEmpty(void) const
{
  return (dataCount == 0);
}

template<typename T>
bool TQueue<T>::IsFull(void) const
{
  return (dataCount == size);
}

template<typename T>
void TQueue<T>::Push(const T& elem)
{
  if (IsFull()) { throw "TQueue Push error"; }
  pMem[top] = elem;
  top++;
  top = (top < size) ? top : 0;
  dataCount++;
}

template<typename T>
T TQueue<T>::Top() const
{
  if (IsEmpty()) { throw "Queue is empty"; }
  return pMem[bot];
}

template<typename T>
void TQueue<T>::Pop()
{
  if (IsEmpty()) { throw "Queue is empty"; }
  bot++;
  bot = (bot < size) ? bot : 0;
  dataCount--;
}

template<typename T>
T TQueue<T>::TopPop()
{
  T Result = Top();
  Pop();
  return Result;
}

template<typename T>
bool TQueue<T>::operator==(const TQueue& q) const
{
  if (dataCount != q.dataCount ) { return false; }
  int j = bot;
  int k = q.bot;
  for (int i = 0; i < dataCount; i++)
  {
	if (pMem[j] != q.pMem[k]) { return false; }
	j--;
	j = (j < 0) ? (size - 1) : j;
	k--;
	k = (k < 0) ? (q.size - 1) : k;
  }
  return true;
}

template<typename T>
bool TQueue<T>::operator!=(const TQueue& q) const
{
  return (!(this->operator==(q)));
}

template<typename T>
void TQueue<T>::Free()
{
  top = 0;
  bot = 0;
  dataCount = 0;
}
#endif