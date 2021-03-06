#include "Queue.h"

void Queue::Node::set_next(Node* node) { this->next = node; }

Queue::Node* Queue::Node::get_next() { return this->next; }

void Queue::Node::set_data(BinaryTree::Node* node) { this->data = node; }

BinaryTree::Node* Queue::Node::get_data() { return this->data; }

void Queue::enqueue(BinaryTree::Node* data) {
	if (this->isEmpty()) {
		this->first = new Node(data);
		this->last = this->first;
	}
	else {
		this->last->set_next(new Node(data));
		this->last = this->last->get_next();
	}
}

BinaryTree::Node* Queue::dequeue() {
	if (this->isEmpty())
		throw exception("Queue is emtpy");
	else {
		BinaryTree::Node* temp = this->first->get_data();
		this->first = this->first->get_next();
		return temp;
	}
}

bool Queue::isEmpty() { return this->first == nullptr; }