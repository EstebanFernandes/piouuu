#pragma once
#include"Card.h"
class CardUpgrade : public Card
{
private:
	std::vector<sf::Text> Stats;
public:
	std::vector<std::string> type;
	std::vector<std::string> Upgrade;
	const int trueNumber;
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	CardUpgrade() : trueNumber(-1){}
	CardUpgrade(int levelofEntity);//Nouvelle CardUpgrade pour quand on a complété toutes les améliorations
	CardUpgrade(std::vector<std::string> Upgrade, std::vector<std::string> type, AssetManager* assetParam,int trueNumber_);
	//Surcharge pour une amélioration
	CardUpgrade(std::string Upgrade, std::string type, AssetManager* assetParam);
	void setPosition(sf::Vector2f r);
	//resize le text pour qu'il ne dépasse pas, ne descend pas en dessous de la taille de caractère 20
	//Va falloir faire un truc pour rendre plus jolie les noms des types, surement plus dans upgradestate cela dit
	void update(float deltaTime);
	void reduceScale();
	//Fonction qui resize une liste de texte compte tenu d'une bordure en hauteur et en largeur
	void resizeTexts();
	void fillSpace(std::vector<sf::Text>& texts, sf::FloatRect border);
	void fillSpace(sf::Text& text, sf::FloatRect border);
	void setStatsCharSize(unsigned int size)
	{
		for (int i = 0; i < Stats.size(); i++)
		{
			Stats[i].setCharacterSize(size);
		}
	}
	unsigned int getStatsCharSize()
	{
		unsigned int minSize = 1000;
		for (int i = 0; i < Stats.size(); i++)
		{
			unsigned int curSize = Stats[i].getCharacterSize();
			if (minSize > curSize)
			{
				minSize = curSize;
			}
		}
		return minSize;
	}
	void setSize(sf::Vector2f size);
	void setTitle(std::string titre)
	{
		cardTitle.setString(titre);
	}
	void setFontColor(sf::Color color)
	{
		cardTitle.setFillColor(color);
		cardDescription.setFillColor(color);
		for (sf::Text& stat : Stats)
		{
			stat.setFillColor(color);
		}
	}
	void setBackColor(sf::Color color)
	{
		cardBack.setFillColor(color);
	}
};

