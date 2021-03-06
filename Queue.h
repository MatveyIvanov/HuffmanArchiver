#pragma once
#include "BinaryTree.h"

class BinaryTree;

class Queue
{
public:
	class Node {
	public:
		Node(BinaryTree::Node* d = nullptr) : data(d), next(nullptr) {}

		void set_next(Node*);
		Node* get_next();
		void set_data(BinaryTree::Node*);
		BinaryTree::Node* get_data();
	private:
		BinaryTree::Node* data;
		Node* next;
	};
	Queue() : first(nullptr), last(nullptr) {}

	void enqueue(BinaryTree::Node*);
	BinaryTree::Node* dequeue();
	bool isEmpty();
private:
	Node* first;
	Node* last;
};

