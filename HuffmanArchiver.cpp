#include <iostream>
#include <queue>
#include <map>
#include <stack>
#include <fstream>
#include <string>
#include <boost/dynamic_bitset.hpp>
#include "BinaryTree.h"
#include <stdio.h>

using namespace std;

string read_file(string filename); // Read text from file to string
map<char, int> count_frequency(string text); // Count frequency of each character in text
BinaryTree* huffman_tree(map<char, int> freq); // Create Huffman tree using priority queue
map<char, string> huffman_table(BinaryTree*); // Create Huffman table based on Huffman tree
void compress_n_write(map<char, string>, string, string, BinaryTree*); // Compress text and write it to new file
string read_n_decompress(string); // Read compressed text from file and decompress it to string

void help(); // Write instructions to console
bool correct_file_extension(string, bool); // Check if file has correct extension
bool correct_outfile_extension(string, bool); // Check if output file has correct extension


void main(int argc, char* argv[])
{
	string file_name, newfile_name; // newfile_name - outfile name
	bool compress = true; // If false - program decompresses the file

	if (argc == 1) { // Case when no arguments passed after program call
		help(); 
	}
	else {
		if (argv[1] == string("-h") || argv[1] == string("--help")) { // Help flags
			help();
		}
		else { // Else name of file has passed
			file_name = argv[1];
		}
		for (int i = 2; i < argc; i++) {
			if (argv[i] == string("-d") || argv[i] == string("--decompress")) // Compress / decompress flags
				compress = false;
			else if (argv[i] == string("-of") || argv[i] == string("--outfile")) { // Outfile name flags
				if (i + 1 >= argc) { // If outfile name hasn't been passed
					cout << "Wrong command. Write <FILENAME> after " << argv[i] << " flag";
					return;
				}
				else { // Else save outfile name & go to next parameter
					newfile_name = argv[i + 1];
					i++;
				}
			}
		}
	}

	string file_text; // Variable to store text from file
	if (correct_file_extension(file_name, compress)) {
		if (compress) {
			try {
				file_text = read_file(file_name); // Read text from file
			}
			catch (const std::exception& e) {
				cout << e.what();
				return;
			}
			if (file_text.empty()) // If file is empty
				cout << "File is empty";
			else {
				BinaryTree* tree = huffman_tree(count_frequency(file_text)); // Create huffman tree
				map<char, string> table = huffman_table(tree); // Create huffman table
				if (newfile_name.empty()) { // If output file name hasn't been set
					compress_n_write(table, file_text, file_name, tree); // Compress to same file
				}
				else {
					if (correct_outfile_extension(newfile_name, compress)) { // If output file has correct extension
						file_name = newfile_name;
						compress_n_write(table, file_text, file_name, tree); // Compress to output file
					}
					else { // Incorrect output file extension
						cout << "Incorrect out file name or extension. Use -h for more information\n";
					}
				}
			}
		}
		else { // Decompress
			if (newfile_name.empty()) { // If output file name hasn't been set
				string decompressed_text = read_n_decompress(file_name); // Decompress file
				ofstream fout(file_name, ofstream::trunc || ofstream::binary); // Write decompressed text to same file
				fout << decompressed_text;
			}
			else {
				if (correct_outfile_extension(newfile_name, compress)) { // If output file has correct extension
					string decompressed_text = read_n_decompress(file_name); // Decompress file
					ofstream fout(newfile_name, ofstream::trunc || ofstream::binary); // Write decompressed text to output file
					fout << decompressed_text;
				}
				else { // Incorrect output file extension
					cout << "Incorrect out file name or extension. Use -h for more information\n";
				}
			}
		}
	}
	else { // Incorrect file extension
		cout << "Incorrect file name or extension. Use -h for more indormation\n";
	}
}


void help() {
	cout << "\n\n| First parameter FILENAME is required! (.txt files for compression, .txt .bin files for decompression!)\n|\n";
	cout << "| Other flags available after FILENAME parameter:\n|\n|";
	cout << "\n| -d --decompress : Decompress the file (Program compresses the file by DEFAULT\n|";
	cout << "\n| -of --outfile <FILENAME> : Set (de)compressed file name (By DEFAULT compresses to source file) Out file name can't be equal to source file name!\n|";

	cout << "\n|\n| -h --help : Show instructions\n";
}

bool correct_file_extension(string filename, bool compress) {
	string extension("");
	for (size_t i = filename.size() - 3; i < filename.size(); i++)
		extension += filename[i];
	if (compress && extension == "txt") // Compress from .txt
		return true;
	if (!compress && (extension == "txt" || extension == "bin")) // Decompress from .bin or .txt
		return true;
	return false;
}

