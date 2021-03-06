#include "Map.h"
#include <string>
#include "BinaryTree.h"

using namespace std;


/* -------------------- Map<char, string> ---------------------- */

template<>
void Map<char, string>::Node::set_key(char k) { this->key = k; }

template<>
void Map<char, string>::Node::set_value(string val) { this->value = val; }

template<>
void Map<char, string>::Node::set_left(Node* l) { this->left = l; }

template<>
void Map<char, string>::Node::set_right(Node* r) { this->right = r; }

template<>
void Map<char, string>::Node::set_parent(Node* p) { this->parent = p; }

template<>
void Map<char, string>::Node::set_color(bool col) { this->color = col; }

template<>
char Map<char, string>::Node::get_key() { return this->key; }

template<>
string Map<char, string>::Node::get_value() { return this->value; }

template<>
typename Map<char, string>::Node* Map<char, string>::Node::get_left() { return this->left; }

template<>
typename Map<char, string>::Node* Map<char, string>::Node::get_right() { return this->right; }

template<>
typename Map<char, string>::Node* Map<char, string>::Node::get_parent() { return this->parent; }

template<>
bool Map<char, string>::Node::get_color() { return this->color; }


template<>
Map<char, string>::Map<char, string>(Node* r) {
	this->root = r;
	this->keys_count = 0;
	this->nil = new Node('\0', "\0", nullptr, nullptr, root, false);
	if (this->root != nullptr) {
		this->root->set_left(this->nil);
		this->root->set_right(this->nil);
	}
}

template<>
void Map<char, string>::set_root(Node* r) { this->root = r; }

template<>
typename Map<char, string>::Node* Map<char, string>::get_root() { return this->root; }

template<>
typename Map<char, string>::Node* Map<char, string>::get_nil() { return this->nil; }

