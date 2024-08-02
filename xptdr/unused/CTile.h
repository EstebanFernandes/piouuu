#pragma once
#include <SFML/Graphics.hpp>
class CTile
{
private:
	sf::Sprite sprite;
	bool damaging;
public:
	//Constructeurs et destructeurs
	CTile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool _damaging = false);

	//Méthodes
	const sf::FloatRect getGlobalBounds();
	void update();
	void render(sf::RenderTarget& target);
};

