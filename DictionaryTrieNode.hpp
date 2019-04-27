/* Description: This is a program that defines a node that holds
 * a single letter, in an autocomplete program that uses tries
 * to store words.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 26, 2019
 * Sources: Piazza
 */

#ifndef DICTIONARYTRIENODE_HPP
#define DICTIONARYTRIENODE_HPP
#include <iostream>

using namespace std;

template<typename Data>

/* DictionaryTrieNode class defines the left, right and middle children of the
 * current node. It also stores the data AKA the character, as well as a flag
 * to check if it is the end of a word. 
 */
class DictionaryTrieNode {

	public:

		// Constructor.  Initialize a TrieNode with left, right, middle, freq
		// and flag
		DictionaryTrieNode(const Data & d) : data(d), frequency(0), endWord(0){
		    middle = left = right = nullptr;	
		}

		DictionaryTrieNode<Data>* middle; // middle child
		DictionaryTrieNode<Data>* left; // left child
		DictionaryTrieNode<Data>* right; // right child
		unsigned int frequency; // The word frequency, only stored at leaf
		Data const data;   // the data stored in this node
		bool endWord; // Flag to check if this is the end of a word

};
#endif // DICTIONARYTRIENODE_HPP