bool correct_outfile_extension(string filename, bool compress) {
	string extension("");
	for (size_t i = filename.size() - 3; i < filename.size(); i++)
		extension += filename[i];
	if (compress && (extension == "txt" || extension == "bin")) // Compress to .bin or .txt
		return true;
	if (!compress && extension == "txt") // Decompress to txt 
		return true;
	return false;
}


string read_file(string filename) {
	ifstream fin(filename);
	if (!fin.is_open()) {
		string emessage = "Error opening file " + filename + ". Make sure this file exists.";
		throw exception(emessage.c_str());
	}
	string text((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
	fin.close();
	return text;
}

map<char, int> count_frequency(string text) {
	map<char, int> frequencies;

	for (size_t i = 0; i < text.size(); i++) { // Count frequency of every character in text
		if (frequencies.find(text[i]) == frequencies.end())
			frequencies.insert(make_pair(text[i], 1));
		else
			frequencies[text[i]]++;
	}
	return frequencies;
}

BinaryTree* huffman_tree(map<char, int> freq) {
	auto comp = [](BinaryTree::Node* a, BinaryTree::Node* b) {return a->get_freq() > b->get_freq(); }; // Lambda for comparison two nodes (based on node's frequency)
	priority_queue <BinaryTree::Node*, vector<BinaryTree::Node*>, decltype(comp)> q(comp);
	for (auto const& x : freq) {
		q.push(new BinaryTree::Node(x.second, x.first));
	}

	while (true) {
		BinaryTree::Node* node1 = q.top();
		q.pop();
		BinaryTree::Node* node2 = q.top();
		q.pop();
		if (q.empty()) {
			BinaryTree::Node* root = new BinaryTree::Node(node1->get_freq() + node2->get_freq(), '\0', node1, node2);
			BinaryTree* tree = new BinaryTree(root);
			return tree;
		}
		else { // Create tree
			q.push(new BinaryTree::Node(node1->get_freq() + node2->get_freq(), '\0', node1, node2));
		}
	}

	return nullptr; // If smth went wrong
}

map<char, string> huffman_table(BinaryTree* tree) { // Create huffman table
	map<char, string> table;
	stack<BinaryTree::Node*> s;
	tree->get_root()->set_code("");
	s.push(tree->get_root());
	while (!s.empty()) {
		BinaryTree::Node* cur = s.top();
		s.pop();
		if (!cur->get_code().empty() && cur->get_letter() != '\0')
			table.insert(make_pair(cur->get_letter(), cur->get_code()));
		if (cur->get_left() != nullptr) {
			if (cur->get_code().empty())
				cur->get_left()->set_code("0");
			else
				cur->get_left()->set_code(cur->get_code() += "0");
			s.push(cur->get_left());
		}
		if (cur->get_right() != nullptr) {
			if (cur->get_code().empty())
				cur->get_right()->set_code("1");
			else
				cur->get_right()->set_code(cur->get_code() += "1");
			s.push(cur->get_right());
		}
	}
	return table;
}

void compress_n_write(map<char, string> table, string text, string filename, BinaryTree* tree) {
	string uncompressed; // Text to compress
	for (int i = 0; i < text.size(); i++)
		uncompressed += table[text[i]];

	ofstream fout(filename, ofstream::binary);
	boost::dynamic_bitset<> compressed(uncompressed.size()); // For bits
	for (int i = 0; i < uncompressed.size(); i++) { // Write bits to bitset
		if (uncompressed[i] == '1')
			compressed[uncompressed.size() - i - 1].flip();
	}

	unsigned char bitbuffer = 0;
	while (compressed.size() > 0) { // Write bitset to file
		size_t i;
		for (i = 0; i < 8 && i < compressed.size(); i++) {
			if ((compressed[compressed.size() - i - 1] & 1) == 1)
				bitbuffer |= 1 << i;
		}
		if (i < 7) {
			fout << i;
		}
		fout.write(reinterpret_cast<const char*>(&bitbuffer), 1);
		bitbuffer = 0;
		if (compressed.size() >= 8) {
			compressed.resize(compressed.size() - 8);
		}
		else
			break;
	}

	fout.close(); // Close file


	/* Create tree file for decompress */
	filename.pop_back();
	filename.pop_back();
	filename.pop_back();
	string tree_filename = "tree" + filename + "bin";
	ofstream treeout(tree_filename);
	int tree_lvl = 1, cur_node = 0, let_added = 0;
	BinaryTree::Node* cur = tree->get_root();
	queue<BinaryTree::Node*> q;
	q.push(cur);
	while (!q.empty()) {
		cur = q.front();
		if (cur->get_left() != nullptr) {
			q.push(cur->get_left());
			q.push(cur->get_right());
			if (cur_node == pow(2, tree_lvl - 1)) {
				tree_lvl++;
				cur_node = let_added * 2;
				let_added *= 2;
				treeout << '\n';
			}
			treeout << "EM"; // Empty node
			cur_node++;
		}
		else {
			if (cur_node == pow(2, tree_lvl - 1)) {
				tree_lvl++;
				cur_node = let_added * 2;
				let_added *= 2;
				treeout << '\n';
			}
			if (cur->get_letter() == ' ')
				treeout << "SP"; // Node with space
			else if (cur->get_letter() == '\n')
				treeout << "NL"; // Node with new line
			else
				treeout << cur->get_letter(); // Node with other character
			cur_node++;
			let_added++;
		}
		if (cur_node != pow(2, tree_lvl - 1))
			treeout << ' ';

		q.pop();
	}
	treeout.close();
}

string read_n_decompress(string filename) {
	ifstream fin(filename, ifstream::binary);
	boost::dynamic_bitset<> compressed;


	/* Write bits from file to bitset */
	char bitbuffer;
	fin.seekg(-2, ios::end);
	fin.get(bitbuffer);
	int last_bits = bitbuffer - '0';
	fin.get(bitbuffer);
	for (int i = last_bits - 1; i >= 0; i--)
		compressed.push_back((bitbuffer >> i) & 1);

	fin.seekg(-3, ios::end);
	for (char bitbuffer; fin.get(bitbuffer);) {
		for (int i = 7; i >= 0; i--)
			compressed.push_back((bitbuffer >> i) & 1);
		fin.seekg(-2, ios::cur);
	}

	fin.close();


	/* Create tree using tree file */
	filename.pop_back();
	filename.pop_back();
	filename.pop_back();
	string tree_filename = "tree" + filename + "bin";
	BinaryTree* tree = new BinaryTree(new BinaryTree::Node(0, '\0', nullptr, nullptr));
	BinaryTree::Node* cur = tree->get_root();
	ifstream treein(tree_filename);
	queue<BinaryTree::Node*> q;
	q.push(cur);
	string cur_line;
	getline(treein, cur_line);
	while (!q.empty()) {
		if (!treein.eof()) {
			getline(treein, cur_line);
			int line_index = 0;
			cur = q.front();
			q.pop();
			while (line_index < cur_line.size()) {
				if (cur_line[line_index] == 'E' && line_index + 1 < cur_line.size() && cur_line[line_index + 1] == 'M') {
					if (cur->get_left() == nullptr) {
						cur->set_left(new BinaryTree::Node(0, '\0', nullptr, nullptr));
						line_index += 3;
						q.push(cur->get_left());
					}
					else if (cur->get_right() == nullptr) {
						cur->set_right(new BinaryTree::Node(0, '\0', nullptr, nullptr));
						line_index += 3;
						q.push(cur->get_right());
					}
					else if (!q.empty()) {
						cur = q.front();
						q.pop();
					}
				}
				else if (cur_line[line_index] == 'S' && line_index + 1 < cur_line.size() && cur_line[line_index + 1] == 'P') {
					if (cur->get_left() == nullptr) {
						cur->set_left(new BinaryTree::Node(0, ' ', nullptr, nullptr));
						line_index += 3;
					}
					else if (cur->get_right() == nullptr) {
						cur->set_right(new BinaryTree::Node(0, ' ', nullptr, nullptr));
						line_index += 3;
					}
					else if (!q.empty()) {
						cur = q.front();
						q.pop();
					}
				}
				else if (cur_line[line_index] == 'N' && line_index + 1 < cur_line.size() && cur_line[line_index + 1] == 'L') {
					if (cur->get_left() == nullptr) {
						cur->set_left(new BinaryTree::Node(0, '\n', nullptr, nullptr));
						line_index += 3;
					}
					else if (cur->get_right() == nullptr) {
						cur->set_right(new BinaryTree::Node(0, '\n', nullptr, nullptr));
						line_index += 3;
					}
					else if (!q.empty()) {
						cur = q.front();
						q.pop();
					}
				}
				else {
					if (cur->get_left() == nullptr) {
						cur->set_left(new BinaryTree::Node(0, cur_line[line_index], nullptr, nullptr));
						line_index += 2;
					}
					else if (cur->get_right() == nullptr) {
						cur->set_right(new BinaryTree::Node(0, cur_line[line_index], nullptr, nullptr));
						line_index += 2;
					}
					else if (!q.empty()) {
						cur = q.front();
						q.pop();
					}
				}
			}
		}
		else
			break;
	}


	/* Decompress text using Huffman tree */
	string uncompressed("");
	cur = tree->get_root();
	for (size_t i = compressed.size(); i >= 1; i--) {
		if (compressed[i - 1] == 0)
			cur = cur->get_left();
		else
			cur = cur->get_right();
		if (cur->get_letter() != '\0') {
			uncompressed += cur->get_letter();
			cur = tree->get_root();
		}
	}

	treein.close();


	/* Delete tree file */
	if (remove(tree_filename.c_str()) != 0)
		cout << "Error deleting tree file";

	return uncompressed;
}