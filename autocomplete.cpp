#include "DictionaryTrie.hpp"
#include "DictionaryTrieNode.hpp"
using namespace std;

/**
 * IMPORTANT! You should use the following lines of code to match the correct output:
 * 
 * cout << "This program needs exactly one argument!" << endl;
 * cout << "Reading file: " << file << endl;
 * cout << "Enter a prefix/pattern to search for:" << endl;
 * cout << "Enter a number of completions:" << endl;
 * cout << completion << endl;
 * cout << "Continue? (y/n)" << endl;
 * 
 * arg 1 - Input file name (in format like freq_dict.txt)
 */
int main(int argc, char** argv)
{
	DictionaryTrie * myTrie = new DictionaryTrie();
	myTrie->insert("at", 4);
	cout << myTrie->insert("ate", 6) << endl;
	cout << myTrie->getRoot()->data << endl;
	delete myTrie;
}
