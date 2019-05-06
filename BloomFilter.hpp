/* Description: This is a program that defines the bloom filter program
 * that inserts a string into three positions in a table so
 * that it can be found later. The program's purpose is to reduce
 * the chance of false positives being found.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 05, 2019
 * Sources: Piazza
 */

#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <string>

using namespace std;

/**
 * The class for bloom filter that provides memory efficient check
 * of whether an item has been inserted before. Small amount of 
 * false positives is possible but there will be no false negatives.
 */
class BloomFilter {

public:

    /* Create a new bloom filter with the size in bytes */
    BloomFilter(size_t numBytes);

    /* Insert an item into the bloom filter */
    void insert(std::string item);

    /* Determine whether an item is in the bloom filter */
    bool find(std::string item);
	
	/* Destrctor for the bloom filter */
    ~BloomFilter();

private:

    // The char array as the hash table
    unsigned char * table;
    unsigned int numSlots;

	/* Hash function1, takes a string, and table size and returns index*/
	unsigned int hashFunc1(std::string item, unsigned int size);

	/* Hash function2, takes a string, and table size and returns index*/
	unsigned int hashFunc2(std::string item, unsigned int size);

	/* Hash function3, takes a string, and table size and returns index*/
	unsigned int hashFunc3(std::string item, unsigned int size);
};
#endif // BLOOM_FILTER
