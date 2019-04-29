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

/* DictionaryTrieNode class defines the left, right and middle children 
 * of the current node. It also stores the character, as well as a flag
 * to check if it is the end of a word. 
 */
class DictionaryTrieNode {

	public:

		char data; // the data stored in this node
		unsigned int frequency; // The word frequency, only stored at leaf

		DictionaryTrieNode * middle; // middle child
		DictionaryTrieNode * left; // left child
		DictionaryTrieNode * right; // right child
		
		// Constructor.  Initialize a TrieNode with left, right, middle, freq
		DictionaryTrieNode(char d) : data(d) { 
		    frequency = 0;
			middle = left = right = nullptr;	
		}
};
#endif // DICTIONARYTRIENODE_HPP

