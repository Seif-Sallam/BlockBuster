#include "BlockBuster/Grid.h"
#include "BlockBuster/Common.h"

#include "Utils/Logger.h"

#define TILE_SIZE ((float)TILE_SIZE)

Grid::Grid()
{
    m_VertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
}

void Grid::updateBoundries(sf::Vector2f horizontal, sf::Vector2f vertical)
{
    Util::Logger::Debug("Horizontal: {}, Vertical: {}", horizontal, vertical);
    m_StartPosition.x = horizontal.x / (uint32_t)TILE_SIZE;
    m_StartPosition.y = vertical.x / (uint32_t)TILE_SIZE;

    m_EndPosition.x = horizontal.y / (uint32_t)TILE_SIZE;
    m_EndPosition.y = vertical.y / (uint32_t)TILE_SIZE;

    sf::Vector2i numOfPoints{(int32_t)(m_EndPosition.x - m_StartPosition.x), (int32_t)(m_EndPosition.y - m_StartPosition.x)};

    m_VertexArray.clear();

    for (int i = 0; i <= numOfPoints.x; i++) {
        sf::Vertex v1{}, v2{};
        v1.color = sf::Color::White;
        v2.color = sf::Color::White;
        v1.position.x = horizontal.x + TILE_SIZE * i;
        v1.position.y = vertical.x;
        v2.position.x = horizontal.x + TILE_SIZE * i;
        v2.position.y = vertical.y;

        m_VertexArray.append(v1);
        m_VertexArray.append(v2);
    }
    for (int j = 0; j <= numOfPoints.y; j++) {
        sf::Vertex v1{}, v2{};
        v1.color = sf::Color::White;
        v2.color = sf::Color::White;
        v1.position.x = horizontal.x;
        v1.position.y = vertical.x + TILE_SIZE * j;
        v2.position.x = horizontal.y;
        v2.position.y = vertical.x + TILE_SIZE * j;

        m_VertexArray.append(v1);
        m_VertexArray.append(v2);
    }
    Util::Logger::Info("Updated size of the screen to be Start: {}, End: {}", m_StartPosition, m_EndPosition);
    Util::Logger::Info("Number of verticies in the grid vertex array: {}", m_VertexArray.getVertexCount());
}


void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_VertexArray, states);
}