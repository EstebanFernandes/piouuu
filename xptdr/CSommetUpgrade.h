#pragma once
#include"CSommet.h"
#include<vector>
class CSommetUpgrade : public CSommet
{
private:
	std::vector<std::string> keywords;
	std::vector<std::string> values;
};

