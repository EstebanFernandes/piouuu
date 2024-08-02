#include "CTile.h"

CTile::CTile(sf::Texture& texture_sheet, sf::IntRect texture_rect, bool _damaging)
{
    sprite.setTexture(texture_sheet);
    sprite.setTextureRect(texture_rect);
    damaging = _damaging;

}

const sf::FloatRect CTile::getGlobalBounds()
{
    return sprite.getGlobalBounds();
}

void CTile::render(sf::RenderTarget& target)
{
    target.draw(sprite);
}
