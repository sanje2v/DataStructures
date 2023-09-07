#pragma once

#include <iostream>


template<typename T>
class LinkedList;

template<typename T>
class Node
{
private:
	T m_data;
	Node* m_pnextNode;

public:
	Node(const T& data)
		: m_data(data), m_pnextNode(nullptr) {}

	T data() const
	{
		return this->m_data;
	}

	void data(const T& data)
	{
		this->m_data = data;
	}

	Node* next() const
	{
		return this->m_pnextNode;
	}

	void next(Node* const node)
	{
		this->m_pnextNode = node;
	}

	friend LinkedList<T>;
};


template<typename T>
class LinkedList
{
private:
	Node<T> *m_pfirstNode;

	void freeAll()
	{
		auto pnextNode = this->m_pfirstNode;

		while (pnextNode)
		{
			auto pnextnextNode = pnextNode->next();
			delete pnextNode;
			pnextNode = pnextnextNode;
		}

		this->m_pfirstNode = nullptr;
	}

	Node<T>* lastNode() const
	{
		auto pnextNode = this->m_pfirstNode;
		if (!pnextNode)
			return nullptr;

		while (pnextNode->next())
			pnextNode = pnextNode->next();

		return pnextNode;
	}

	inline void assertNotEmpty() const
	{
		if (!this->m_pfirstNode)
			throw std::runtime_error("Linked list is empty!");
	}

public:
	LinkedList()
		: m_pfirstNode(nullptr) {}

	// Copy constructor
	LinkedList(const LinkedList<T>& src)
	{
		this->freeAll();

		auto psrcNext = src.m_pfirstNode;
		auto ppdestNext = &this->m_pfirstNode;
		while (psrcNext)
		{
			*ppdestNext = new Node<T>(psrcNext->data());
			ppdestNext = &(*ppdestNext)->next();
		}
	}

	// Move constructor
	LinkedList(LinkedList<T>&& src)
	{
		this->freeAll();

		this->m_pfirstNode = src.m_pfirstNode;
		src.m_pfirstNode = nullptr;
	}

	~LinkedList()
	{
		this->freeAll();
	}

	// Member functions
	void append(LinkedList<T>& src)
	{
		auto plastNode = this->lastNode();
		if (!plastNode)
			this->m_pfirstNode = src.m_pfirstNode;
		else
			plastNode->m_pNext = src.m_pfirstNode;

		src.m_pfirstNode = nullptr;
	}

	void insertFirst(const T& data)
	{
		auto pnewNode = new Node<T>(data);
		pnewNode->next(this->m_pfirstNode);
		this->m_pfirstNode = pnewNode;
	}

	void insertMiddle(const T& data)
	{

	}

	void insertLast(const T& data)
	{
		auto plastNode = this->lastNode();
		if (!plastNode)
			this->m_pfirstNode = new Node<T>(data);
		else
			plastNode->next(new Node<T>(data));
	}

	void removeFirst()
	{
		this->assertNotEmpty();

		auto pfirstNode = this->m_pfirstNode;
		this->m_pfirstNode = this->m_pfirstNode->next();
		delete pfirstNode;
	}

	void removeMiddle()
	{

	}

	void removeLast()
	{
		this->assertNotEmpty();

		decltype(this->m_pfirstNode) pnextNode = nullptr;
		auto pnextnextNode = this->m_pfirstNode;
		while (pnextnextNode->next())
		{
			pnextNode = pnextnextNode;
			pnextnextNode = pnextnextNode->next();
		}

		if (!pnextNode)
		{
			delete this->m_pfirstNode;
			this->m_pfirstNode = nullptr;
		}
		else
		{
			delete pnextNode->m_pnextNode;
			pnextNode->m_pnextNode = nullptr;
		}
	}

	void reverse()
	{
		this->assertNotEmpty();

		decltype(this->m_pfirstNode) pnextNode = nullptr;
		auto pnextnextNode = this->m_pfirstNode;
		while (pnextnextNode)
		{
			auto pnextnextnextNode = pnextnextNode->next();
			pnextnextNode->next(pnextNode);
			pnextNode = pnextnextNode;
			pnextnextNode = pnextnextnextNode;
		}

		this->m_pfirstNode = (pnextNode ? pnextNode : pnextnextNode);
	}

	// Friends
	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& src)
	{
		// Allows std::cout to print LinkedList contents
		auto pNextNode = src.m_pfirstNode;
		while (pNextNode)
		{
			os << pNextNode->data() << "->";
			pNextNode = pNextNode->next();
		}

		os << "NULL";

		return os;
	}
};