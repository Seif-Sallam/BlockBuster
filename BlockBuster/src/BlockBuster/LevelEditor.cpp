#include "BlockBuster/LevelEditor.h"
#include "BlockBuster/Common.h"

constexpr const float ZOOM_THRESHOLD_MIN = 0.2f;
constexpr const float ZOOM_THRESHOLD_MAX = 4.0f;

LevelEditor::LevelEditor(sf::RenderWindow* renderWindow)
{
    m_RenderWindow = renderWindow;
    m_View = renderWindow->getDefaultView();
    m_View.setCenter(sf::Vector2f(renderWindow->getSize() / 2u));
    m_View.setSize(sf::Vector2f(renderWindow->getSize()));
    m_ZoomLevel = 1.0f;
    m_UpdateGrid = true;
}

void LevelEditor::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelMoved)
    {
        float zoomDelta = event.mouseWheel.delta * -0.1f;
        m_ZoomLevel += zoomDelta;
        if (m_ZoomLevel < ZOOM_THRESHOLD_MIN)
            m_ZoomLevel = ZOOM_THRESHOLD_MIN;
        else if (m_ZoomLevel > ZOOM_THRESHOLD_MAX)
            m_ZoomLevel = ZOOM_THRESHOLD_MAX;

        m_View.setSize(sf::Vector2f(m_RenderWindow->getSize()) * m_ZoomLevel);
        Util::Logger::Debug("ZOOMING: {}, {}", m_ZoomLevel, zoomDelta);
        m_UpdateGrid = true;
    }
    else if (event.type == sf::Event::Resized)
    {
        m_View = m_RenderWindow->getDefaultView();
        m_View.setCenter(sf::Vector2f(m_RenderWindow->getSize() / 2u));
        m_View.setSize(sf::Vector2f(m_RenderWindow->getSize()) * m_ZoomLevel);
        m_UpdateGrid = true;
    }
}

void LevelEditor::update(const sf::Time& deltaTime)
{
    if (m_UpdateGrid)
    {
        // Something is wrong here, I am not sure what is wrong though.
        sf::Vector2f horizontal{}, vertical{};
        if (m_ZoomLevel < 1.0f)
        {
            horizontal.x =  m_View.getSize().x - m_RenderWindow->getSize().x;    // there is no panning right now
            vertical.x = m_View.getSize().y - m_RenderWindow->getSize().y;      // there is no panning right now
        }
        else
        {
            horizontal.x = m_RenderWindow->getSize().x - m_View.getSize().x;    // there is no panning right now
            vertical.x = m_RenderWindow->getSize().y - m_View.getSize().y;      // there is no panning right now
        }
        horizontal.y = m_View.getSize().x;
        vertical.y = m_View.getSize().y;

        m_Grid.updateBoundries(horizontal, vertical);
        m_UpdateGrid = false;
    }
}

void LevelEditor::imguiLayer()
{

}

void LevelEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_RenderWindow->setView(m_View);
    m_RenderWindow->clear();

    target.draw(m_Grid);
    // target.draw(m_BlockHighlight);
    // for(auto& block : m_BlocksMap)
    // {
    //     target.draw(block.second);
    // }
}

sf::Vector2f LevelEditor::getMousePosition()
{

    return sf::Vector2f{};
}

sf::Vector2i LevelEditor::getTilePosition(const sf::Vector2i)
{

    return sf::Vector2i{};
}

void LevelEditor::updateBlockHighlight()
{

}

void LevelEditor::addBlock(const sf::Vector2i& tilePosition)
{

}
