#include "ParserCSV.h"

namespace IO {
	bool isEmpty(std::vector<std::vector<std::string>>& matrix)
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (!matrix[i][j].empty())
					return false;
			}
		}
		return true;
	}

	std::vector< std::vector<std::string>> retrieveCSVFile(std::string filePath)
	{
		ParserCSV parser(filePath);
		return parser.getElements();
	}
}

void IO::ParserCSV::parseFile()
{
	std::ifstream file(sFileName);
	if (!file.is_open()) {
		std::cout << "Can't open file\n";
	}
	while (std::getline(file, sCurrentLine)) {
		if(!sCurrentLine.empty())
		{
			fileElements.push_back(std::vector<std::string>());
			lineAnalysis();
			imaxRow++;
		}
	}
}

void IO::ParserCSV::lineAnalysis()
{
	unsigned int col=0;
	int substr = 0;
	std::string temp = sCurrentLine;
	while (substr != std::string::npos)
	{
		substr = (int)temp.find(";");
		fileElements[imaxRow].push_back(temp.substr(0, substr));
		temp = temp.substr(substr + 1);
		col++;
	}
	if (col > imaxCol)
		imaxCol = col;
}
 
IO::ParserCSV::ParserCSV()
{
	imaxCol = -1;
	imaxRow = -1;
	sFileName = "";
}

IO::ParserCSV::ParserCSV(std::string fileName,bool display)
{
	imaxCol = 0;
	imaxRow = 0;
	sFileName = fileName;
	parseFile();
	if(display==true)
		displayInfo();
}
