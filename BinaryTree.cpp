#include <queue>
#include <stack>
#include <iostream>
#include <string>
#include "BinaryTree.h"

using namespace std;

void BinaryTree::Node::set_freq(int freq) {
	this->frequency = freq;
}

void BinaryTree::Node::set_letter(char let) {
	this->letter = let;
}

void BinaryTree::Node::set_left(Node* left) {
	this->leftChild = left;
}

void BinaryTree::Node::set_right(Node* right) {
	this->rightChild = right;
}

void BinaryTree::Node::set_code(string c) {
	this->code = c;
}

int BinaryTree::Node::get_freq() {
	return this->frequency;
}

char BinaryTree::Node::get_letter() {
	return this->letter;
}

BinaryTree::Node* BinaryTree::Node::get_left() {
	return this->leftChild;
}

BinaryTree::Node* BinaryTree::Node::get_right() {
	return this->rightChild;
}

string BinaryTree::Node::get_code() {
	return this->code;
}

BinaryTree::Node* BinaryTree::get_root() {
	return this->root;
}

void BinaryTree::bft() {
	queue<Node*> q;
	q.push(this->root);
	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();
		if (cur->get_letter() == '\0')
			cout << "Empty: ";
		else if (cur->get_letter() == '\n')
			cout << "New line: ";
		else if (cur->get_letter() == ' ')
			cout << "Space: ";
		else
			cout << cur->get_letter() << ": ";
		if (cur->get_left() != nullptr) {
			if (cur->get_left()->get_letter() == '\0')
				cout << "Empty ";
			else if (cur->get_left()->get_letter() == '\n')
				cout << "New line ";
			else if (cur->get_left()->get_letter() == ' ')
				cout << "Space ";
			else
				cout << cur->get_left()->get_letter() << " ";
			q.push(cur->get_left());
		}
		if (cur->get_right() != nullptr) {
			if (cur->get_right()->get_letter() == '\0')
				cout << "Empty ";
			else if (cur->get_right()->get_letter() == '\n')
				cout << "New line ";
			else if (cur->get_right()->get_letter() == ' ')
				cout << "Space ";
			else
				cout << cur->get_right()->get_letter() << " ";
			q.push(cur->get_right());
		}
		cout << endl;
	}
}

void BinaryTree::dft() {
	stack<Node*> s;
	s.push(this->root);
	while (!s.empty()) {
		Node* cur = s.top();
		s.pop();
		if (cur->get_left() != nullptr)
			s.push(cur->get_left());
		if (cur->get_right() != nullptr)
			s.push(cur->get_right());
		if (cur->get_letter() == '\0')
			cout << "Empty" << endl;
		else if (cur->get_letter() == '\n')
			cout << "New line" << endl;
		else if (cur->get_letter() == ' ')
			cout << "Space" << endl;
		else
			cout << cur->get_letter() << endl;
	}
}