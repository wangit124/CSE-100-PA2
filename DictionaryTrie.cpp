/* Description: This is a program that defines the trie
 * program that can store to-be-searched words. It can
 * create a network of nodes that stores each character
 * in each word and allow that word to be searched for in 
 * different ways.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 27, 2019
 * Sources: Piazza
 */

#include "DictionaryTrieNode.hpp"
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
	// Set root to null, size to 0
	root = nullptr;
	trieSize = 0;
}

/* Method to get the root of DictionaryTrie*/
DictionaryTrieNode * DictionaryTrie::getRoot() 
{
	return root;
}

/* Method to return the size of the trie*/
int DictionaryTrie::getSize()
{
	return trieSize;
}

/** 
 * Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string). This might be useful for testing
 * when you want to test a certain case, but don't want to
 * write out a specific word 300 times.
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	// Check if word is empty
	if (word.length() == 0) {
		return false;
	}
	
	// Store return value
	bool returnVal;

	// Create copy of root
	DictionaryTrieNode * curr = root;
		
	// If trie is empty, simply insert word
	if (!curr) {
		// Add word.length() new nodes
		for (unsigned int i=0; i<word.length(); i++) {
			// Insert differently at the last character
			if (i == (word.length()-1)) {
				curr = new DictionaryTrieNode(word.at(i));
				curr->frequency = freq;
				curr->endWord = true;
			}
			else {
				curr = new DictionaryTrieNode(word.at(i));
			}
			
			// Go to next node
			curr = curr->middle;
		}

		// set return value
		returnVal = true;
	}
	else {
		// If tree not empty, call helper method
		returnVal = insertHelper(curr, word, 0, freq);
	}

	return returnVal;
}			

/* Helper method for insert, uses recursion
* @param takes in the current node, the string to insert, and
* the current index
* @return returns true if success, false if failure
*/
bool DictionaryTrie::insertHelper(DictionaryTrieNode * curr, std::string word, 
								   unsigned int currInd, unsigned int frequency) 
{
	// Get current character to insert
	char insertChar = word.at(currInd);

	// If current node is empty, insert and return true
	if (!curr) {
		curr = new DictionaryTrieNode(insertChar);
	}

	// Get data of current node
	char currChar = curr->data;
	
	// Check if data is smaller
	if (insertChar < currChar) {
		insertHelper(curr->left, word, currInd+1, frequency);
	}
	// If larger, go right
	else if (insertChar > currChar) {
		insertHelper(curr->right, word, currInd+1, frequency);
	}
	// Otherwise go middle
	else {
		if (currInd != (word.length()-1)) {
			insertHelper(curr->middle, word, currInd+1, frequency);
		}
		else {
			// If duplicate, return false
			if (curr->endWord) {
				return false;
			}

			// Otherwise set endWord and frequency
			curr->frequency = frequency;
			curr->endWord = true;
		}
	}
	// if successful, return true
	return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
}


/* 
 * Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
}

/* Return up to num_completions of the most frequent completions
 * of the pattern, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The pattern itself might be included in the returned words if the pattern
 * is a word (and is among the num_completions most frequent completions
 * of the pattern)
 */
std::vector<string> DictionaryTrie::predictUnderscore(std::string pattern, unsigned int num_completions)
{
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
}
