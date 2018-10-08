#include "stdafx.h"
#include "primeGenerator.h"


/*
*  Constructor that initializes the creation of the primelist
*/
primeGenerator::primeGenerator(std::string file, size_t SIZE) {

	set(file, SIZE);    // Create list of primes

}


primeGenerator::~primeGenerator()
{
}


/*
*  Decide if we should read primes from a previously generated prime list stored inside a textfile
*  or if we should create a brand new list. This is useful since the prime generation process is
*  slow on a new list.
*/
void primeGenerator::set(std::string file, size_t SIZE) {

	std::ifstream reader;
	reader.open(file);

	if (reader.is_open() && SIZE == getOldFileSize()) {
		reader.close();
		list = readFromFile(file, SIZE);    // Read from the file and set it to the current primelist

	}
	else {
		std::cerr << "NOTICE: Old file detected! Old file will be discarded." << std::endl;
		reader.close();
		list = eratosthenesSieve(SIZE);     // Create a new list of primes and set it to the current primelist

		writeToFile(file, list, SIZE);      // Make a backup of <list>
	}

}


/*
*  Creates a vector<int> of prime numbers according to "Eratosthenes Sieve" Algorithm and
*  gives it back to the function caller.
*/
std::vector<int> primeGenerator::eratosthenesSieve(size_t SIZE) {

	std::cout << "Generating primes... \t";

	std::vector<size_t> emptyList;
	std::vector<int> primeList;

	// Fyll emptyList med tomma värden
	for (size_t n = 0; n < SIZE; n++) {
		emptyList.push_back(true);
	}

	// Repetera tills alla icke-primtal enligt listans index är markerade true.
	for (size_t x = 2; x <= sqrt(SIZE); ++x) {
		if (emptyList[x] == true) {
			for (size_t y = pow(x, 2); y < SIZE; y = y + x) {
				emptyList[y] = false;
			}
		}
	}

	// För varje värde list[x] == true, fyll med respektive x-värde.
	for (size_t x = 2; x < emptyList.size(); x++) {
		if (emptyList[x] == 1) {
			primeList.push_back(x);
		}
	}

	std::cout << "Done!" << std::endl;

	return primeList;
}


/*
*  Print the primelist for debug.
*/
void primeGenerator::print() {

	std::vector<int> primeList = get();

	for (int x = 0; x < primeList.size(); x++) {
		std::cout << list[x] << std::endl;
	}

}


/*
*  Output the current primelist to a file for backup purposes. Also stores the size
*  in a separate textfile.
*/
void primeGenerator::writeToFile(std::string file, std::vector<int>& newList, size_t SIZE) {
	std::cout << "Creating backup...\t";

	std::ofstream writer;
	writer.open(file);

	for (int x = 0; x < newList.size(); x++) {
		writer << newList[x] << std::endl;
	}

	writer.close();
	std::cout << "Done!" << std::endl;

	// Update oldFile.txt
	std::ofstream oldFileWriter;
	oldFileWriter.open("oldSize.txt");
	oldFileWriter << SIZE;  // Update the value that the biggest prime can be.
	oldFileWriter.close();
}


/*
*  Read from <file> and make it the current primelist.
*/
std::vector<int> primeGenerator::readFromFile(std::string file, size_t SIZE) {
	std::ifstream reader;
	reader.open(file);

	std::vector<int> oldList;   // The old list inside the text file is stored here
	int p = 0;

	while (reader >> p) {        // Read the file until end-of-file
		oldList.push_back(p);
	}

	reader.close();
	return oldList;             // Give back the stored list

}


/*
*  Returns the primelist
*/
std::vector<int> primeGenerator::get() {
	return list;
}


/*
*  Returns how many primes there are in the primelist
*/
int primeGenerator::getSize() {
	return list.size();
}


/*
*  Returns a random prime from the primelist.
*/
int primeGenerator::getRandomPrime() {
	int upperLimit = get().size();

	while (true) {
		int random = rand() % upperLimit;

		if (random < 3) {
			return 0;
		}

		bool is_Prime = true;

		for (int i = 2; i <= random / 2; ++i) {
			if (random % i == 0) {
				is_Prime = false;
				break;
			}
		}

		if (is_Prime == true) {
			return random;
		}
	}
	return 0;
}


/*
*  Opens and reads the oldSize.txt and returns the old size inside. It is used to check if dimension of
*  the backup-primelist from previous runtimes is the same as the new desired size.
*/
int primeGenerator::getOldFileSize() {
	std::ifstream reader;
	reader.open("oldSize.txt");

	if (!reader.is_open()) {
		return 0;
	}

	int x;
	reader >> x;        // Write to file.
	reader.close();

	return x;

}