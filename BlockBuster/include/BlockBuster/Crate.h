#pragma once

#include <SFML/Graphics.hpp>

class Crate : public sf::Drawable, public sf::Transformable
{
public:
    Crate();

    void setTiledPosition(const sf::Vector2i& position);
    inline sf::Vector2i getTiledPosition() const { return m_Position; }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
private:
    sf::Sprite m_Sprite;
    sf::Texture m_Texture;
    sf::Vector2i m_Position;
};