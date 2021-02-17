#pragma once
#include <string>

using namespace std;

class BinaryTree
{
public:
	class Node
	{
	public:
		Node(int freq = 0, char l = '\0', Node* left = nullptr, Node* right = nullptr) {
			this->frequency = freq;
			this->letter = l;
			this->leftChild = left;
			this->rightChild = right;
			this->code = "";
		}
		void set_freq(int);
		void set_letter(char);
		void set_left(Node*);
		void set_right(Node*);
		void set_code(string);

		int get_freq();
		char get_letter();
		Node* get_left();
		Node* get_right();
		string get_code();
	private:
		char letter;
		int frequency;
		Node* leftChild;
		Node* rightChild;
		string code;
	};

	BinaryTree(Node* r) : root(r) {};

	Node* get_root();

	void bft();
	void dft();
private:
	Node* root;
};

