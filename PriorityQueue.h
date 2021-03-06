#pragma once
#include "BinaryTree.h"

class PriorityQueue
{
public:
	PriorityQueue(int s) {
		this->cur_size = -1;
		this->heap = new BinaryTree::Node * [s];
	}

	bool isEmpty();
	int PARENT(int);
	int LEFT(int);
	int RIGHT(int);
	void heapify_down(int);
	void heapify_up(int);
	void push(BinaryTree::Node*);
	void pop();
	BinaryTree::Node* top();
private:
	BinaryTree::Node** heap;
	int cur_size;
};

