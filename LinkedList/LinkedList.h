#pragma once

#include <iostream>


template<typename T>
class LinkedList
{
private:
	class Node
	{
		friend LinkedList<T>;

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
	};

	Node *m_pfirstNode;

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

	Node* lastNode() const
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
	class iterator
	{
		friend class LinkedList<T>;

	private:
		Node* m_pNode;

	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator(Node* pfirstNode)
			: m_pNode(pfirstNode) {}

		reference operator*()
		{
			return this->m_pNode->m_data;
		}

		pointer operator->()
		{
			return &this->m_pNode->m_data;
		}

		iterator& operator++()
		{
			this->m_pNode = this->m_pNode->m_pnextNode;
			return *this;
		}

		// Post increment
		iterator operator++(int)
		{
			auto tmp = *this;
			++this;
			return tmp;
		}

		friend bool operator==(const iterator& a, const iterator& b) { return a.m_pNode == b.m_pNode; };
		friend bool operator!=(const iterator& a, const iterator& b) { return a.m_pNode != b.m_pNode; };
	};

	class const_iterator
	{
		friend class LinkedList<T>;

	private:
		Node* m_pNode;

	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T* const;
		using reference = const T &;

		const_iterator(Node* pfirstNode)
			: m_pNode(pfirstNode) {}

		reference operator*()
		{
			return this->m_pNode->m_data;
		}

		pointer operator->()
		{
			return &this->m_pNode->m_data;
		}

		const_iterator& operator++()
		{
			this->m_pNode = this->m_pNode->m_pnextNode;
			return *this;
		}

		// Post increment
		const_iterator operator++(int)
		{
			auto tmp = *this;
			++this;
			return tmp;
		}

		friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.m_pNode == b.m_pNode; };
		friend bool operator!=(const const_iterator& a, const const_iterator& b) { return a.m_pNode != b.m_pNode; };
	};

	iterator begin()
	{
		return iterator(this->m_pfirstNode);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator cbegin() const
	{
		return const_iterator(this->m_pfirstNode);
	}

	const_iterator cend() const
	{
		return const_iterator(nullptr);
	}

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
		auto pnewNode = new Node(data);
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
			this->m_pfirstNode = new Node(data);
		else
			plastNode->next(new Node(data));
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