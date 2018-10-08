#pragma once

#include <vector>

class binarySearcher
{
public:
	binarySearcher();
	~binarySearcher();

	bool search(std::vector<int>& list, int target, int N); // sök

};

