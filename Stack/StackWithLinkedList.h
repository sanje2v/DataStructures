#pragma once

#include <LinkedList.h>
#include "Stack.h"


template<typename T>
class Stack<T, LinkedList>
{
private:
	LinkedList<T> m_llist;
	size_t m_top;

	inline void assertIsNotEmpty() const
	{
		if (m_top == 0)
			throw std::runtime_error("Stack is empty!");
	}

public:
	Stack()
		: m_top(0) {}

	~Stack() {}

	// Member functions
	void push(const T& data)
	{
		this->m_llist.insertFirst(data);
		++this->m_top;
	}

	T pop()
	{
		assertIsNotEmpty();

		auto value = this->m_llist.data();
		--this->m_top;
		this->m_llist.removeFirst();

		return value;
	}

	void clear()
	{
		this->m_top = 0;
	}

	// Friends
	friend std::ostream& operator<<(std::ostream& os, const Stack<T>& src)
	{
		// Allows std::cout to print Stack contents
		os << "__TOP__" << std::endl;

		for (size_t i = src.m_top; i-- > 0;)
			os << src.m_pArray[i] << std::endl;

		return os;
	}
};