#pragma once

#include <vector>


// Default implementation of Stack using C++ array
template<typename T, template<typename...> class Container=std::vector>
class Stack
{
private:
	const size_t DEFAULT_SIZE = 32;

	size_t m_size;
	T* m_pArray;
	size_t m_top;

	inline void assertIsNotEmpty() const
	{
		if (m_top == 0)
			throw std::runtime_error("Stack is empty!");
	}

	void moveToBiggerArray()
	{
		this->m_size *= 2;
		auto pnewArray = new T[this->m_size];
		for (size_t i = 0; i < this->m_top; ++i)
			pnewArray[i] = this->m_pArray[i];
		delete this->m_pArray;
		this->m_pArray = pnewArray;
	}

public:
	Stack(size_t initialSize = 0)
		: m_size(initialSize == 0 ? DEFAULT_SIZE : initialSize),
		m_pArray(new T[this->m_size]),
		m_top(0) {}

	~Stack()
	{
		delete[] this->m_pArray;
	}

	// Member functions
	inline bool isFull() const
	{
		return m_top == m_size;
	}

	void push(const T& data)
	{
		if (this->isFull())
			moveToBiggerArray();

		this->m_pArray[this->m_top++] = data;
	}

	T pop()
	{
		assertIsNotEmpty();

		return this->m_pArray[this->m_top--];
	}

	void clear()
	{
		this->m_top = 0;
	}

	// Friends
	friend std::ostream& operator<<(std::ostream& os, const Stack<T>& src)
	{
		// Allows std::cout to print Stack contents
		os << "__TOP__\n";

		for (size_t i = src.m_top; i-- > 0;)
			os << src.m_pArray[i] << '\n';

		return os;
	}
};