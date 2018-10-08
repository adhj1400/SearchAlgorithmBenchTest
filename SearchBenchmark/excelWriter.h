/*
 * Instead of manually copying ALL values from a test table console
 * program, why not just create a spreadsheet compatible with MS Excel?
 * Author: Adam Hjernquist
 */

#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

class excelWriter
{
public:
	excelWriter();
	~excelWriter();

	void push_seq(std::vector<std::string>, std::string);
	void remove(int x, int y);
	void clear();
	void createSpreadsheet();

private:
	std::vector<std::vector<std::string> > spreadSheet;
};

