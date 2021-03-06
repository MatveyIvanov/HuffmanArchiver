#include "pch.h"
#include "CppUnitTest.h"

#include "../HuffmanArchiver.cpp"
#include <boost/dynamic_bitset.hpp>
#include "../PriorityQueue.cpp"
#include "../Queue.cpp"
#include "../impl.cpp"
#include "../Stack.cpp"
#include "../BinaryTree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HuffmanArchiverTests
{
	TEST_CLASS(HuffmanArchiverTests)
	{
		TEST_METHOD(TestCountFrequency)
		{
			string text("Some test text");
			Map<char, int> freq = count_frequency(text);
			Assert::AreEqual(1, freq.find('S'));
			Assert::AreEqual(3, freq.find('e'));
			Assert::AreEqual(2, freq.find(' '));
			Assert::AreEqual(4, freq.find('t'));
		}
		TEST_METHOD(TestHuffmanTree)
		{
			string text("Some test text");
			Map<char, int> freq = count_frequency(text);
			BinaryTree* tree = huffman_tree(freq);
			string tree_elements[15];
			int i = 0;
			Queue q;
			q.enqueue(tree->get_root());
			while (!q.isEmpty()) {
				BinaryTree::Node* temp = q.dequeue();
				if (temp->get_left() != nullptr)
					q.enqueue(temp->get_left());
				if (temp->get_right() != nullptr)
					q.enqueue(temp->get_right());
				if (temp->get_letter() == '\n')
					tree_elements[i++] = "NL";
				else if (temp->get_letter() == ' ')
					tree_elements[i++] = "SP";
				else if (temp->get_letter() == '\0')
					tree_elements[i++] = "EM";
				else
					tree_elements[i++] = temp->get_letter();
			}
			string expected[15] = { "EM" ,"EM" ,"EM", "e","EM" ,"EM", "t", "o", "EM","EM", "SP", "x", "s", "m", "S" };
			for (int i = 0; i < 15; i++)
				Assert::AreEqual(expected[i], tree_elements[i]);
		}
		TEST_METHOD(TestHuffmanTable)
		{
			string text("Some test text");
			Map<char, int> freq = count_frequency(text);
			BinaryTree* tree = huffman_tree(freq);
			Map<char, string> table = huffman_table(tree);
			Assert::AreEqual((string)"1001", table.find('S'));
			Assert::AreEqual((string)"101", table.find(' '));
			Assert::AreEqual((string)"0111", table.find('s'));
			Assert::AreEqual((string)"1000", table.find('m'));
			Assert::AreEqual((string)"00", table.find('e'));
			Assert::AreEqual((string)"010", table.find('o'));
			Assert::AreEqual((string)"11", table.find('t'));
			Assert::AreEqual((string)"0110", table.find('x'));
		}
		TEST_METHOD(TestCompressDecompress)
		{
			ifstream fin("text.txt");
			string file_text((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
			fin.close();
			Map<char, int> freq = count_frequency(file_text);
			BinaryTree* tree = huffman_tree(freq);
			Map<char, string> table = huffman_table(tree);
			compress_n_write(table, file_text, "text.txt", tree);
			string decompressed = read_n_decompress("text.txt");
			Assert::IsTrue(file_text == decompressed);
		}
	};
}
