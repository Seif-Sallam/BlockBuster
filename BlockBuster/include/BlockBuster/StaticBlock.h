#pragma once

#include <SFML/Graphics.hpp>

#include <Utils/Logger.h>

class StaticBlock : public sf::Drawable, public sf::Transformable, public sf::FloatRect
{
public:
    StaticBlock();

    void setTiledPosition(const sf::Vector2i& tiledPosition);
    const sf::Vector2i& getTiledPosition() const;
    void setTexture(const std::string& textureName);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
private:
    sf::Sprite m_Sprite;
    sf::Vector2i m_TiledPosition;
    sf::Texture* m_Texture;
    // Add shader for extra effects?
};