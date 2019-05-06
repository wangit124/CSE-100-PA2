/* Description: This is a program designed to test the
 * hash functions used in Bloom Filter. It counts the 
 * number of collisions to determine the latency. 
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 06, 2019
 * Sources: Piazza, Hash_Functions.docx from PA2
 * writeup
 */

#include "BloomFilter.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#define SHIFT 0x80 // Bit to shift and XOR with
#define FIRSTFIVE 0xf8000000 // Hex to get first 5 bits
#define FIRSTFOUR 0xf0000000 // Hex to get first 4 bits
#define FIRSTBIT 0x80000000 // Hex to get first bit
#define SHIFT4 4 // Define shift value 4
#define SHIFT5 5 // Define shift value 5
#define SHIFT24 24 // Define shift value 24
#define SHIFT27 27 // Define shift value 27
#define SHIFT31 31 // Define shift value 31

using namespace std;

const unsigned int DEFAULT_SIZE = 5;
const unsigned int RESIZE_FACTOR = 2;
const double MAX_LOAD_FACTOR = 0.67;

// stores number of inserted items in each slot
vector<unsigned int> table(DEFAULT_SIZE);

// stores all the hash value of inserted items
vector<unsigned int> inserted;

unsigned int tableLen = DEFAULT_SIZE;
unsigned int numElem = 0;

/* The hash function that we are testing for collisions 
 * Currently testing hashFunc3 from BloomFilter.hpp
 */
unsigned int hashFunc(const std::string & item) {
	// Define sum and highorder
	unsigned int sum = 0;
	unsigned int highOrder = 0;

	// Call srand to set seed for random generator
	srand(time(0));
	unsigned int random = 0;

	// For each character in item, perform hashing
	for (unsigned int i=0; i<item.length(); i++) {
		// Get random number between 0 and item length
		random = rand() % item.length();
		
		// hash the current sum
		highOrder = sum & FIRSTBIT;
		sum = sum << 1;
		sum = sum ^ (highOrder >> SHIFT31);
		sum = sum ^ item.at(random); 
	}
	
	// Return a modded table index
	return sum%tableLen;
}

/** Returns the number of collisions in the hash table */
unsigned int countCollision() {
	// Count up number of collisions
	unsigned int currNum = 0;
	unsigned int sum = 0;
	for (unsigned int i=0; i<tableLen; i++) {
		// Get each table element
		currNum = table[i];
		
		// If the number of elements in bucket > 1, count up
		if (currNum > 1) {
			sum += (currNum - 1);
		}
	}
	return sum;
}

/** When load factor is high, rehash all the inserted items */
void rehash() {

    // print out the stats before each rehash
    std::cout << "#insertions: " << numElem
    << "; hash table size: " << tableLen
    << "; #collisions: " << countCollision() << std::endl;
    
    tableLen = tableLen * RESIZE_FACTOR;
    table.clear();
    table.resize(tableLen);
    // rehash all the inserted items
    for (unsigned int hashVal: inserted) {
        table[hashVal % tableLen]++;
    }
}

/** "Insert" a given item to hash table. This function does not 
 *  actually insert the item, it only increases the count of number
 *  of items inserted in the hashed slot.
 */
void insert(const std::string & item) 
{
    // rehash if load factor is high
    if ((double) numElem / tableLen >= MAX_LOAD_FACTOR) {
        rehash();
    }
    unsigned int hashVal = hashFunc(item);
    table[hashVal % tableLen]++;
    numElem++;
    inserted.push_back(hashVal);
}

int main(int argc, const char * argv[]) {
    
    // reads the file line by line and insert each line to hash 
    // table to output stats about the hash function
    ifstream items (argv[1]);
    string line;
    
    while (true) {
        getline(items, line);
        if (items.eof()) break;
        insert(line);
    }    
}

