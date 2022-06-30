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
	size_t quantityNodes_{};
	Node<T>* head_{};
	Node<T>* tail_{};

	Node<T>* getNode(size_t const index) const;
	Node<T>* getNodeStartFromHead(size_t const index) const;
	Node<T>* getNodeStartFromTail(size_t const index) const;
public:
	MyList();
	MyList(size_t const size);
	MyList(size_t const size, const T& value);
	MyList(const MyList& temp);
	MyList(MyList&& temp);

	MyList<T>& operator=(const MyList& temp);
	MyList<T>& operator=(MyList&& temp);

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

	T& operator[](size_t const index);
	const T& operator[](size_t const index) const;



	Node<T>& front();
	const Node<T>& front() const;
	Node<T>& back();
	const Node<T>& back() const;
};

template<typename T>
inline Node<T>* MyList<T>::getNode(size_t const index) const
{
	if (index >= quantityNodes_)
	{
		throw ("Out of range");
	}
	Node<T>* outNode{};
	if (quantityNodes_ / 2 > index)
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
	Node<T> *outNode{ head_ };
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
	Node<T>* outNode{ tail_ };
	for (size_t i{ quantityNodes_ - 1 };; --i)
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
	Node<T>* activTempNode{ temp.head_ };
	while (temp.quantityNodes_ > quantityNodes_)
	{
		pushBack(activTempNode->value);
		activTempNode = activTempNode->nextNode;
	}
}

template<typename T>
inline MyList<T>::MyList(MyList&& temp)
{
	quantityNodes_ = temp.quantityNodes_;
	head_ = temp.head_;
	tail_ = temp.tail_;
	temp.quantityNodes_ = 0;
}

template<typename T>
inline MyList<T>& MyList<T>::operator=(const MyList& temp)
{
	while (quantityNodes_ > temp.quantityNodes_)
		popBack();

	Node<T>* activTempNode{ temp.head_ };
	Node<T>* activNode{ head_ };
	for (size_t copiedNodes{}; quantityNodes_ > copiedNodes; ++copiedNodes)
	{
		activNode->value = activTempNode->value;
		activTempNode = activTempNode->nextNode;
		activNode = activNode->nextNode;
	}

	while (quantityNodes_ < temp.quantityNodes_)
	{
		pushBack(activTempNode->value);
		activTempNode = activTempNode->nextNode;
	}

	return *this;
}

template<typename T>
inline MyList<T>& MyList<T>::operator=(MyList&& temp)
{
	head_ = temp.head_;
	tail_ = temp.tail_;
	quantityNodes_ = temp.quantityNodes_;

	temp.quantityNodes_ = 0;
}

template<typename T>
inline MyList<T>::~MyList()
{
	clear();
}

template<typename T>
inline void MyList<T>::assign(size_t const newSize, const T& value)
{
	Node<T>* activNode{ head_ };
	if (quantityNodes_ > newSize)
	{
		for (size_t i{}; i < newSize; ++i)
		{
			activNode->value = value;
			activNode = activNode->nextNode;
		}
		while (quantityNodes_ > newSize)
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
		while (newSize > quantityNodes_)
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
	if (tail_ == nullptr)
	{
		tail_ = newTail;
		head_ = newTail;
	}
	else
	{
		newTail->previousNode = tail_;
		tail_->nextNode = newTail;
		tail_ = newTail;
	}
	++quantityNodes_;
}

template<typename T>
inline void MyList<T>::pushFront(const T& newValue)
{
	Node<T>* newHead{ new Node<T>{} };
	newHead->value = newValue;
	if (head_ == nullptr)
	{
		tail_ = newHead;
		head_ = newHead;
	}
	else
	{
		newHead->nextNode = head_;
		head_->previousNode = newHead;
		head_ = newHead;
	}
	++quantityNodes_;
}

template<typename T>
inline void MyList<T>::emplace(size_t const index, const T& newValue)
{
	if (index == 0)
	{
		pushFront(newValue);
	}
	else if (index == quantityNodes_ - 1)
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
	if (head_ == tail_)
	{
		delete tail_;
		tail_ = nullptr;
		head_ = nullptr;
		quantityNodes_ = 0;
	}
	else
	{
		Node<T>* newTail{};
		newTail = tail_->previousNode;
		newTail->nextNode = nullptr;
		delete tail_;
		tail_ = newTail;
		--quantityNodes_;
	}
}

template<typename T>
inline void MyList<T>::popFront()
{
	if (head_ == tail_)
	{
		delete head_;
		tail_ = nullptr;
		head_ = nullptr;
		quantityNodes_ = 0;
	}
	else
	{
		Node<T>* newHead{};
		newHead = head_->nextNode;
		newHead->previousNode = nullptr;
		delete head_;
		head_ = newHead;
		--quantityNodes_;
	}
}

template<typename T>
inline void MyList<T>::erase(size_t const index)
{
	
	if (index == 0)
	{
		popFront();
	}
	else if (index == quantityNodes_ - 1)
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
		--quantityNodes_;
	}
}

template<typename T>
inline void MyList<T>::clear()
{
	while (quantityNodes_)
	{
		popBack();
	}
}


template<typename T>
inline size_t MyList<T>::size() const
{
	return quantityNodes_;
}

template<typename T>
inline bool MyList<T>::empty() const
{
	if (quantityNodes_ == 0)
		return true;
	else
		return false;
}

template<typename T>
inline void MyList<T>::resize(size_t const newSize)
{
	if (newSize >= quantityNodes_)
	{
		while (newSize > quantityNodes_)
		{
			pushBack(T{});
		}
	}
	else
	{
		while (newSize < quantityNodes_)
		{
			popBack();
		}
	}
}

template<typename T>
inline void MyList<T>::resize(size_t const newSize, T const value)
{
	if (newSize >= quantityNodes_)
	{
		while (newSize > quantityNodes_)
		{
			pushBack(value);
		}
	}
	else
	{
		while (newSize < quantityNodes_)
		{
			popBack();
		}
	}
}

template<typename T>
inline T& MyList<T>::operator[](size_t const index)
{
	Node<T>* neededNode{ getNode(index) };
	return neededNode->value;
}

template<typename T>
inline const T& MyList<T>::operator[](size_t const index) const
{
	Node<T>* neededNode{ getNode(index) };
	return neededNode->value;
}

template<typename T>
inline Node<T>& MyList<T>::front()
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return head_->value;
}

template<typename T>
inline const Node<T>& MyList<T>::front() const
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return head_->value;
}

template<typename T>
inline Node<T>& MyList<T>::back()
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return tail_->value;
}

template<typename T>
inline const Node<T>& MyList<T>::back() const
{
	if (quantityNodes_ == 0)
		throw ("list emplace");
	return tail_->value;
}