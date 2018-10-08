#include "stdafx.h"
#include "excelWriter.h"


excelWriter::excelWriter() {}

excelWriter::~excelWriter() {}

void excelWriter::push_seq(std::vector<std::string> data, std::string dataName) {
	data.insert(data.begin(), dataName);
	spreadSheet.push_back(data);
}

void excelWriter::remove(int x, int y) {}

void excelWriter::clear() {
	spreadSheet.clear();
}

void excelWriter::createSpreadsheet() {
	std::ofstream output;
	output.open("results.csv");
	if (output.is_open()) {
		output << "sep=:" << std::endl;		// Define separator

		for (int y = 0; y < spreadSheet[0].size(); y++)
		{
			for (int x = 0; x < spreadSheet.size(); x++)
			{
				std::cout << spreadSheet[x][y] << "\t";
				output << spreadSheet[x][y] << ":";
			}

			std::cout << std::endl;
			output << std::endl;
		}

		output.close();
	}
	else std::cerr << "\aERROR: Spreadsheet could not be created." << std::endl;
}
