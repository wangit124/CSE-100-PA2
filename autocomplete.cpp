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
#include "util.hpp"
#include <fstream>
#include <sstream>

using namespace std;

/**
 * Autocomplete main program, prompts user to search
 * for a prefix, and returns matching words
 * autocompleted.
 */
int main(int argc, char** argv)
{
  	// Check valid arguments
	if(argc < 2){
		cout << "This program needs exactly one argument!" << endl;
        	exit(-1);
    	}
	
	// Read file
	char * file = argv[1];
	cout << "Reading file: " << file << endl;

	// Read file
	ifstream in;
    	in.open(file, ios::binary);

	// Load dictionary
    	DictionaryTrie* dictionary_trie = new DictionaryTrie();

    	Utils::load_dict(*dictionary_trie, in);

	// Define vector to store results
	vector <std::string> results;

	// Read in prefix and print completions
	while (true) {
        	string prefix;
		string ws;		
		string response;
		int num_completions;

		cout << "Enter a prefix/pattern to search for:" << endl;	
		getline(cin, prefix);
		
		cout << "Enter a number of completions:" << endl;
		getline(cin, ws);
		num_completions = stoi(ws);
		
		results = dictionary_trie->predictCompletions(prefix,num_completions);
    
		// Print all completions
		for (unsigned int i=0; i<results.size(); i++) {
			cout << results[i] << endl;
		}
		
		// Prompt user to continue, if not, exit
		cout << "Continue? (y/n)" << endl;
		getline(cin, response);
		
		if(response.compare("n") == 0) {
			break;
		}
	}

	delete dictionary_trie;
}
