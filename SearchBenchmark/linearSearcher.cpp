#include "stdafx.h"
#include "linearSearcher.h"
#include <iostream>


linearSearcher::linearSearcher()
{
}


linearSearcher::~linearSearcher()
{
}


/*
* Search in <list> for <target> within a partition of size <N>.
*/
bool linearSearcher::search(std::vector<int>& list, int target, int& N) {

	if (list.size() > N) {
		for (int j = 0; j < N; j++) {
			if (list[j] == target) return true; 
		}
	} else std::cerr << "Vector out of range i linearSearcher.cpp";

	return false;   // Not found.
}