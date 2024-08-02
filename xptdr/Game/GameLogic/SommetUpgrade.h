#pragma once
#include"Sommet.h"
#include<vector>
/// <summary>
/// Extension de la classe Sommet, adapt� aux arbres d'am�liorations
/// </summary>
class SommetUpgrade : public Sommet
{
private:
public:
	std::vector<std::string> values;
	SommetUpgrade(int num) {
		iSOMNumero = num;
	}
	SommetUpgrade() {
		iSOMNumero = -1;
	}
	void addValue(std::string value)
	{
		values.push_back(value);
	}
	std::vector<std::string>& returnValues()
	{
		return values;
	}
};

