#include "stdafx.h"
#include "hashSearcher.h"

hashSearcher::hashSearcher(int bucket) : bucketSize(bucket) {
	hash_table.resize(bucket);
}

hashSearcher::~hashSearcher() {}

void hashSearcher::fill(std::vector<int>& list, int N) {
	for (int x = 0; x < N; x++)		insert(list[x]);
}

int hashSearcher::get(int value) {
	// Decide which bucket we should start searching in
	int key = hash(value);

	// Search the bucket
	for (int x = 0; x < hash_table[key].size(); x++) {
		if (hash_table[key][x].getValue() == value)	return hash_table[key][x].getValue();
	}

	return 0;
}

int hashSearcher::hash(int key) {
	return key % bucketSize; 
}

void hashSearcher::insert(int value) {
	// Get hash (encrypt)
	int key = hash(value);

	// Search the entire column
	for (int x = 0; x < hash_table[key].size(); x++) {
		if (hash_table[key][x].getValue() == value) return;	 // The key-value pair already exists: return
	}

	// Push on top of vector
	Entry newEntry(key, value);
	hash_table[key].push_back(newEntry);
}

bool hashSearcher::find(int x) { 
	return get(x);
}

void hashSearcher::print() {
	for (int x = 0; x < hash_table.size(); x++) {
		std::cout << "Bucket #" << x << ": ";
		for (int y = 0; y < hash_table[x].size(); y++) {
			if (y > 0)
				std::cout << ", ";
			std::cout << hash_table[x][y].getValue();
		}
		std::cout << std::endl;
	}
}
