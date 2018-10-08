#include "stdafx.h"
#include "skipSearcher.h"
#include "time.h"
#include <algorithm>


skipSearcher::skipSearcher() : head(nullptr) {}

skipSearcher::~skipSearcher() {
	destroyList();      // Destroy the entire linked list.
}

void skipSearcher::destroyList() {
	node* ptrX;
	node* ptrY = head;  // Start at head

	while (ptrY != nullptr) {
		ptrX = ptrY;        // Update current row
		ptrY = ptrY->down;   // Move down one row in preparation of next iteration.

		while (ptrX != nullptr) {
			node* ptrDel = ptrX;    // the address space to free (old ptrX)
			ptrX = ptrX->right;      // update ptrX (move to the right)

			delete ptrDel;      // remove old ptrX
		}
	}

	height = 0;
	head = nullptr; // NOTICE: Otherwise <head> will point to a space which is to be freed.
}


void skipSearcher::fill(std::vector<int>& list, int N) {
	for (int x = 0; x < N; x++)  insert(list[x]);
}

bool skipSearcher::coinFlip() {
	return rand() % 2;
}

void skipSearcher::setHead(int val) {
	head = new node(val);
	height++; // öka höjden till 1
	head->level = height;
}

void skipSearcher::insert(int newVal) {
	if (head == nullptr) {
		setHead(newVal);
		return;
	}

	node* ptr = head;   // Start at head
	std::deque<node*> nodeLeaders;  // Containing all leading nodes (potential links) up until the insertion point

	// Find where to insert node
	while (true) {
		if ((ptr->right != nullptr) && (ptr->right->value < newVal)) ptr = ptr->right;   // Move to the right in skip list. Make a "skip".

		else if (ptr->value == newVal)	return;             // Node already exist.

		else if (ptr->down != nullptr) {
			nodeLeaders.push_back(ptr); // We reached row end < newVal, add this node to the list of node leaders
			ptr = ptr->down;    // Move down in skip list. Avoid "skip".
		}

		// We are at our destination.
		else {
			node* newNode = new node(newVal);   // New Node
			ptr->right = newNode;
			newNode->level = 1;

			int thisHeight = 1;

			// Add another layer on top of this node? Let a coin flip decide.
			while (coinFlip()) {
				++thisHeight;

				// If the height is higher than the head, increment it and renew head.
				if (thisHeight > height) {
					node* newHead = new node(head->value);
					newHead->down = head;
					head = newHead;
					height++;
					head->level = height;
					nodeLeaders.push_front(head);   // insert at front
				}

				// Add to height with the same value
				node* aboveNode = new node(newVal);
				aboveNode->down = newNode;
				aboveNode->level = thisHeight;

				// Connect <aboveNode> to the node on it's right (if there is one)
				if (nodeLeaders.size()) {
					node* oldParent = nodeLeaders[nodeLeaders.size() + 1 - thisHeight];

					if (oldParent->right != nullptr)	aboveNode->right = oldParent->right;

					oldParent->right = aboveNode;	// Connect <aboveNode> to the node on it's left (reversed)
				}

				newNode = aboveNode;	// If coinFlip should return true another time, remember this node.
			}

			return;
		}
	}
}

bool skipSearcher::find(int key) {
	node* ptr = head;

	while (true) {
		if (ptr->value == key)												return true;		// Found

		else if ((ptr->right != nullptr) && (ptr->right->value <= key))		ptr = ptr->right;	// Move right

		else if ((ptr->down != nullptr) && (ptr->value != key))				ptr = ptr->down;	// Move down

		else if (ptr->value != key)											return false;		// Not found
	}
}

void skipSearcher::remove(int key) {
	// not yet implemented
}

void skipSearcher::print() {
	std::cout << "Printing the skip list." << std::endl;

	node* ptrX;
	node* ptrY = head;
	std::vector<int> debug;

	while (ptrY != nullptr) {
		ptrX = ptrY;    // updatera rad
		ptrY = ptrY->down;  // flytta ner en rad inför nästa loop

		while (ptrX != nullptr) {
			node* ptrDel = ptrX;    // the address space to free (old ptrX)
			ptrX = ptrX->right;      // update ptrX (move to the right)
			debug.push_back(ptrDel->value);
		}
	}

	std::sort(debug.begin(), debug.end());
	int prev;

	for (std::vector<int>::iterator it = debug.begin(); it != debug.end(); ++it) {
		if (*it != prev)	std::cout << std::endl;
		std::cout << *it << "\t";
		prev = *it;
	}

	std::cout << std::endl;
}