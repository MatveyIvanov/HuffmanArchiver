#pragma once
#include "Stack.h"

enum Color {
	Black,
	Red
};

template<class K, class V>
class Map
{
public:
	class Node {
	public:
		Node(K k, V val, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr, bool col = Red) : key(k), value(val), left(l), right(r), parent(p), color(col) {}

		void set_key(K);
		void set_value(V);
		void set_left(Node*);
		void set_right(Node*);
		void set_parent(Node*);
		void set_color(bool);

		K get_key();
		V get_value();
		Node* get_left();
		Node* get_right();
		Node* get_parent();
		bool get_color();
	private:
		K key;
		V value;
		Node* left;
		Node* right;
		Node* parent;
		bool color;
	};
	Map(Node* r = nullptr);

	void set_root(Node*);
	Node* get_root();
	Node* get_nil();

	void left_rotate(Node*);
	void right_rotate(Node*);
	void insert_balance(Node*);
	void insert(K, V, Node* r = nullptr);
	V find(K);
	int size();
	bool isEmpty();
	V operator[](K);
	void increment(K);

	class Iterator {
	public:
		Iterator(Map*);
		bool has_next();
		Node* next();
	private:
		Stack<Node*> s;
		Node* nil;
	};
private:
	Node* root;
	Node* nil;
	int keys_count; // Map size
};