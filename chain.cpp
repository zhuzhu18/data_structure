#include<iostream>
#include<ostream>
#include<sstream>
#include"utils.h"

template<typename T>
struct ChainNode {
	T element;
	ChainNode<T>* next;

	ChainNode() {};
	ChainNode(const T& e) { element = e; next = nullptr; };
	ChainNode(const T& e, const ChainNode* next) { element = e;this->next = next; }
};

template<class T>
class chain {
public:
	chain(int capacity=10);
	chain(const chain<T>& c);
	~chain();

	bool empty() const { return listSize == 0; }
	int size()const { return listSize; }
	T& get(int index)const;
	int indexOf(const T& theElement)const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out)const;
	friend std::ostream& operator<<(std::ostream& os, const chain<T>& x);

private:
	int listSize;
	ChainNode<T>* firstNode;
	void checkIndex(const int theIndex)const;
};

template<class T>
chain<T>::chain(int initialCapacity) {
	if (initialCapacity < 1) {
		std::stringstream s;
		s << "Initial capacity = " << initialCapacity << "Must be > 0.";
		throw illegalParameterValue(s.str().c_str());
	}
	firstNode = nullptr;
	listSize = 0;
}

template<typename T>
chain<T>::chain(const chain<T>& theList) {
	listSize = theList.listSize;
	if (listSize == 0) {
		firstNode = nullptr;
		return;
	}
	ChainNode* sourceNode = theList.firstNode;            // sourceNode指向即将要拷贝的那个节点
	firstNode = new ChainNode(sourceNode->element);          // 若listSize > 1, 则创建第一个节点
	ChainNode<T>* targetNode = firstNode;           // targetNode指向拷贝后的那个节点
	sourceNode = sourceNode->next;
	while (sourceNode != nullptr) {
		targetNode->next = new ChainNode(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
}

template<class T>
chain<T>::~chain() {
	while(firstNode)
	{
		ChainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
T& chain<T>::get(const int index)const {
	checkIndex(index);
	ChainNode<T>* currentNode = firstNode;
	for (auto i = 0; i < index;i++) {
		currentNode = currentNode->next;
	}
	return currentNode->element;
}

template<class T>
int chain<T>::indexOf(const T& theElement)const {
	ChainNode<T>* currentNode = firstNode;
	int index{ 0 };
	while (currentNode != nullptr && currentNode->element != theElement) {
		currentNode = currentNode->next;
		index++;
	}
	if (!currentNode)
		return -1;
	else
		return index;
}

template<class T>
void chain<T>::erase(int theIndex) {
	checkIndex(theIndex);
	ChainNode<T>* deleteNode = firstNode;
	if (theIndex == 0) { firstNode = deleteNode->next; }
	else {
		int index{ 0 };
		ChainNode<T>* p = firstNode;       // p指向要删除节点的上一节点
		while (index < theIndex-1 && index < listSize) {
			p = p->next;
			index++;
		}
		deleteNode = p->next;
		p->next = deleteNode->next;
	}
	delete deleteNode;
	listSize--;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement) {
	if (theIndex < 0 || theIndex > listSize) {
		std::stringstream s;
		s << "index = " << theIndex << ", listSize = " << listSize;
		throw illegalParameterValue(s.str().c_str());
	}
	if (theIndex == 0) { 
		ChainNode<T>* insertNode = new ChainNode<T>(theElement); 
		insertNode->next = firstNode;
		firstNode = insertNode;
	}
	else {
		ChainNode<T>* p = firstNode;
		for (int index = 0;index < theIndex-1;index++)
			p = p->next;
		ChainNode<T>* insertNode = new ChainNode<T>(theElement);
		insertNode->next = p->next;
		p->next = insertNode;
	}
	listSize++;
}

template<class T>
void chain<T>::output(std::ostream& os) const{
	auto currentNode = firstNode;
	for (;currentNode != nullptr;currentNode = currentNode->next) {
		os << currentNode->element << " ";
	}
}
// friend std::ostream& operator<<(std::ostream& os, const chain<T>& x)
template<typename T>
std::ostream& operator<<(std::ostream& os, chain<T>& x) {
	x.output(os);
	return os;
}

template<class T>
void chain<T>::checkIndex(const int theIndex) const{
	if (theIndex<0 || theIndex > listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << ", Invalid!!";
		throw illegalParameterValue(s.str().c_str());
	}
}

int main() {
	chain<int> p;
	for (auto i = 0;i < 10;i++) {
		p.insert(i, 10 - i);
	}
	std::cout << p.empty() << '\n';
	std::cout << p.size() << '\n';
	std::cout << p.get(4) << '\n';
	std::cout << p.indexOf(5) << '\n';
	p.erase(4);
	std::cout << p << std::endl;
}
