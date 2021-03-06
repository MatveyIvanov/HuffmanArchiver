#include "Stack.h"
#include "Map.h"


/* --------------- Stack<BinaryTree::Node*> ------------------ */

template<>
void Stack<BinaryTree::Node*>::Node::set_next(Node* n) { this->next = n; }

template<>
Stack<BinaryTree::Node*>::Node* Stack<BinaryTree::Node*>::Node::get_next() { return this->next; }

template<>
void Stack<BinaryTree::Node*>::Node::set_data(BinaryTree::Node* n) { this->data = n; }

template<>
BinaryTree::Node* Stack<BinaryTree::Node*>::Node::get_data() { return this->data; }

template<>
void Stack<BinaryTree::Node*>::push(BinaryTree::Node* n) {
	Node* new_node = new Node(n);
	if (this->isEmpty())
		this->top_node = new_node;
	else {
		Node* temp = this->top_node;
		this->top_node = new_node;
		this->top_node->set_next(temp);
	}
}

template<>
BinaryTree::Node* Stack<BinaryTree::Node*>::top() { return this->top_node->get_data(); }

template<>
BinaryTree::Node* Stack<BinaryTree::Node*>::pop() {
	if (this->isEmpty())
		throw exception("Stack is empty");
	else {
		BinaryTree::Node* temp = this->top_node->get_data();
		this->top_node = this->top_node->get_next();
		return temp;
	}
}

template<>
bool Stack<BinaryTree::Node*>::isEmpty() { return this->top_node == nullptr; }


/* --------------- Stack<Map<char, int> ------------------ */


template<>
void Stack<Map<char, int>::Node*>::Node::set_next(Node* n) { this->next = n; }

template<>
Stack<Map<char, int>::Node*>::Node* Stack<Map<char, int>::Node*>::Node::get_next() { return this->next; }

template<>
void Stack<Map<char, int>::Node*>::Node::set_data(Map<char, int>::Node* n) { this->data = n; }

template<>
Map<char, int>::Node* Stack<Map<char, int>::Node*>::Node::get_data() { return this->data; }

template<>
void Stack<Map<char, int>::Node*>::push(Map<char, int>::Node* n) {
	Node* new_node = new Node(n);
	if (this->isEmpty())
		this->top_node = new_node;
	else {
		Node* temp = this->top_node;
		this->top_node = new_node;
		this->top_node->set_next(temp);
	}
}

template<>
Map<char, int>::Node* Stack<Map<char, int>::Node*>::top() { return this->top_node->get_data(); }

template<>
Map<char, int>::Node* Stack<Map<char, int>::Node*>::pop() {
	if (this->isEmpty())
		throw exception("Stack is empty");
	else {
		Map<char, int>::Node* temp = this->top_node->get_data();
		this->top_node = this->top_node->get_next();
		return temp;
	}
}

template<>
bool Stack<Map<char, int>::Node*>::isEmpty() { return this->top_node == nullptr; }


/* --------------- Stack<Map<char, string> ------------------ */


template<>
void Stack<Map<char, string>::Node*>::Node::set_next(Node* n) { this->next = n; }

template<>
Stack<Map<char, string>::Node*>::Node* Stack<Map<char, string>::Node*>::Node::get_next() { return this->next; }

template<>
void Stack<Map<char, string>::Node*>::Node::set_data(Map<char, string>::Node* n) { this->data = n; }

template<>
Map<char, string>::Node* Stack<Map<char, string>::Node*>::Node::get_data() { return this->data; }

template<>
void Stack<Map<char, string>::Node*>::push(Map<char, string>::Node* n) {
	Node* new_node = new Node(n);
	if (this->isEmpty())
		this->top_node = new_node;
	else {
		Node* temp = this->top_node;
		this->top_node = new_node;
		this->top_node->set_next(temp);
	}
}

template<>
Map<char, string>::Node* Stack<Map<char, string>::Node*>::top() { return this->top_node->get_data(); }

template<>
Map<char, string>::Node* Stack<Map<char, string>::Node*>::pop() {
	if (this->isEmpty())
		throw exception("Stack is empty");
	else {
		Map<char, string>::Node* temp = this->top_node->get_data();
		this->top_node = this->top_node->get_next();
		return temp;
	}
}

template<>
bool Stack<Map<char, string>::Node*>::isEmpty() { return this->top_node == nullptr; }

template class Stack<BinaryTree::Node*>;
template class Stack<Map<char, int>::Node*>;
template class Stack<Map<char, string>::Node*>;