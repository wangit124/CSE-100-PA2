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
	threshold.first = "";
	threshold.second = 0;
}

/* Method to get the root of DictionaryTrie*/
DictionaryTrieNode * DictionaryTrie::getRoot() 
{
	return root;
}

/* Method to get the complete queue of DictionaryTrie*/
myQueue DictionaryTrie::getComplete() 
{
	return complete;
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
		return insertHelper(&((*currPtr)->left), word, currInd, frequency);
	}
	// If larger, go right
	else if (insertChar > currChar) {
		return insertHelper(&((*currPtr)->right), word, currInd, frequency);
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
	// Check if word is empty
	if (word.length() == 0) {
		return false;
	}
	
	// Call insert helper method
	return findHelper(root, word, 0);
}

/* Helper method to find if word is in the dictionary
 * @params current node, string to check, and currIndex
 * @return true if found, false otherwise
 */
bool DictionaryTrie::findHelper(DictionaryTrieNode * curr, std::string word, 
				  unsigned int currInd) const
{
	// Get current character to insert
	char findChar = word.at(currInd);

	// If current node is empty, reached end of search
	if (!curr) {
		return false;
	}

	// Get data of current node
	char currChar = curr->data;
	
	// Check if data is smaller
	if (findChar < currChar) {
		return findHelper(curr->left, word, currInd);
	}
	// If larger, go right
	else if (findChar > currChar) {
		return findHelper(curr->right, word, currInd);
	}
	// Otherwise go middle
	else {
		if (currInd != (word.length()-1)) {
			return findHelper(curr->middle, word, currInd+1);
		}
		else {
			// If duplicate, return true
			if ((curr->frequency) != 0) {
				return true;
			}

			return false;
		}
	}
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
	// Get root node
	DictionaryTrieNode * curr = root;

	// Create a vector to store strings
	vector<std::string> empty;
	
	// if prefix is empty, or num_completions is empty, return empty
	if (prefix.length() == 0 || num_completions == 0) {
		return empty;
	}
	
	// Empty complete and set threshold to 0
	while (!complete.empty()) {
		complete.pop();
	}
	threshold.first = "";
	threshold.second = 0;

	// Create prefix string
	std::string builder = prefix;

	// Initialize current prefix and current character
	char currPrefix;
	char currChar;
	unsigned int currIndex = 0;

	// First traverse to end of prefix
	while (true) {
		// If curr is null, return empty
		if (!curr) {
			return empty;
		}

		// Get current prefix
		currPrefix = prefix.at(currIndex);
		currChar = curr->data;

		if (currPrefix < currChar) {
			curr = curr->left;
		}
		else if (currPrefix > currChar) {
			curr = curr->right;
		}
		else {
			// If checking last character, see if prefix is a completion
			if (currIndex == prefix.length()-1) {
				if (curr->frequency > 0) {
					myPair prefixComplete (prefix, curr->frequency);
					updateCompletion(prefixComplete, num_completions);
				}
			}
			curr = curr->middle;
			currIndex++;
		}
		
		// If at end of prefix, break
		if (currIndex == prefix.length()) {
			break;
		}
	}
		
	// Call helper method to recurse through all possible words
	predictHelper(curr, builder, num_completions);

	// Pop from pQueue and store in vector
	while (complete.size() > 0) {
		empty.insert(empty.begin(), complete.top().first);
		complete.pop();
	}

	return empty;
}

/* Helper method to find completions given a prefix
 * @params current node, string to build
 */
void DictionaryTrie::predictHelper(DictionaryTrieNode*curr, std::string builder,
					unsigned int num_completions) 
{
	// Check if curr is null
	if (!curr) {
		return;
	}

	// Build up string
	std::string prevBuild = builder;
	builder += curr->data;
	
	// If curr does not equal null, check if end of word
	if ((curr->frequency) != 0) {
		// Create pair
		myPair nodeComplete (builder, curr->frequency);
		
		// Call update method
		updateCompletion(nodeComplete, num_completions);
	}

	// Traverse left, middle, right
	if (curr->left) {
		predictHelper(curr->left, prevBuild, num_completions);
	}
	if (curr->middle) {
		predictHelper(curr->middle, builder, num_completions);
	}
	if (curr->right) {
		predictHelper(curr->right, prevBuild, num_completions);
	}
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
	// Create empty vector
	vector <std::string> empty;
	return empty;
}

/* Helper method to update the complete data structure, takes in a pair
 * and sees if needs to be pushed into list
 * @param current pair to push, and number of completions to have
 */
void DictionaryTrie::updateCompletion(myPair & currPair, unsigned int k) 
{
	// Check if size of array is equal to k
	if (complete.size() == k) {
	
		// Update threshold if better
		if (currPair.second > threshold.second) {
			// If so, remove max element and push current
			complete.pop();
			complete.push(currPair);
		}
		else {
			if (currPair.second == threshold.second) {
				// If equal, compare alphabetically
				if (currPair.first.compare(threshold.first) < 0) {
					// If so, remove max element and push current
					complete.pop();
					complete.push(currPair);
				}
			}
		}

		// Set threshold
		myPair minFreq = complete.top();
		threshold = minFreq;
	}
	else {
		// If k nodes haven't been reached, push node 
		complete.push(currPair);
		
		// If reached k items, set threshold
		if (complete.size() == k) {
			// Set threshold
			myPair minFreq = complete.top();
			threshold = minFreq;
		}
	} 
}

/* Helper method to destructor, deletes all nodes*/
void DictionaryTrie::deleteAll(DictionaryTrieNode ** currPtr)
{
	// Check if root is null
	if (!(*currPtr)) {
		return;
	}

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

