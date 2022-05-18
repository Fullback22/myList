#pragma once
template <typename T>
struct Node
{
	Node* nextNode{};
	Node* previousNode{};
	T value{};
};

template <typename T>
class MyList
{
	size_t _quantityNodes{};
	Node<T>* _head{};
	Node<T>* _tail{};

	Node<T>* getNode(size_t const index) const;
	Node<T>* getNodeStartFromHead(size_t const index) const;
	Node<T>* getNodeStartFromTail(size_t const index) const;
public:
	MyList();
	MyList(size_t const size);
	MyList(size_t const size, const T& value);
	MyList(const MyList& temp);
	~MyList();

	void assign(size_t const newSize, const T& value);

	void pushBack(const T& newValue);
	void pushFront(const T& newValue);
	void emplace(size_t const index, const T& newValue);

	void popBack();
	void popFront();
	void erase(size_t const index);
	void clear();

	size_t size() const;
	bool empty() const;

	void resize(size_t const newSize);
	void resize(size_t const newSize, T const value);

	T& operator[](size_t const& index);

	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
};

template<typename T>
inline Node<T>* MyList<T>::getNode(size_t const index) const
{
	if (index >= _quantityNodes)
	{
		throw ("Out of range");
	}
	Node<T>* outNode{};
	if (_quantityNodes / 2 > index)
	{
		outNode = getNodeStartFromTail(index);
	}
	else
	{
		outNode = getNodeStartFromHead(index);
	}
	return outNode;
}

template<typename T>
inline Node<T>* MyList<T>::getNodeStartFromHead(size_t const index) const
{
	Node<T> *outNode{ _head };
	for (size_t i{};; ++i)
	{
		if (i == index)
			return outNode;
		else
			outNode = outNode->nextNode;
	}
}

template<typename T>
inline Node<T>* MyList<T>::getNodeStartFromTail(size_t const index) const
{
	Node<T>* outNode{ _tail };
	for (size_t i{ _quantityNodes - 1 };; --i)
	{
		if (i == index)
			return outNode;
		else
			outNode = outNode->previousNode;
	}
	return nullptr;
}


template<typename T>
inline MyList<T>::MyList()
{
}

template<typename T>
inline MyList<T>::MyList(size_t const size)
{
	resize(size);
}

template<typename T>
inline MyList<T>::MyList(size_t const size, const T& value)
{
	resize(size, value);
}

template<typename T>
inline MyList<T>::MyList(const MyList& temp)
{
	Node<T>* activTempNode{ temp._head };
	while (temp._quantityNodes > _quantityNodes)
	{
		pushBack(activTempNode->value);
		activTempNode = activTempNode->nextNode;
	}
}

template<typename T>
inline MyList<T>::~MyList()
{
	clear();
}

template<typename T>
inline void MyList<T>::assign(size_t const newSize, const T& value)
{
	Node<T>* activNode{ _head };
	if (_quantityNodes > newSize)
	{
		for (size_t i{}; i < newSize; ++i)
		{
			activNode->value = value;
			activNode = activNode->nextNode;
		}
		while (_quantityNodes > newSize)
		{
			popBack();
		}
	}
	else
	{
		while (activNode != nullptr)
		{
			activNode->value = value;
			activNode = activNode->nextNode;
		}
		while (newSize > _quantityNodes)
		{
			pushBack(value);
		}
	}
}

///ADD ELEMENTS
template<typename T>
inline void MyList<T>::pushBack(const T& newValue)
{
	Node<T>* newTail{new Node<T>{}};
	newTail->value = newValue;
	if (_tail == nullptr)
	{
		_tail = newTail;
		_head = newTail;
	}
	else
	{
		newTail->previousNode = _tail;
		_tail->nextNode = newTail;
		_tail = newTail;
	}
	++_quantityNodes;
}

template<typename T>
inline void MyList<T>::pushFront(const T& newValue)
{
	Node<T>* newHead{ new Node<T>{} };
	newHead->value = newValue;
	if (_head == nullptr)
	{
		_tail = newHead;
		_head = newHead;
	}
	else
	{
		newHead->nextNode = _head;
		_head->previousNode = newHead;
		_head = newHead;
	}
	++_quantityNodes;
}

