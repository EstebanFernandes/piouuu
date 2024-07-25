#pragma once
#include"SFML/Graphics.hpp"
#include"CButton.h"
#include"CCardUpgrade.h"
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
	/// <summary>
	/// renvoie le minimum de charactère pour : le titre 0, les stats 1, la description 2
	/// </summary>
	/// <param name="uiList"></param>
	/// <param name="type"></param>
	/// <returns></returns>
	static int getCardMinCharSize(std::vector<CCardUpgrade>& uiList,int type = 0) {

		unsigned int min = 100000;
		for (int i = 0; i < uiList.size(); i++)
		{
			unsigned int curMax = min + 1;
			switch (type)
			{
			case 0:
				curMax = uiList[i].getTitleCharSize();
				break;
			case 1:
				curMax = uiList[i].getStatsCharSize();
				break;
			case 2:
				curMax = uiList[i].getDescriptionCharSize();
				break;
			}
			if (min > curMax)
				min = curMax;
		}
		return min;
	}

	/// <summary>
	/// Apply the min character size thats possible on the vector of UI pass in parameter
	/// </summary>
	/// <param name="buttonlist"></param>
	static void applyCardUpgrademaxMinCharSize(std::vector<CCardUpgrade>& uiList)
	{
		for (int i = 0; i < 3; i++)
		{
			unsigned int charSize = -1;
			switch (i)
			{
			case 0:
				charSize = getCardMinCharSize(uiList,i);
				break;
			case 1:
				charSize = getCardMinCharSize(uiList, i);
				break;
			case 2:
				charSize = getCardMinCharSize(uiList, i);
				break;
			}
			for (int j = 0; j < uiList.size(); j++)
			{
				switch (i)
				{
				case 0:
					uiList[j].setTitleCharSize(charSize);
					break;
				case 1:
					uiList[j].setStatsCharSize(charSize);
					break;
				case 2:
					uiList[j].setDescriptionCharSize(charSize);
					break;
				}
			}
		}
	}

	static int getMinCharSize(std::vector<CCard>& cards, int part)
	{
		unsigned int minCharSize = 10000;
		for (int i = 0; i < cards.size(); i++)
		{
			switch (part)
			{
			case 0://Title 
				if (minCharSize > cards.at(i).getTitleCharSize())
					minCharSize = cards[i].getTitleCharSize();
				break;
			case 1://Description
				if (minCharSize > cards.at(i).getDescriptionCharSize())
					minCharSize = cards[i].getDescriptionCharSize();
				break;

			}
		}
		return (int)minCharSize;
	}




};

