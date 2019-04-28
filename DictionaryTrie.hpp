/* Description: This is a program that defines the trie
 * program that can store to-be-searched words. It can
 * create a network of nodes that stores each character
 * in each word and allow that word to be searched for in 
 * different ways.
 *
 * CSE 100 PA2 C++ Autocomplete
 * Authors: Jor-el Briones, Christine Alvarado, Howard Wang (luw055)
 * 
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: April 27, 2019
 * Sources: Piazza
 */
#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <queue>
#include "DictionaryTrieNode.hpp"

using namespace std;

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Get the root of the trie*/
  DictionaryTrieNode * getRoot();

  /* Get the size of the trie*/
  int getSize();

  /** 
   * Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string). This might be useful for testing
   * when you want to test a certain case, but don't want to
   * write out a specific word 300 times.
   */
  bool insert(std::string word, unsigned int freq);

  /* Helper method for insert, uses recursion
   * @param takes in the current node, the string to insert, and
   * the current index
   * @return returns true if success, false if failure
   */
  bool insertHelper(DictionaryTrieNode * curr, std::string word, 
					unsigned int currInd, unsigned int frequency);

  /* Return true if word is in the dictionary, and false otherwise. */
  bool find(std::string word) const;

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
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

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
  std::vector<std::string>
  predictUnderscore(std::string pattern, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
	
  int trieSize; // The number of nodes in the trie
  DictionaryTrieNode * root; //Starting node of the data structure
	
};

#endif // DICTIONARY_TRIE_H
