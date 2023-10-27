#include "CParserCSV.h"

void CParserCSV::parseFile()
{
	std::ifstream file(sFileName);
	if (!file.is_open()) {
		std::cout << "Can't open file\n";
	}
	while (std::getline(file, sCurrentLine)) {
		fileElements.push_back(std::vector<std::string>());
		lineAnalysis();
		imaxRow++;
	}
}

void CParserCSV::lineAnalysis()
{
	unsigned int col=0;
	int substr = 0;
	std::string temp = sCurrentLine;
	while (substr != std::string::npos)
	{
		substr = temp.find(";");
		fileElements[imaxRow].push_back(temp.substr(0, substr));
		temp = temp.substr(substr + 1);
		col++;
	}
	if (col > imaxCol)
		imaxCol = col;
}

CParserCSV::CParserCSV(std::string fileName)
{
	imaxCol = 0;
	imaxRow = 0;
	sFileName = fileName;
	parseFile();
	displayInfo();
}
