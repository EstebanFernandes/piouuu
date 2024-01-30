#pragma once
#include"SFML/Graphics.hpp"
#include"CButton.h"
/// <summary>
/// Interface that implement method useful for CState inherit
/// </summary>
class InterfaceState
{
public:
	/// <summary>
	/// return the largest charactersize in a vector of button
	/// </summary>
	/// <param name="buttonlist"></param>
	/// <returns></returns>
	int getLargestCharSize(std::vector<CUI*>& uiList) {
		
		unsigned int max = 0;
		for (int i = 0; i < uiList.size(); i++)
		{
			unsigned int tempMax = uiList[i]->getCharacterSize();
			if (tempMax > max)
				max = tempMax;
		}
		return max;
	}

	int getMinCharSize(std::vector<CUI*>& uiList) {

		unsigned int max =100000;
		for (int i = 0; i < uiList.size(); i++)
		{
			unsigned int tempMax = uiList[i]->getCharacterSize();
			if (max> tempMax)
				max = tempMax;
		}
		return max;
	}

	/// <summary>
	/// Apply the min character size thats possible on the vector of UI pass in parameter
	/// </summary>
	/// <param name="buttonlist"></param>
	void applymaxMinCharSize(std::vector<CUI*>& uiList)
	{
		unsigned int charSize = getMinCharSize(uiList);
		for (int i = 0; i < uiList.size(); i++)
		{
			uiList[i]->setCharacterSize(charSize);
		}
	}
};

