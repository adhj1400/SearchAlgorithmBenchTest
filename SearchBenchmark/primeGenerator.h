#pragma once

#include <vector>
#include <fstream>
#include <iostream>

class primeGenerator
{
public:
	primeGenerator(std::string file, size_t SIZE);
	~primeGenerator();

	std::vector<int> eratosthenesSieve(size_t SIZE);
	std::vector<int> get();
	int getRandomPrime();
	int getSize();
	void print();

private:
	std::vector<int> list;  // The primelist

							// Private functions
	int getOldFileSize();
	void set(std::string, size_t);
	void writeToFile(std::string, std::vector<int>&, size_t);
	std::vector<int> readFromFile(std::string, size_t);

};

