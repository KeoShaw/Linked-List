#pragma once
//This class is not tested, do not use without further testing of all methods.



template<typename T>
struct Node {
	T data;
	Node *nextNode;
};


//This class is not tested, do not use without further testing of all methods.
template<typename T>
class List {
public:
	List();
	List(const T& data); //Initialises with first data element.
	List(const List& toCopy); //Copy constructor
	List& operator =(const List& toAssign);
	~List();

	void Add(const T& data); //Inserts data to end of list.
	bool Delete(const T& todelete); //Deletes all nodes which match toDelete (== operator must be defined for T).
	bool Search(const T& toFind) const; //Checks if data exists in List and returns true if so. 
	unsigned GetSize() const; //Returns size of list.
	T& operator [](unsigned index); //returns element (type T) at position i
	const T& operator [](unsigned index) const; //^^

private:
	Node<T> *node;
	unsigned length;
	void duplicateList(const Node<T> *copyList); //Assumes the current object has already been erased
	void eraseList();
};

template<typename T>
List<T>::List() : node(nullptr), length(0) {}

template<typename T>
List<T>::List(const T& data) : length(1) {
	node = new Node<T>;
	node.data = data;
	node.nextNode = nullptr;
}

template<typename T>
List<T>::List(const List& toCopy) {
	this->length = toCopy.length;
	this->duplicateList(toCopy.node);
}

template<typename T>
List<T>& List<T>::operator =(const List<T>& toAssign) {
	if (this != &toAssign) {
		this->eraseList();
		this->duplicateList(toAssign.node);
		this->length = toAssign.length;
	}
	return *this;
}

template<typename T>
List<T>::~List() {
	eraseList();
}

template<typename T>
void List<T>::Add(const T& data) {
	Node<T> *newNode = new Node<T>;
	newNode->data = data;
	newNode->nextNode = nullptr;

	if (length == 0) {
		node = newNode;
		length = 1;
	}
	else {
		Node<T> *currNode = node;
		while (currNode->nextNode != nullptr) {
			currNode = node->nextNode;
		}
		currNode->nextNode = newNode;
		length++;
	}
}

template<typename T>
bool List<T>::Delete(const T& toDelete) {
	if (length == 0) return false;
	Node<T> *currNode = node;
	Node<T> *prevNode = nullptr;
	
	while (currNode->nextNode != nullptr) { //If the node to be deleted is anywhere in the middle of the list (not beginning or end)
		if (currNode->data == toDelete) {
			if (prevNode == nullptr) { //If the node to be deleted is at the beginning of the list.
				prevNode = currNode;
				currNode = node = currNode->nextNode;
				delete prevNode;
				prevNode = nullptr;
			}


			currNode = currNode->nextNode;
			delete prevNode->nextNode;
			prevNode->nextNode = currNode;
			length--;
		}
		else {
			prevNode = currNode;
			currNode = currNode->nextNode;
		}
	}

	if (currNode->data == toDelete) { //If the node to be deleted is at the end of the list
		delete currNode;
		prevNode->nextNode = nullptr;
		length--;
	}
}

template<typename T>
bool List<T>::Search(const T& toFind) const {
	Node<T> *currNode = node;
	while (currNode->nextNode != nullptr) {
		if (currNode->data == toFind) return true;

		currNode = currNode->nextNode;
	}
	if (currNode->data == toFind) return true;
	else return false;
}

template<typename T>
unsigned List<T>::GetSize() const {
	return length;
}

template<typename T>
void List<T>::duplicateList(const Node<T> *copyList) {
	if (copyList != nullptr) {
		const Node<T> *currNode = copyList; 
		Node<T> *baseNode = new Node<T>, *prevNode = baseNode;

		baseNode->data = currNode->data;
		baseNode->nextNode = nullptr;

		while (currNode->nextNode != nullptr) {
			currNode = currNode->nextNode;
			Node<T> *tempNode = new Node;
			tempNode->data = currNode->data;
			tempNode->nextNode = nullptr;
			prevNode->nextNode = tempNode;
			prevNode = currNode;
		}

		node = baseNode;
	}
}

template<typename T>
void List<T>::eraseList() {
	if (node != nullptr) {
		Node<T> *currNode = node, *nextNode = nullptr;

		while (currNode->nextNode != nullptr) {
			nextNode = currNode->nextNode;
			delete currNode;
			currNode = nextNode;
		}

		delete currNode;
	}
}

template<typename T>
T& List<T>::operator [](unsigned index) {
	Node<T> *currNode = node;

	for (int i = 0; i <= index; i++) {
		if (currNode->nextNode == nullptr) {
			return currNode->data;
		}
		else if(i < index) {
			currNode = currNode->nextNode;
		}
		else {
			return currNode->data;
		}
	}
}

template<typename T>
const T& List<T>::operator [](unsigned index) const {
	Node<T> *currNode = node;

	for (int i = 0; i <= index; i++) {
		if (currNode->nextNode == nullptr) {
			return currNode->data;
		}
		else if (i < index) {
			currNode = currNode->nextNode;
		}
		else {
			return currNode->data;
		}
	}
}