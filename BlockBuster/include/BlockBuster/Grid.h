#pragma once
#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable, public sf::Transformable
{
public:
    Grid();

    void updateBoundries(sf::Vector2f horizontal, sf::Vector2f vertical);
    inline sf::Vector2i getSpanningSize() const { return m_SpanningSize; }
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

private:
    sf::VertexArray m_VertexArray;

    sf::Vector2f m_StartPosition;
    sf::Vector2f m_EndPosition;
    sf::Vector2i m_SpanningSize;
};