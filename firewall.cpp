/* Description: This program runs the bloom filter, which can be
 * used to test for malicious urls. Specifically, spam urls that
 * have been seen before will be reported as malicious. This
 * program can also calculate the percentage of urls it deemed
 * falsely as malicious. Overall it is a testing/benchmark
 * program.
 *
 * Name: Luhao Wang
 * Email: luw055@ucsd.edu
 * Date: May 06, 2019
 * Sources: Piazza
 */

#include "BloomFilter.hpp"
#include "util.hpp"
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#define FILEARG1 1
#define FILEARG2 2
#define FILEOUT 3
#define MEMRATIO 3
#define HALF 2

using namespace std;

/**
 * Main method, checks valid arguments, and prints out 
 * memory ratio.
 *
 * arg1 - list of malicious urls/bad words filter out
 * arg2 - list of mixed (good/bad) to only write good urls to
 * arg3 - file to write only the good urls to (one on each line)
 */

int main(int argc, char** argv) {
 	// Check valid arguments
	if(argc < 4){
		cout << "This program requires 3 arguments!" << endl;
        exit(-1);
    }
	
	// Store arguments
	char * badUrls = argv[FILEARG1];
	char * genUrls = argv[FILEARG2];
	char * outputFile = argv[FILEOUT];
    
	// Read files
	ifstream in;
    in.open(badUrls, ios::binary);
	std::string line = "";
    unsigned int countLines = 0;

	// Count up number of lines and bytes
	while (!in.eof()) {
        getline(in, line);
		countLines++;
    }
	
	// Calculate max bytes
	unsigned int maxBytes = countLines * MEMRATIO/HALF; 
	
	// Allocate Bloom filter
	BloomFilter * myFilter = new BloomFilter(maxBytes);

	// insert badURL lines
	while (!in.eof()) {
        getline(in, line);
		myFilter->insert(line);
    }	
	
	// open outputFile
	ofstream out;
	out.open(outputFile, ios::binary);
	
	// Open genUrls file
	in.close();
	in.open(genUrls, ios::binary);

	// Count number of genUrls and write bad ones to output
	unsigned int countGen = 0;
	unsigned int countOut = 0;

	while (!in.eof()) {
		// read url
        getline(in, line);

		// Search for URL, if not found, then write
		bool check = myFilter->find(line);
		if (!check) {
			// Count number of output Urls
			countOut++;
			out << line << endl;
		}
		
		// Count up general URLs
		countGen++;
    }

	// Calculate number of safeUrls
	unsigned int safeUrls = countGen - countLines;
	
	// Subtract safeUrls from ground truth
	int difference = (signed int)(safeUrls - countOut);

	// Calculate false positive rate
	double falsePos = (double) difference / safeUrls;
	
	// Determine file size
	unsigned int numBytes = 0;
	struct stat st;

	// If error stating file, set numBytes to 0
	if (stat(badUrls, &st) != 0) {
		numBytes = 0;
	}
	else {
		numBytes = (unsigned int)st.st_size;
	}

	// Calculate saved memory ratio
	double memRatio = (double) numBytes / maxBytes;

	// Print false positive rate and other information
	cout << "False positive rate: " << abs(falsePos) << endl;
	cout << "Saved memory ratio: " << memRatio << endl; 
	
	// Close filestreams
	in.close();
	out.close();
	delete myFilter;
}
