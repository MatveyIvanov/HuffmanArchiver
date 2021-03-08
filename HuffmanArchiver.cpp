#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "PriorityQueue.h"
#include "Queue.h"
#include "Map.h"
#include "Stack.h"
#include "BinaryTree.h"
#include <sys/stat.h>

using namespace std;

string read_file(string filename); // Read text from file to string
Map<char, int> count_frequency(string text); // Count frequency of each character in text
BinaryTree* huffman_tree(Map<char, int>); // Create Huffman tree using priority queue
Map<char, string> huffman_table(BinaryTree*); // Create Huffman table based on Huffman tree
void compress_n_write(Map<char, string>, string, string, BinaryTree*); // Compress text and write it to new file
string read_n_decompress(string); // Read compressed text from file and decompress it to string

void help(); // Write instructions to console
bool correct_file_extension(string, bool); // Check if file has correct extension
bool correct_outfile_extension(string, bool); // Check if output file has correct extension


void main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");

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
	int file1_size, file2_size;
	Map<char, int> freq;
	BinaryTree* tree;
	Map<char, string> table;
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
				freq = count_frequency(file_text); // Create frequency table
				tree = huffman_tree(freq); // Create huffman tree
				table = huffman_table(tree); // Create huffman table
				if (newfile_name.empty()) { // If output file name hasn't been set
					struct stat fi;
					stat(file_name.c_str(), &fi);
					file1_size = fi.st_size;
					cout << endl << "Размер файла до сжатия: " << file1_size << " Кбайт" << endl;
					compress_n_write(table, file_text, file_name, tree); // Compress to same file
					stat(file_name.c_str(), &fi);
					file2_size = fi.st_size;
					cout << "Размер файла после сжатия: " << file2_size << " Кбайт" << endl;

					// Frequency table output
					cout << endl << endl << "ТАБЛИЦА ЧАСТОТ:" << endl << endl;
					Map<char, int>::Iterator it1(&freq);
					while (it1.has_next()) {
						Map<char, int>::Node* cur = it1.next();
						cout << cur->get_key() << ": " << cur->get_value() << endl;
					}

					// Huffman table output
					cout << endl << endl << "ТАБЛИЦА КОДОВ:" << endl << endl;
					Map<char, string>::Iterator it2(&table);
					while (it2.has_next()) {
						Map<char, string>::Node* cur = it2.next();
						cout << cur->get_key() << ": " << cur->get_value() << endl;
					}

					// Сompression ratio output
					cout << endl << endl << "Коэффициент сжатия: " << (double)file1_size / (double)file2_size << endl;
				}
				else {
					if (correct_outfile_extension(newfile_name, compress)) { // If output file has correct extension
						struct stat fi;
						stat(file_name.c_str(), &fi);
						file1_size = fi.st_size;
						cout << endl << "Размер файла до сжатия: " << file1_size << " Кбайт" << endl;
						file_name = newfile_name;
						compress_n_write(table, file_text, file_name, tree); // Compress to output file
						stat(file_name.c_str(), &fi);
						file2_size = fi.st_size;
						cout << "Размер файла после сжатия: " << file2_size << " Кбайт" << endl;

						// Frequency table output
						cout << endl << endl << "ТАБЛИЦА ЧАСТОТ:" << endl << endl;
						Map<char, int>::Iterator it1(&freq);
						while (it1.has_next()) {
							Map<char, int>::Node* cur = it1.next();
							cout << cur->get_key() << ": " << cur->get_value() << endl;
						}

						// Huffman table output
						cout << endl << endl << "ТАБЛИЦА КОДОВ:" << endl << endl;
						Map<char, string>::Iterator it2(&table);
						while (it2.has_next()) {
							Map<char, string>::Node* cur = it2.next();
							cout << cur->get_key() << ": " << cur->get_value() << endl;
						}

						// Сompression ratio output
						cout << endl << endl << "Коэффициент сжатия: " << (double)file1_size / (double)file2_size << endl;
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
		string emessage = "Error opening file " + filename + ". Make sure this file exists";
		throw exception(emessage.c_str());
	}
	string text((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
	fin.close();
	return text;
}

Map<char, int> count_frequency(string text) {
	Map<char, int> frequencies;

	for (size_t i = 0; i < text.size(); i++) { // Count frequency of every character in text
		if (frequencies.find(text[i]) == NULL)
			frequencies.insert(text[i], 1);
		else
			frequencies.increment(text[i]);
	}
	return frequencies;
}

BinaryTree* huffman_tree(Map<char, int> freq) {
	PriorityQueue q(freq.size());
	Map<char, int>::Iterator it(&freq);
	while (it.has_next()) { // Add all symbols from frequency table
		Map<char, int>::Node* temp = it.next();
		q.push(new BinaryTree::Node(temp->get_value(), temp->get_key()));
	}

	while (true) { // Create huffman tree
		BinaryTree::Node* node1 = q.top();
		q.pop();
		BinaryTree::Node* node2 = q.top();
		q.pop();
		if (q.isEmpty()) { // Create tree
			BinaryTree::Node* root = new BinaryTree::Node(node1->get_freq() + node2->get_freq(), '\0', node1, node2);
			BinaryTree* tree = new BinaryTree(root);
			return tree;
		}
		else { // Create new node
			q.push(new BinaryTree::Node(node1->get_freq() + node2->get_freq(), '\0', node1, node2));
		}
	}

	return nullptr; // If smth went wrong
}

Map<char, string> huffman_table(BinaryTree* tree) { // Create huffman table
	Map<char, string> table;
	Stack<BinaryTree::Node*> s;
	tree->get_root()->set_code("");
	s.push(tree->get_root());
	while (!s.isEmpty()) {
		BinaryTree::Node* cur = s.top();
		s.pop();
		if (!cur->get_code().empty() && cur->get_letter() != '\0')
			table.insert(cur->get_letter(), cur->get_code());
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

void compress_n_write(Map<char, string> table, string text, string filename, BinaryTree* tree) {
	string uncompressed(""); // Text to compress
	for (int i = 0; i < text.size(); i++)
		uncompressed += table[text[i]];

	ofstream fout(filename, ofstream::binary);

	unsigned char bitbuffer = 0; // For storing 8 bits
	while (uncompressed.size() > 0) { // Write bits to file
		size_t i;
		for (i = 0; i <= 7 && i < uncompressed.size(); i++) {
			if (uncompressed[i] == '1')
				bitbuffer |= 1 << (7 - i);
		}
		if (i < 7) { // If last byte not fully filled
			fout << i; // Write number of bits to be read in last byte
		}
		fout.write(reinterpret_cast<const char*>(&bitbuffer), 1); // Write byte to the file
		bitbuffer = 0;
		if (uncompressed.size() >= 8) { // Delete first 8 elements from string
			for (i = 0; i < 8; i++)
				uncompressed.erase(uncompressed.begin());
		}
		else // If all bits are written
			break;
	}

	fout.close(); // Close file


	/* Create tree file for decompress */
	filename.pop_back(); // Delete txt extension from filename
	filename.pop_back();
	filename.pop_back();
	string tree_filename = "tree" + filename + "bin"; // Tree filename
	ofstream treeout(tree_filename);
	int tree_lvl = 1; // Current height level of the tree
	int	cur_node = 0; // Current node of the tree
	int let_added = 0; // Letters added to the file
	BinaryTree::Node* cur = tree->get_root();
	Queue q;
	q.enqueue(cur);
	while (!q.isEmpty()) { // BFT
		cur = q.dequeue();
		if (cur->get_left() != nullptr) { // If current node is not leaf
			q.enqueue(cur->get_left());
			q.enqueue(cur->get_right());
			if (cur_node == pow(2, tree_lvl - 1)) { // If current node is last on current level of the tree
				tree_lvl++; // Increase tree level
				cur_node = let_added * 2; // Multiply by 2 because new level has 2 times more nodes than previous
				let_added *= 2;
				treeout << '\n'; // Write new line to the file
			}
			treeout << "EM"; // Empty node, because all not leaf nodes are empty
			cur_node++;
		}
		else { // If current node is leaf
			if (cur_node == pow(2, tree_lvl - 1)) {	// If current node is last on current level of the tree
				tree_lvl++; // Increase tree level
				cur_node = let_added * 2; // Multiply by 2 because new level has 2 times more nodes than previous
				let_added *= 2;
				treeout << '\n'; // Write new line to the file
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
		if (cur_node != pow(2, tree_lvl - 1)) // Write space between nodes
			treeout << ' ';
	}
	treeout.close();
}

string read_n_decompress(string filename) {
	ifstream fin(filename, ifstream::binary);
	string compressed("");

	/* Write bits from file to string */
	char bitbuffer; // For storing 8 bits (1 byte)
	fin.seekg(-2, ios::end); // Go to 2nd byte from the end and read number of bits to be read in last byte
	fin.get(bitbuffer);
	int last_bits = bitbuffer - '0'; // Convert char to int
	fin.get(bitbuffer);
	for (int i = 7 - last_bits; i < 8; i++) // Read needed bits from last byte
		compressed.insert(compressed.begin(), (((bitbuffer >> i) & 1) == 1) ? '1' : '0');

	fin.seekg(-3, ios::end);
	for (char bitbuffer; fin.get(bitbuffer);) { // Read next byte while bytes aren't over
		for (int i = 0; i < 8; i++) // Read bits from byte and write them to string
			compressed.insert(compressed.begin(), (((bitbuffer >> i) & 1) == 1) ? '1' : '0');
		fin.seekg(-2, ios::cur); // Go to next byte
	}

	fin.close();


	/* Create tree using tree file */
	filename.pop_back(); 
	filename.pop_back();
	filename.pop_back();
	string tree_filename = "tree" + filename + "bin"; // Tree filename
	BinaryTree* tree = new BinaryTree(new BinaryTree::Node(0, '\0', nullptr, nullptr));
	BinaryTree::Node* cur = tree->get_root();
	ifstream treein(tree_filename);
	Queue q;
	q.enqueue(cur);
	string cur_line;
	getline(treein, cur_line);
	while (!q.isEmpty()) {
		if (!treein.eof()) {
			getline(treein, cur_line);
			int line_index = 0; // Current element of current line in file
			cur = q.dequeue();
			while (line_index < cur_line.size()) {
				if (cur_line[line_index] == 'E' && line_index + 1 < cur_line.size() && cur_line[line_index + 1] == 'M') { // If EM write empty node to the tree
					if (cur->get_left() == nullptr) { // Write as left child
						cur->set_left(new BinaryTree::Node(0, '\0', nullptr, nullptr));
						line_index += 3;
						q.enqueue(cur->get_left());
					}
					else if (cur->get_right() == nullptr) { // Write as right child
						cur->set_right(new BinaryTree::Node(0, '\0', nullptr, nullptr));
						line_index += 3;
						q.enqueue(cur->get_right());
					}
					else if (!q.isEmpty()) { // Get next node
						cur = q.dequeue();
					}
				}
				else if (cur_line[line_index] == 'S' && line_index + 1 < cur_line.size() && cur_line[line_index + 1] == 'P') { // If SP write node with space to the tree
					if (cur->get_left() == nullptr) { // Write as left child
						cur->set_left(new BinaryTree::Node(0, ' ', nullptr, nullptr)); 
						line_index += 3;
					}
					else if (cur->get_right() == nullptr) { // Write as right child
						cur->set_right(new BinaryTree::Node(0, ' ', nullptr, nullptr));
						line_index += 3;
					}
					else if (!q.isEmpty()) { // Get next node
						cur = q.dequeue();
					}
				}
				else if (cur_line[line_index] == 'N' && line_index + 1 < cur_line.size() && cur_line[line_index + 1] == 'L') { // If NL write node with \n to the tree
					if (cur->get_left() == nullptr) { // Write as left child
						cur->set_left(new BinaryTree::Node(0, '\n', nullptr, nullptr));
						line_index += 3;
					}
					else if (cur->get_right() == nullptr) { // Write as right child
						cur->set_right(new BinaryTree::Node(0, '\n', nullptr, nullptr));
						line_index += 3;
					}
					else if (!q.isEmpty()) { // Get next node
						cur = q.dequeue();
					}
				}
				else { // If letter, write node letter to the tree
					if (cur->get_left() == nullptr) { // Write as left child
						cur->set_left(new BinaryTree::Node(0, cur_line[line_index], nullptr, nullptr));
						line_index += 2;
					}
					else if (cur->get_right() == nullptr) { // Write as right child
						cur->set_right(new BinaryTree::Node(0, cur_line[line_index], nullptr, nullptr));
						line_index += 2;
					}
					else if (!q.isEmpty()) { // Get next node
						cur = q.dequeue();
					}
				}
			}
		}
		else // If end of file
			break;
	}


	/* Decompress text using Huffman tree */
	string uncompressed("");

	cur = tree->get_root();
	for (size_t i = 0; i < compressed.size(); i++) { 
		if (cur != nullptr && compressed[i] == '0') // Go to the left subtree if current num is 0
			cur = cur->get_left();
		else if (cur != nullptr) // Go to the right subtree if current num is 1
			cur = cur->get_right();
		if (cur != nullptr && cur->get_letter() != '\0') { // If current node has letter
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