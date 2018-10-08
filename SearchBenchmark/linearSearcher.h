#pragma once
#include <vector>

class linearSearcher
{
public:
	linearSearcher();
	~linearSearcher();

	bool search(std::vector<int>&, int, int&);
};