template<>
void Map<char, string>::left_rotate(Node* node) {
	Node* child = nullptr;
	if (node->get_right() != nullptr)
		child = node->get_right();
	if (node == this->root) {
		this->root = child;
		Node* temp = child->get_left();
		child->set_left(node);
		child->set_parent(nullptr);
		node->set_right(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
	else {
		child->set_parent(node->get_parent());
		if (node->get_parent()->get_right() == node)
			node->get_parent()->set_right(child);
		else
			node->get_parent()->set_left(child);
		Node* temp = child->get_left();
		child->set_left(node);
		node->set_right(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
}

template<>
void Map<char, string>::right_rotate(Node* node) {
	Node* child = nullptr;
	if (node->get_left() != nullptr)
		child = node->get_left();
	if (node == this->root) {
		this->root = child;
		Node* temp = child->get_right();
		child->set_right(node);
		child->set_parent(nullptr);
		node->set_left(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
	else {
		child->set_parent(node->get_parent());
		if (node->get_parent()->get_right() == node)
			node->get_parent()->set_right(child);
		else
			node->get_parent()->set_left(child);
		Node* temp = child->get_right();
		child->set_right(node);
		node->set_left(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
}

template<>
void Map<char, string>::insert_balance(Node* node) {
	Node* balanceNode = node;
	while (balanceNode->get_parent() != nullptr && balanceNode->get_parent()->get_color() == Red) {
		Node* gp = balanceNode->get_parent()->get_parent();
		Node* p = balanceNode->get_parent();
		if (gp != nullptr && gp->get_left() == p) {
			if (gp->get_right()->get_color() == Red) {
				gp->get_left()->set_color(Black);
				gp->get_right()->set_color(Black);
				gp->set_color(Red);
				balanceNode = gp;
			}
			else if (p->get_right() == balanceNode) {
				balanceNode = p;
				this->left_rotate(balanceNode);
			}
			else {
				p->set_color(Black);
				gp->set_color(Red);
				this->right_rotate(gp);
			}
		}
		else if (gp != nullptr) {
			if (gp->get_left()->get_color() == Red) {
				gp->get_left()->set_color(Black);
				gp->get_right()->set_color(Black);
				gp->set_color(Red);
				balanceNode = gp;
			}
			else if (p->get_left() == balanceNode) {
				balanceNode = p;
				this->right_rotate(balanceNode);
			}
			else {
				p->set_color(Black);
				gp->set_color(Red);
				this->left_rotate(gp);
			}
		}
		else {
			break;
		}
	}
	this->root->set_color(Black);
}

template<>
void Map<char, string>::insert(char k, string val, Node* r) {
	if (this->isEmpty())
		this->root = new Node(k, val, this->nil, this->nil, nullptr, false);
	else {
		if (r == nullptr)
			r = this->root;
		if (r->get_key() == k)
			throw exception("Pair already exists");
		if (r->get_key() > k) {
			if (r->get_left() == this->nil) {
				r->set_left(new Node(k, val, this->nil, this->nil, r));
				this->keys_count++;
				if (r != this->root)
					this->insert_balance(r->get_left());
			}
			else
				this->insert(k, val, r->get_left());
		}
		else {
			if (r->get_right() == this->nil) {
				r->set_right(new Node(k, val, this->nil, this->nil, r));
				this->keys_count++;
				if (r != this->root)
					this->insert_balance(r->get_right());
			}
			else
				this->insert(k, val, r->get_right());
		}
	}
}

template<>
string Map<char, string>::find(char k) {
	if (this->isEmpty())
		throw exception("Map is empty");
	Node* cur = this->root;
	while (cur != this->nil && cur->get_key() != k) {
		if (cur->get_key() > k)
			cur = cur->get_left();
		else
			cur = cur->get_right();
	}
	if (cur == this->nil)
		return "\0";
	return cur->get_value();
}

template<>
int Map<char, string>::size() { return this->keys_count; }

template<>
bool Map<char, string>::isEmpty() {
	if (this->root == nullptr)
		return true;
	return false;
}

template<>
string Map<char, string>::operator[](char key) {
	string value = this->find(key);
	if (value == "\0")
		return "";
	return value;
}

template<>
Map<char, string>::Iterator::Iterator(Map<char, string>* map) {
	this->s.push(map->get_root());
	this->nil = map->get_nil();
}

template<>
bool Map<char, string>::Iterator::has_next() { return !this->s.isEmpty(); }

template<>
Map<char, string>::Node* Map<char, string>::Iterator::next() {
	if (this->has_next()) {
		Node* temp = this->s.pop();
		if (temp->get_right() != nullptr && temp->get_right() != this->nil)
			this->s.push(temp->get_right());
		if (temp->get_left() != nullptr && temp->get_left() != this->nil)
			this->s.push(temp->get_left());
		return temp;
	}
	else
		throw exception("Iteration stopped");
}



/* -------------------- Map<char,int> ---------------------- */

template<>
void Map<char, int>::Node::set_key(char k) { this->key = k; }

template<>
void Map<char, int>::Node::set_value(int val) { this->value = val; }

template<>
void Map<char, int>::Node::set_left(Node* l) { this->left = l; }

template<>
void Map<char, int>::Node::set_right(Node* r) { this->right = r; }

template<>
void Map<char, int>::Node::set_parent(Node* p) { this->parent = p; }

template<>
void Map<char, int>::Node::set_color(bool col) { this->color = col; }

template<>
char Map<char, int>::Node::get_key() { return this->key; }

template<>
int Map<char, int>::Node::get_value() { return this->value; }

template<>
typename Map<char, int>::Node* Map<char, int>::Node::get_left() { return this->left; }

template<>
typename Map<char, int>::Node* Map<char, int>::Node::get_right() { return this->right; }

template<>
typename Map<char, int>::Node* Map<char, int>::Node::get_parent() { return this->parent; }

template<>
bool Map<char, int>::Node::get_color() { return this->color; }


template<>
Map<char, int>::Map<char, int>(Node* r) {
	this->root = r;
	this->keys_count = 0;
	this->nil = new Node('\0', NULL, nullptr, nullptr, root, false);
	if (this->root != nullptr) {
		this->root->set_left(this->nil);
		this->root->set_right(this->nil);
	}
}

template<>
void Map<char, int>::set_root(Node* r) { this->root = r; }

template<>
typename Map<char, int>::Node* Map<char, int>::get_root() { return this->root; }

template<>
typename Map<char, int>::Node* Map<char, int>::get_nil() { return this->nil; }

template<>
void Map<char, int>::left_rotate(Node* node) {
	Node* child = nullptr;
	if (node->get_right() != nullptr)
		child = node->get_right();
	if (node == this->root) {
		this->root = child;
		Node* temp = child->get_left();
		child->set_left(node);
		child->set_parent(nullptr);
		node->set_right(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
	else {
		child->set_parent(node->get_parent());
		if (node->get_parent()->get_right() == node)
			node->get_parent()->set_right(child);
		else
			node->get_parent()->set_left(child);
		Node* temp = child->get_left();
		child->set_left(node);
		node->set_right(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
}

template<>
void Map<char, int>::right_rotate(Node* node) {
	Node* child = nullptr;
	if (node->get_left() != nullptr)
		child = node->get_left();
	if (node == this->root) {
		this->root = child;
		Node* temp = child->get_right();
		child->set_right(node);
		child->set_parent(nullptr);
		node->set_left(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
	else {
		child->set_parent(node->get_parent());
		if (node->get_parent()->get_right() == node)
			node->get_parent()->set_right(child);
		else
			node->get_parent()->set_left(child);
		Node* temp = child->get_right();
		child->set_right(node);
		node->set_left(temp);
		temp->set_parent(node);
		node->set_parent(child);
	}
}

template<>
void Map<char, int>::insert_balance(Node* node) {
	Node* balanceNode = node;
	while (balanceNode->get_parent() != nullptr && balanceNode->get_parent()->get_color() == Red) {
		Node* gp = balanceNode->get_parent()->get_parent();
		Node* p = balanceNode->get_parent();
		if (gp != nullptr && gp->get_left() == p) {
			if (gp->get_right()->get_color() == Red) {
				gp->get_left()->set_color(Black);
				gp->get_right()->set_color(Black);
				gp->set_color(Red);
				balanceNode = gp;
			}
			else if (p->get_right() == balanceNode) {
				balanceNode = p;
				this->left_rotate(balanceNode);
			}
			else {
				p->set_color(Black);
				gp->set_color(Red);
				this->right_rotate(gp);
			}
		}
		else if (gp != nullptr) {
			if (gp->get_left()->get_color() == Red) {
				gp->get_left()->set_color(Black);
				gp->get_right()->set_color(Black);
				gp->set_color(Red);
				balanceNode = gp;
			}
			else if (p->get_left() == balanceNode) {
				balanceNode = p;
				this->right_rotate(balanceNode);
			}
			else {
				p->set_color(Black);
				gp->set_color(Red);
				this->left_rotate(gp);
			}
		}
		else {
			break;
		}
	}
	this->root->set_color(Black);
}

template<>
void Map<char, int>::insert(char k, int val, Node* r) {
	if (this->isEmpty())
		this->root = new Node(k, val, this->nil, this->nil, nullptr, false);
	else {
		if (r == nullptr)
			r = this->root;
		if (r->get_key() == k)
			throw exception("Pair already exists");
		if (r->get_key() > k) {
			if (r->get_left() == this->nil) {
				r->set_left(new Node(k, val, this->nil, this->nil, r));
				this->keys_count++;
				if (r != this->root)
					this->insert_balance(r->get_left());
			}
			else
				this->insert(k, val, r->get_left());
		}
		else {
			if (r->get_right() == this->nil) {
				r->set_right(new Node(k, val, this->nil, this->nil, r));
				this->keys_count++;
				if (r != this->root)
					this->insert_balance(r->get_right());
			}
			else
				this->insert(k, val, r->get_right());
		}
	}
}

template<>
int Map<char, int>::find(char k) {
	if (this->isEmpty())
		return NULL;
	Node* cur = this->root;
	while (cur != this->nil && cur->get_key() != k) {
		if (cur->get_key() > k)
			cur = cur->get_left();
		else
			cur = cur->get_right();
	}
	if (cur == this->nil)
		return NULL;
	return cur->get_value();
}

template<>
int Map<char, int>::size() { return this->keys_count; }

template<>
bool Map<char, int>::isEmpty() {
	if (this->root == nullptr)
		return true;
	return false;
}

template<>
int Map<char, int>::operator[](char key) {
	int value = this->find(key);
	if (value == NULL)
		throw exception("Key is not in map!");
	return value;
}

template<>
Map<char, int>::Iterator::Iterator(Map<char, int>* map) {
	this->s.push(map->get_root());
	this->nil = map->get_nil();
}

template<>
bool Map<char, int>::Iterator::has_next() { return !this->s.isEmpty(); }

template<>
Map<char, int>::Node* Map<char, int>::Iterator::next() {
	if (this->has_next()) {
		Node* temp = this->s.pop();
		if (temp->get_right() != nullptr && temp->get_right() != this->nil)
			this->s.push(temp->get_right());
		if (temp->get_left() != nullptr && temp->get_left() != this->nil)
			this->s.push(temp->get_left());
		return temp;
	}
	else
		throw exception("Iteration stopped");
}

template<>
void Map<char, int>::increment(char key) {
	if (this->isEmpty())
		return;
	Node* cur = this->root;
	while (cur != this->nil && cur->get_key() != key) {
		if (cur->get_key() > key)
			cur = cur->get_left();
		else
			cur = cur->get_right();
	}
	if (cur == this->nil)
		return;
	cur->set_value(cur->get_value() + 1);
}


template class Map<char, string>;
template class Map<char, int>;
