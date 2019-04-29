/* Description: This is a program that stores words in a ternary tree and
 * can autocomplete searches based on this sorted data. It can autocomplete
 * based on a prefix, or based on a matching pattern in a word. It will 
 * return a specified number of the most related words in the dictionary, 
 * in alphabetical order.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 28, 2019
 * Sources: Piazza
 */

#include "DictionaryTrie.hpp"
#include "DictionaryTrieNode.hpp"
using namespace std;

/**
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
