#include <iostream>
#include "MyList.h"
#include<list>

int main()
{
	MyList <int>testList{};
	testList.pushBack(1);
	testList.pushBack(2);
	testList.pushFront(3);
	testList.pushBack(4);
	testList.emplace(0, 10);
	testList[1] = 20;

	testList.front() = 22;
	MyList <int>testList2{ testList };

	testList2 = testList;

	testList[0] = 33;
	testList2[0] = 11;
	
	
	std::list<int> qwe{ 0,1,2,3 };
	qwe.resize(10000000,1);
	
	int b[3]{ 1,2,3 };

	
	return 0;
}