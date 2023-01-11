#pragma once
#include <SFML/Graphics.hpp>

#include "BlockBuster/Common.h"

class CrateSpot : public sf::Drawable, public sf::Transformable
{
public:
    CrateSpot();

    void setTileTexture(const std::string& tileTextureName);
    void setTileType(TileType tileType);
    TileType getTileType();
    void setTiledPosition(const sf::Vector2i& position);
    inline sf::Vector2i getTiledPosition() const { return m_TilePosition; }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
private:
    sf::Sprite m_TileSprite;
    sf::Texture* m_TileTexture;

    sf::Sprite m_TileColorSprite;
    sf::Texture* m_TileColorTexture;

    TileType m_TileType;
    sf::Vector2i m_TilePosition;
};