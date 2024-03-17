#pragma once
#include"CSommet.h"
#include<vector>
/// <summary>
/// Extension de la classe CSommet, adapté aux arbres d'améliorations
/// </summary>
class CSommetUpgrade : public CSommet
{
private:
	std::vector<std::string> values;
public:
	CSommetUpgrade(int num) {
		iSOMNumero = num;
	}
	CSommetUpgrade() {
		iSOMNumero = -1;
	}
	void addValue(std::string value)
	{
		values.push_back(value);
	}
	std::vector<std::string> returnValues()
	{
		return values;
	}
};

