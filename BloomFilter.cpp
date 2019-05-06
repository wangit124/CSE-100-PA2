/* Description: This is the bloom filter program
 * that inserts a string into three positions in a table so
 * that it can be found later. The program's purpose is to reduce
 * the chance of false positives being found.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 05, 2019
 * Sources: Piazza, Hash_Functions.docx from PA2
 * writeup
 */

#include "BloomFilter.hpp"
#include <cstdlib>
#include <ctime>

#define BYTE 8 // Define 8 bits in a byte
#define SHIFT 0x80 // Bit to shift and XOR with
#define FIRSTFIVE 0xf8000000 // Hex to get first 5 bits
#define FIRSTFOUR 0xf0000000 // Hex to get first 4 bits
#define FIRSTBIT 0x80000000 // Hex to get first bit
#define SHIFT4 4 // Define shift value 4
#define SHIFT5 5 // Define shift value 5
#define SHIFT24 24 // Define shift value 24
#define SHIFT27 27 // Define shift value 27
#define SHIFT31 31 // Define shift value 31

/* Create a new bloom filter with the size in bytes */
BloomFilter::BloomFilter(size_t numBytes)
{
	// Set table slot size
	numSlots = numBytes * BYTE;
	
	// Allocate numBytes for character array
	table = new unsigned char[numBytes];
}

/* Insert an item into the bloom filter */
void BloomFilter::insert(std::string item) 
{
	// Call each hash function and set correspond table bit
	unsigned int slot1 = hashFunc1(item, numSlots);
	unsigned int slot2 = hashFunc2(item, numSlots);
	unsigned int slot3 = hashFunc3(item, numSlots);

	// Get index into table
	unsigned int index1 = slot1/BYTE;
	unsigned int index2 = slot2/BYTE;
	unsigned int index3 = slot3/BYTE;

	// Get slot relative to closest minimum index
	unsigned int slotInd1 = slot1 - (index1*BYTE);
	unsigned int slotInd2 = slot2 - (index2*BYTE);
	unsigned int slotInd3 = slot3 - (index3*BYTE);

	// Get OR bytes for each slot
	unsigned char OR1 = SHIFT >> slotInd1;
	unsigned char OR2 = SHIFT >> slotInd2;
	unsigned char OR3 = SHIFT >> slotInd3;

	// Set bits in table
	table[index1] |= OR1;
	table[index2] |= OR2;
	table[index3] |= OR3;
}

/* Hash function1, takes a string, 
 * manipulates first 5 bits of each cumulative ascii
 * sum and returns index. Known as CRC variant.
 */
unsigned int BloomFilter::hashFunc1(std::string item, unsigned int size)
{
	// Define sum and highorder
	unsigned int sum = 0;
	unsigned int highOrder = 0;

	// For each character in item, perform hashing
	for (unsigned int i=0; i<item.length(); i++) {
		highOrder = sum & FIRSTFIVE;
		sum = sum << SHIFT5;
		sum = sum ^ (highOrder >> SHIFT27);
		sum = sum ^ item.at(i);
	}
	
	// Return a modded table index
	return sum%size;
}

/* Hash function2, takes a string, and table size and returns index
 * Known as PJW hash, left shift by 4 bits then manipulate 
 */
unsigned int BloomFilter::hashFunc2(std::string item, unsigned int size)
{
	// Define sum and topBits
	unsigned int sum = 0;
	unsigned int topBits = 0;

	// For each character in item, perform hashing
	for (unsigned int i=0; i<item.length(); i++) {
		sum = (sum << SHIFT4) + item.at(i);
		topBits = sum & FIRSTFOUR;
		if (topBits != 0) {
			sum = sum ^ (topBits >> SHIFT24);
			sum = sum ^ topBits;
		}
	}
	
	// Return a modded table index
	return sum%size;
}

/* Hash function3, takes a string, and table size and returns index
 */
unsigned int BloomFilter::hashFunc3(std::string item, unsigned int size)
{
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
	return sum%size;
}

/* Determine whether an item is in the bloom filter */
bool BloomFilter::find(std::string item) 
{
	// Call each hash function and get correspond table slot
	unsigned int slot1 = hashFunc1(item, numSlots);
	unsigned int slot2 = hashFunc2(item, numSlots);
	unsigned int slot3 = hashFunc3(item, numSlots);

	// Get index into table
	unsigned int index1 = slot1/BYTE;
	unsigned int index2 = slot2/BYTE;
	unsigned int index3 = slot3/BYTE;

	// Get slot relative to closest minimum index
	unsigned int slotInd1 = slot1 - (index1*BYTE);
	unsigned int slotInd2 = slot2 - (index2*BYTE);
	unsigned int slotInd3 = slot3 - (index3*BYTE);

	// Get OR bytes for each slot
	unsigned char OR1 = SHIFT >> slotInd1;
	unsigned char OR2 = SHIFT >> slotInd2;
	unsigned char OR3 = SHIFT >> slotInd3;

	// Set bits in table
	unsigned char check1 = table[index1] & OR1;
	unsigned char check2 = table[index2] & OR2;
	unsigned char check3 = table[index3] & OR3;

	// If all three bits are set, return true
	if (check1 == OR1 && check2 == OR2 && check3 == OR3) {
		return true;
	}
	return false;
}

/* Destrctor for the bloom filter */
BloomFilter::~BloomFilter()
{
	// Delete table
	delete table;
}
