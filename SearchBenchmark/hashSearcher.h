/*
*	Author:			Adam Hjernquist
*	Performance:	O(1) time compexity. Performance is affected by <hash_table> size.
*/
#pragma once
#include <vector>
#include <iostream>

class hashSearcher {
public:
	hashSearcher(int);
	~hashSearcher();
	int get(int);
	void insert(int);
	bool find(int);
	void fill(std::vector<int>&, int);	// Fill <hash_table> with contents of vector.
	void print();	// For debug purposes

private:
	int hash(int);
	int bucketSize;	// The size of each buckets. Bigger bucket size == better performance.

	struct Entry {
		int key, val;
		int getKey() { return key; }
		int getValue() { return val; }

		Entry(int key, int value) { 
			this->key = key; 
			this->val = value; 
		}
	};
	std::vector<std::vector<Entry> > hash_table;		// The table
};

