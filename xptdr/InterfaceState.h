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
	int getLargestCharSize(std::vector<CButton*>& buttonlist) {
		
		unsigned int max = 0;
		for (int i = 0; i < buttonlist.size(); i++)
		{
			unsigned int tempMax = buttonlist[i]->getCharacterSize();
			if (tempMax > max)
				max = tempMax;
		}
		return max;
	}

	int getMinCharSize(std::vector<CButton>& buttonlist) {

		unsigned int max =100000;
		for (int i = 0; i < buttonlist.size(); i++)
		{
			unsigned int tempMax = buttonlist[i].getCharacterSize();
			if (max> tempMax)
				max = tempMax;
		}
		return max;
	}

	/// <summary>
	/// Apply the min character size thats possible on the vector of button pass in parameter
	/// </summary>
	/// <param name="buttonlist"></param>
	void applymaxMinCharSize(std::vector<CButton>& buttonlist)
	{
		unsigned int charSize = getMinCharSize(buttonlist);
		for (int i = 0; i < buttonlist.size(); i++)
		{
			buttonlist[i].setCharacterSize(charSize);
		}
	}
};

