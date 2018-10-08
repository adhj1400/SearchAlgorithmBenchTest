#pragma once

#include <vector>
#include <deque>
#include <iostream>

class skipSearcher
{
public:
	skipSearcher();
	~skipSearcher();

	bool find(int key);
	void fill(std::vector<int>&, int);
	void insert(int val);
	void remove(int key);
	void print();
	void destroyList();

private:
	bool coinFlip();
	void setHead(int);

	struct node {
		node(int value, node* right = nullptr, node* down = nullptr) {
			this->value = value;
			this->right = right;
			this->down = down;
		}

		int value;
		int level;
		node* right;
		node* down;
	};

	node* head;
	int height = 0;
};

