#pragma once
#include<ostream>
#include<sstream>
#include<deque>
#include"myExceptions.h"

using namespace std;
#define MAXDATA 10000

template<class T>
class maxHeap {
public:
	maxHeap();
	bool isEmpty()const { return heapSize == 0; }
	int size()const { return heapSize; }
	const T& top() {
		if (heapSize == 0)
			throw queueEmpty();
		return heap[1];
	}
	T pop();
	void push(const T&);
	void initialize(std::deque<T>);
	void output(std::ostream& out)const;
	template<class T>
	friend std::ostream& operator<<(std::ostream&, const maxHeap<T>&);
	std::deque<T> heap;
private:
	int heapSize;
};

template<class T>
maxHeap<T>::maxHeap() {
	heap = {MAXDATA};
	heapSize = 0;
}

template<class T>
T maxHeap<T>::pop() {
	if (heapSize == 0) {
		std::ostringstream s;
		s << "heap is empty, can not pop\n";
		throw illegalParameterValue(s.str());
	}
	T popElement = heap[1];
	T lastElement = heap[heapSize];           // 取出最后一个元素的值，将它放在合适的位置
	heap.pop_back();
	heapSize--;
	if (heapSize == 0)return popElement;
	int current_pos = 1;              // 指示最后一个节点应该放的位置
	int child = 2 * current_pos;
	while (2*current_pos <= heapSize) {
		child = 2 * current_pos;
		if (heapSize > child && heap[child + 1] > heap[child])
			child++;
		if (lastElement >= heap[child])
			break;
		heap[current_pos] = heap[child];
		current_pos = child;
	}
	heap[current_pos] = lastElement;
	return popElement;
}

template<typename T>
void maxHeap<T>::push(const T& theElement) {
	heap.push_back(theElement);
	int current_pos = ++heapSize;
	if (heapSize > 1) {
		int parent_pos = current_pos / 2;
		while (current_pos > 1) {
			parent_pos = current_pos / 2;
			if (theElement <= heap[parent_pos])
				break;
			heap[current_pos] = heap[parent_pos];
			current_pos = parent_pos;
		}
		heap[current_pos] = theElement;
	}
}

template<typename T>
void maxHeap<T>::initialize(std::deque<T> h) {
	heap = h;
	heap.push_front(MAXDATA);
	heapSize = h.size();
	for (auto root = heapSize / 2;root >= 1;root--) {
		T rootElement = heap[root];
		int child = 2 * root;
		while (root*2 <= heapSize) {
			child = 2 * root;
			if (heapSize > child && heap[child + 1] > heap[child])
				child++;
			if (rootElement >= heap[child])
				break;
			heap[root] = heap[child];
			root = child;
		}
		heap[root] = rootElement;
	}
}

template<typename T>
void maxHeap<T>::output(std::ostream& out)const {
	int index{ 1 };
	for (;index<=heapSize;index++)
		out << heap[index] << " ";
}

template<class T>
std::ostream& operator<<(std::ostream& os, const maxHeap<T>& h) {
	h.output(os);
	return os;
}
