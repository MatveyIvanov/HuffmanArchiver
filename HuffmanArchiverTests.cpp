#include "pch.h"
#include "CppUnitTest.h"

#include "../HuffmanArchiver.cpp"
#include "../PriorityQueue.cpp"
#include "../Queue.cpp"
#include "../Map.cpp"
#include "../Stack.cpp"
#include "../BinaryTree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HuffmanArchiverTests
{
	TEST_CLASS(HuffmanArchiverTests)
	{
		TEST_METHOD(TestCountFrequency) // Test frequency counting
		{
			string text("Some test text");
			Map<char, int> freq = count_frequency(text);
			Assert::AreEqual(1, freq.find('S'));
			Assert::AreEqual(3, freq.find('e'));
			Assert::AreEqual(2, freq.find(' '));
			Assert::AreEqual(4, freq.find('t'));
		}
		TEST_METHOD(TestHuffmanTree) // Test Huffman tree creation
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
		TEST_METHOD(TestHuffmanTable) // Test Huffman table creation
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
		TEST_METHOD(TestCompressDecompress) // Compress and decompress text. Compare the original text with the de-encoded text
		{
			string file_text("To be, or not to be, that is the question:\
				Whether 'tis nobler in the mind to suffer\
				The slings and arrows of outrageous fortune,\
				Or to take arms against a sea of troubles\
				And by opposing end them.To die—to sleep,\
				No more; and by a sleep to say we end\
				The heart - ache and the thousand natural shocks\
				That flesh is heir to : 'tis a consummation\
				Devoutly to be wish'd. To die, to sleep;\
				To sleep, perchance to dream—ay, there's the rub:\
				For in that sleep of death what dreams may come,\
				When we have shuffled off this mortal coil,\
				Must give us pause—there's the respect\
				That makes calamity of so long life.\
				For who would bear the whips and scorns of time,\
				Th'oppressor's wrong, the proud man's contumely,\
				The pangs of dispriz'd love, the law's delay,\
				The insolence of office, and the spurns\
				That patient merit of th'unworthy takes,\
				When he himself might his quietus make\
				With a bare bodkin ? Who would fardels bear,\
				To grunt and sweat under a weary life,\
				But that the dread of something after death,\
				The undiscovere'd country, from whose bourn\
				No traveller returns, puzzles the will,\
				And makes us rather bear those ills we have\
				Than fly to others that we know not of?\
				Thus conscience doth make cowards of us all,\
				And thus the native hue of resolution\
				Is sicklied o'er with the pale cast of thought,\
				And enterprises of great pith and moment\
				With this regard their currents turn awry\
				And lose the name of action.");
			Map<char, int> freq = count_frequency(file_text);
			BinaryTree* tree = huffman_tree(freq);
			Map<char, string> table = huffman_table(tree);
			compress_n_write(table, file_text, "text.txt", tree);
			string decompressed = read_n_decompress("text.txt");
			Assert::IsTrue(file_text == decompressed);
		}
	};
}
