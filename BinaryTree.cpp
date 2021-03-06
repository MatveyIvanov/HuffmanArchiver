#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include "BinaryTree.h"

using namespace std;

void BinaryTree::Node::set_freq(int freq) { this->frequency = freq; }

void BinaryTree::Node::set_letter(char let) { this->letter = let; }

void BinaryTree::Node::set_left(Node* left) { this->leftChild = left; }

void BinaryTree::Node::set_right(Node* right) { this->rightChild = right; }

void BinaryTree::Node::set_code(string c) { this->code = c; }

int BinaryTree::Node::get_freq() { return this->frequency; }

char BinaryTree::Node::get_letter() { return this->letter; }

BinaryTree::Node* BinaryTree::Node::get_left() { return this->leftChild; }

BinaryTree::Node* BinaryTree::Node::get_right() { return this->rightChild; }

string BinaryTree::Node::get_code() { return this->code; }

BinaryTree::Node* BinaryTree::get_root() { return this->root; }