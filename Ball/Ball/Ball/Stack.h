#pragma once
#ifndef STACK_H
#define STACK_H

#include <cassert> // ��� assert
#include <iostream>
#include <iomanip> // ��� setw
using namespace std;

template <typename T>
class Stack
{
private:
	T* stackPtr;                      // ��������� �� ����
	const int size;                   // ������������ ���������� ��������� � �����
	int top;                          // ����� �������� �������� �����
public:
	Stack(int = 132);                  // �� ��������� ������ ����� ����� 10 ���������
	Stack(const Stack<T>&);          // ����������� �����������
	~Stack();                         // ����������

	inline void push(const T&);     // ��������� ������� � ������� �����
	inline void pop();                   // ������� ������� �� ������� ����� � ������� ���
	inline void printStack();         // ����� ����� �� �����
	inline const T& Peek(int) const; // n-� ������� �� ������� �����
	inline int getStackSize() const;  // �������� ������ �����
	inline T* getPtr() const;         // �������� ��������� �� ����
	inline int getTop() const;        // �������� ����� �������� �������� � �����
	inline bool isEmpty();
	inline T& getTopLink();

};

// ���������� ������� ������� ������ STack
template<typename T>
T& Stack<T>::getTopLink()
{
	return stackPtr[top - 1];
}
// ����������� �����
template <typename T>
Stack<T>::Stack(int maxSize) :
	size(maxSize) // ������������� ���������
{
	stackPtr = new T[size]; // �������� ������ ��� ����
	top = 0; // �������������� ������� ������� �����;
}

// ����������� �����������
template <typename T>
Stack<T>::Stack(const Stack<T>& otherStack) :
	size(otherStack.getStackSize()) // ������������� ���������
{
	stackPtr = new T[size]; // �������� ������ ��� ����� ����
	top = otherStack.getTop();

	for (int ix = 0; ix < top; ix++)
		stackPtr[ix] = otherStack.getPtr()[ix];
}

// ������� ����������� �����
template <typename T>
Stack<T>::~Stack()
{
	delete[] stackPtr; // ������� ����
}

// ������� ���������� �������� � ����
template <typename T>
inline void Stack<T>::push(const T& value)
{
	// ��������� ������ �����
	if(top < size); // ����� �������� �������� ������ ���� ������ ������� �����
	stackPtr[top++] = value; // �������� ������� � ����
}

// ������� �������� �������� �� �����
template <typename T>
inline void Stack<T>::pop()
{
	// ��������� ������ �����
	if(top > 0); // ����� �������� �������� ������ ���� ������ 0
	stackPtr[--top]; // ������� ������� �� �����
}

// ������� ���������� n-� ������� �� ������� �����
template <class T>
inline const T& Stack<T>::Peek(int nom) const
{
	//
	if(nom <= top);
	return stackPtr[top - nom]; // ������� n-� ������� �����
}

// ����� ����� �� �����
template <typename T>
inline void Stack<T>::printStack()
{
	for (int ix = top - 1; ix >= 0; ix--)
		cout << "|" << setw(4) << stackPtr[ix] << endl;
}

// ������� ������ �����
template <typename T>
inline int Stack<T>::getStackSize() const
{
	return size;
}

// ������� ��������� �� ���� (��� ������������ �����������)
template <typename T>
inline T* Stack<T>::getPtr() const
{
	return stackPtr;
}

// ������� ������ �����
template <typename T>
inline int Stack<T>::getTop() const
{
	return top;
}
template<typename T>
bool Stack<T>::isEmpty()
{
	return !top;
}
#endif // STACK_H#pragma once
