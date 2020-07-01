#include<iostream>
#include<deque>
#include"maxHeap.h"
#include"myExceptions.h"

using namespace std;

int main() {
	std::deque<int> a{ -3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17 };
	maxHeap<int> h;
	h.initialize(a);         // 将元素初始化为最大堆的结构
	try {
		cout << h.top() << endl;
	}
	catch (exception& e) {
		cout << e.what();
		exit(-1);
	}
	cout << h.size() << endl;
	cout << h.isEmpty() << endl;
	cout << h << endl;
}