template<typename T>
inline void MyList<T>::emplace(size_t const index, const T& newValue)
{
	if (index == 0)
	{
		pushFront(newValue);
	}
	else if (index == _quantityNodes - 1)
	{
		pushBack(newValue);
	}
	else
	{
		Node<T>* changeableNode{ getNode(index) };
		Node<T>* nodeBeforeDeingChangeable{ changeableNode->previousNode };

		Node<T>* newNode{ new Node<T>{} };
		newNode->value = newValue;
		newNode->nextNode = changeableNode;
		newNode->previousNode = nodeBeforeDeingChangeable;

		nodeBeforeDeingChangeable->nextNode = newNode;
		changeableNode->previousNode = newNode;
	}
}

///DELETED ELEMENTS
template<typename T>
inline void MyList<T>::popBack()
{
	if (_head == _tail)
	{
		delete _tail;
		_tail = nullptr;
		_head = nullptr;
		_quantityNodes = 0;
	}
	else
	{
		Node<T>* newTail{};
		newTail = _tail->previousNode;
		newTail->nextNode = nullptr;
		delete _tail;
		_tail = newTail;
		--_quantityNodes;
	}
}

template<typename T>
inline void MyList<T>::popFront()
{
	if (_head == _tail)
	{
		delete _head;
		_tail = nullptr;
		_head = nullptr;
		_quantityNodes = 0;
	}
	else
	{
		Node<T>* newHead{};
		newHead = _head->nextNode;
		newHead->previousNode = nullptr;
		delete _head;
		_head = newHead;
		--_quantityNodes;
	}
}

template<typename T>
inline void MyList<T>::erase(size_t const index)
{
	
	if (index == 0)
	{
		popFront();
	}
	else if (index == _quantityNodes - 1)
	{
		popBack();
	}
	else
	{
		Node<T>* deletedNode{ getNode(index) };
		Node <T>* nodeBeforeBeingDeleted{ deletedNode->previousNode };
		Node <T>* nodeAfterBeingDeleted{ deletedNode->nextNode };

		nodeBeforeBeingDeleted->nextNode = deletedNode->nextNode;
		nodeAfterBeingDeleted->previousNode = deletedNode->previousNode;
		delete deletedNode;
		--_quantityNodes;
	}
}

template<typename T>
inline void MyList<T>::clear()
{
	while (_quantityNodes)
	{
		popBack();
	}
}


template<typename T>
inline size_t MyList<T>::size() const
{
	return _quantityNodes;
}

template<typename T>
inline bool MyList<T>::empty() const
{
	if (_quantityNodes == 0)
		return true;
	else
		return false;
}

template<typename T>
inline void MyList<T>::resize(size_t const newSize)
{
	if (newSize >= _quantityNodes)
	{
		while (newSize > _quantityNodes)
		{
			pushBack(T{});
		}
	}
	else
	{
		while (newSize < _quantityNodes)
		{
			popBack();
		}
	}
}

template<typename T>
inline void MyList<T>::resize(size_t const newSize, T const value)
{
	if (newSize >= _quantityNodes)
	{
		while (newSize > _quantityNodes)
		{
			pushBack(value);
		}
	}
	else
	{
		while (newSize < _quantityNodes)
		{
			popBack();
		}
	}
}

template<typename T>
inline T& MyList<T>::operator[](size_t const& index)
{
	Node<T>* neededNode{ getNode(index) };
	return neededNode->value;
}

template<typename T>
inline T& MyList<T>::front()
{
	if (_quantityNodes == 0)
		throw ("list emplace");
	return _head->value;
}

template<typename T>
inline const T& MyList<T>::front() const
{
	if (_quantityNodes == 0)
		throw ("list emplace");
	return _head->value;
}

template<typename T>
inline T& MyList<T>::back()
{
	if (_quantityNodes == 0)
		throw ("list emplace");
	return _tail->value;
}

template<typename T>
inline const T& MyList<T>::back() const
{
	if (_quantityNodes == 0)
		throw ("list emplace");
	return _tail->value;
}