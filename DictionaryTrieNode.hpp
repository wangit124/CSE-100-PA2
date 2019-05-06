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

#include <string>
#include <utility>
#include <iostream>

using namespace std;

typedef std::pair <std::string, unsigned int> myPair;

/* DictionaryTrieNode class defines the left, right and middle children 
 * of the current node. It also stores the character, as well as a flag
 * to check if it is the end of a word. 
 */
class DictionaryTrieNode {

	public:

		char data; // the data stored in this node
		unsigned int frequency; // The word frequency, only stored at leaf
		unsigned int maxFreqBelow; // Maximum frequency in subtree

		DictionaryTrieNode * middle; // middle child
		DictionaryTrieNode * left; // left child
		DictionaryTrieNode * right; // right child
		
		// Constructor.  Initialize a TrieNode with left, right, middle, freq
		DictionaryTrieNode(char d) : data(d) { 
		    frequency = maxFreqBelow = 0;
			middle = left = right = nullptr;	
		}
};

/** The comparator used in sorting points based on frequency*/
struct CompareNodes {
    bool operator() (const myPair & p1, const myPair & p2) {
		// Define <, > and equal operators
		if (p1.second > p2.second) {
			return true;
		}
		else if (p1.second < p2.second) {
			return false;
		}
		else {
			// if equal, sort alphabetically
			if (p1.first.compare(p2.first) > 0) {
				return false;
			}
			else {
				return true;
			}
		}
	}
};
#endif // DICTIONARYTRIENODE_HPP

