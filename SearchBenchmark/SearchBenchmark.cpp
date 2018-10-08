// SearchBenchmark.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

// Class files
#include "linearSearcher.h"
#include "binarySearcher.h"
#include "skipSearcher.h"
#include "hashSearcher.h"
#include "primeGenerator.h"
#include "excelWriter.h"

int rand_plus();

int main() {
	srand(time(NULL));	// Generate "random" seed.
	std::string         file = "primelist.txt";	// Backup of old primelist.
	size_t              primeRoof = 100000000;	// Highest prime < primeRoof
	int                 N = 128;				// Start value
	int                 T = 12;                 // Times to increment search (antal mätpunkter)
	int					lNRND = 100000;
	int					bNRND = 10000000;
	int					sNRND = 10000000;
	int					hNRND = 10000000;
	std::vector<int>    primes;
	linearSearcher      linearsearcher;
	binarySearcher      binarysearcher;
	primeGenerator      primeList(file, primeRoof);

	/*
	*  Some context
	*/
	std::cout	<< "\n*------* Info\n"
				<< "*   This program will use different search algorithms to search \n"
				<< "*   for random integers within a portion of a list filled with \n"
				<< "*   prime numbers. The list consists of " << primeList.getSize() << " primes in total, but \n"
				<< "*   only a portion of this list will be searched. \n"
				<< "*       - Primes to check (1st): " << N << "\n"
				<< "*       - Binary increments:     " << T << "\n"
				<< "*\n"
				<< "*---------------------------------------------------* End of info\n"
				<< std::endl;

	primes = primeList.get();

	excelWriter spreadSheet;
	std::vector<std::string> result;

	// Fill vector with X-axis values for the spreadsheet
	for (int S = N; S < N*pow(2, T); S = S * 2) {
		if (S == N)		result.push_back("0");
		result.push_back(std::to_string(S));
	}
	spreadSheet.push_seq(result, "Values");
	result.clear();
	/*
	// Linear search
	std::cout << "Linear Search:" << std::endl;
	std::cout << "TIME (s)\tAMOUNT\tFOUND" << std::endl;
	for (int S = N; S < N*pow(2, T); S = S*2) {
		if (S == N)		result.push_back("0.000000");

		int count = 0;
		clock_t start = clock();

		for (int x = 0; x < lNRND; x++)		count += linearsearcher.search(primes, rand_plus(), S);

		// Display results
		clock_t stop = clock();
		float t = (1.0*(stop - start)) / CLOCKS_PER_SEC;
		std::cout << t << "\t\t" << S << "\t" << count << std::endl;
		result.push_back(std::to_string(t));
	}
	spreadSheet.push_seq(result, "Linear search");
	result.clear();


	// Binary search
	std::cout << "\nBinary Search:" << std::endl;
	std::cout << "TIME (s)\tAMOUNT\tFOUND" << std::endl;
	for (int S = N; S < N*pow(2, T); S = S * 2) {
		if (S == N)		result.push_back("0.000000");

		int count = 0;
		clock_t start = clock();

		for (int x = 0; x < bNRND; x++)		count += binarysearcher.search(primes, rand_plus(), S);

		// Display results.
		clock_t stop = clock();
		float t = (1.0*(stop - start)) / CLOCKS_PER_SEC;
		std::cout << t << "\t\t" << S << "\t" << count << std::endl;
		result.push_back(std::to_string(t));
	}
	spreadSheet.push_seq(result, "Binary search");
	result.clear();
	

	// Skip search
	std::cout << "\nSkip Search:" << std::endl;
	std::cout << "TIME (s)\tAMOUNT\tFOUND" << std::endl;
	for (int S = N; S < N*pow(2, T); S = S * 2) {
		if (S == N)		result.push_back("0.000000");

		skipSearcher skipsearcher;
		skipsearcher.fill(primes, S);
		int count = 0;
		clock_t start = clock();

		for (int x = 0; x < sNRND; x++)		count += skipsearcher.find(rand_plus());

		// Display results.
		clock_t stop = clock();
		float t = (1.0*(stop - start)) / CLOCKS_PER_SEC;
		std::cout << t << "\t\t" << S << "\t" << count << std::endl;
		result.push_back(std::to_string(t));
	}
	spreadSheet.push_seq(result, "Skip search");
	result.clear();*/
	

	// Hash search
	std::cout << "\nHash Search:" << std::endl;
	std::cout << "TIME (s)\tAMOUNT\tFOUND" << std::endl;
	//hashSearcher hashsearcher(primes[N*pow(2,T)]);
	//hashsearcher.fill(primes, N*pow(2,T));

	for (int S = N; S < N*pow(2, T); S = S * 2) {
		if (S == N)		result.push_back("0.000000");

		hashSearcher hashsearcher(N);
		hashsearcher.fill(primes, S);
		int count = 0;
		clock_t start = clock();

		for (int x = 0; x < hNRND; x++)		count += hashsearcher.find(rand_plus());

		// Display results.
		clock_t stop = clock();
		float t = (1.0*(stop - start)) / CLOCKS_PER_SEC;
		std::cout << t << "\t\t" << S << "\t" << count << std::endl;
		result.push_back(std::to_string(t));
	}
	spreadSheet.push_seq(result, "Hash search");
	result.clear();
	
	std::cout << std::endl << "Results:" << std::endl;
	spreadSheet.createSpreadsheet();

    return 0;
}

int rand_plus() {
	return (rand() * (rand() % 10 + 1));
}