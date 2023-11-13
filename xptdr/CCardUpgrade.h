#pragma once
#include"CCard.h"
class CCardUpgrade : public CCard
{
private:
	std::vector<sf::Text> Stats;
public:
	std::vector<std::string> type;

	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	CCardUpgrade(){}
	CCardUpgrade(float x, float y, std::string title, std::string description, std::vector<std::string> Upgrade, std::vector<std::string> type, CAssetManager* assetParam);
	CCardUpgrade( std::vector<std::string> Upgrade, std::vector<std::string> type, CAssetManager* assetParam);
	void setPosition(sf::Vector2f r);
	//resize le text pour qu'il ne dépasse pas, ne descend pas en dessous de la taille de caractère 20
	//Va falloir faire un truc pour rendre plus jolie les noms des types, surement plus dans upgradestate cela dit
	void resizeText(sf::Text& textToResize);
	void update(float deltaTime);
	sf::Vector2f getPosition() { return cardBack.getPosition(); }
	sf::Vector2f getSize() { return cardBack.getSize(); }
	void setOutlineThickNess(float r) { cardBack.setOutlineThickness(r); }
};

