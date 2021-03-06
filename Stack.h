#pragma once
#include "BinaryTree.h"

template<class T>
class Stack
{
public:
	class Node {
	public:
		Node(T n) {
			this->data = n;
			this->next = nullptr;
		}
		void set_next(Node*);
		Node* get_next();
		void set_data(T);
		T get_data();
	private:
		T data;
		Node* next;
	};
	Stack() : top_node(nullptr) {}

	void push(T);
	T top();
	T pop();
	bool isEmpty();

private:
	Node* top_node;
};
























/*
class Stack
{
public:
	class Node {
	public:
		Node(BinaryTree::Node* n) {
			this->data = n;
			this->next = nullptr;
		}
		void set_next(Node*);
		Node* get_next();
		void set_data(BinaryTree::Node*);
		BinaryTree::Node* get_data();
	private:
		BinaryTree::Node* data;
		Node* next;
	};
	Stack() : top_node(nullptr) {}

	void push(BinaryTree::Node*);
	BinaryTree::Node* top();
	BinaryTree::Node* pop();
	bool isEmpty();

private:
	Node* top_node;
};
*/

