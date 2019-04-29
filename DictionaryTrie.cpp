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
	
	// Call insert helper method
	return insertHelper(&root, word, 0, freq);
}			

/* Helper method for insert, uses recursion
* @param takes in the current node, the string to insert, and
* the current index
* @return returns true if success, false if failure
*/
bool DictionaryTrie::insertHelper(DictionaryTrieNode** currPtr,std::string word, 
								   unsigned int currInd, unsigned int frequency) 
{
	// Get current character to insert
	char insertChar = word.at(currInd);

	// If current node is empty, insert and return true
	if (!(*currPtr)) {
		*currPtr = new DictionaryTrieNode(insertChar);
	}

	// Get data of current node
	char currChar = (*currPtr)->data;
	
	// Check if data is smaller
	if (insertChar < currChar) {
		return insertHelper(&((*currPtr)->left), word, currInd+1, frequency);
	}
	// If larger, go right
	else if (insertChar > currChar) {
		return insertHelper(&((*currPtr)->right), word, currInd+1, frequency);
	}
	// Otherwise go middle
	else {
		if (currInd != (word.length()-1)) {
			return insertHelper(&((*currPtr)->middle), word, currInd+1, 
									frequency);
		}
		else {
			// If duplicate, return false
			if (((*currPtr)->frequency) != 0) {
				return false;
			}

			// Otherwise set endWord and frequency
			(*currPtr)->frequency = frequency;

			return true;
		}
	}
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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, 
												unsigned int num_completions)
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
std::vector<string> DictionaryTrie::predictUnderscore(std::string pattern, 
												  unsigned int num_completions)
{
}

/* Helper method to destructor, deletes all nodes*/
void DictionaryTrie::deleteAll(DictionaryTrieNode ** currPtr)
{
	// While there is still memory, delete it
	if ((*currPtr)->left) 
		deleteAll(&((*currPtr)->left));
	
	if ((*currPtr)->middle) 
		deleteAll(&((*currPtr)->middle));

	if ((*currPtr)->right) 
		deleteAll(&((*currPtr)->right));
		
	delete (*currPtr);
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
	deleteAll(&root);
}

