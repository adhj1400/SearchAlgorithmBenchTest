#include "stdafx.h"
#include "binarySearcher.h"
#include <iostream>


binarySearcher::binarySearcher()
{
}


binarySearcher::~binarySearcher()
{
}


/*
*  Binary search in <list> for <target> within range N.
*/
bool binarySearcher::search(std::vector<int>& list, int target, int N) 
{
	int L = 0;	// Floor
	int R = N;  // Roof

	if (list.size() > N) {
		for (int m = (L + R) / 2; L <= R; m = (L + R) / 2) {
			if (m < 0 || m > N)			break;
			else if (list[m] == target) return true;
			else if (list[m] < target)	L = m + 1;
			else if (list[m] > target)	R = m - 1;
		}
	} else std::cerr << "Vector out of range in binarySearcher.cpp";

	return false;
}