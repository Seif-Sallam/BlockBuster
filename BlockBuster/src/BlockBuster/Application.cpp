#include "BlockBuster/Application.h"
#include "BlockBuster/Common.h"
#include "BlockBuster/ResourceManager.h"

#include <Utils/Logger.h>

#include <imgui-SFML.h>
#include <imgui.h>

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
    NONE,
};

Application::Application(int argc, const char* argv[])
    : m_Window(sf::RenderWindow(sf::VideoMode(800,600), "BlockBuster"))
{
    m_IsInFocus = m_Window.hasFocus();
    parseArgs(argc, argv);

    ImGui::SFML::Init(m_Window, true);
    m_View = m_Window.getDefaultView();
    ResourceManager::get().registerFromXML(RESOURCE_DIR"Spritesheet/sokoban_spritesheet.xml");
    m_Map.loadMap(RESOURCE_DIR"Maps/TestMap.png");
    m_Bob.Init();
    m_Bob.setTilePosition(sf::Vector2i(5, 5));
}

void Application::run()
{
    while(m_Window.isOpen())
    {
        handleEvents();
        m_IsInFocus = m_Window.hasFocus();
        if (m_IsInFocus)
        {
            update();
            imGuiLayer();
            render();
        }
    }
}

void Application::bobMovement(const sf::Time &deltaTime)
{
    static sf::Time timeDelay = sf::milliseconds(0);
    timeDelay = timeDelay + deltaTime;

    // We only move every 100 milliseconds. to avoid too many keypresses
    if (timeDelay.asMilliseconds() < 100)
        return;

    timeDelay = sf::Time{};

    auto dir = NONE;
    auto newPosition = m_Bob.getTilePosition();

    // Determine the direction and the new position.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        dir = RIGHT;
        newPosition.x += 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        dir = LEFT;
        newPosition.x -= 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        dir = UP;
        newPosition.y -= 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        dir = DOWN;
        newPosition.y += 1;
    }

    if (dir != NONE)
    {

        // CHECK THIS BS
        //FIXME: The Cratets logic is not correct and is not consistent.
        auto type = m_Map.getTileType(newPosition);
        bool canMoveCrate = true;/*canMoveACrate(newPosition, RIGHT);*/

        if (type == COUNT)
            return;

        if (type != BLOCKED && type != BLOCKED_EXIT && canMoveCrate)
        {
            m_Bob.setTilePosition(newPosition);
//            moveCrateInDir(newPosition, RIGHT);
        }
    }
}

void Application::cratesLogic(const sf::Time& deltaTime)
{

}

void Application::handleEvents()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (m_IsInFocus)
            ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
            m_Window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Tilde)
                m_DrawLogger = !m_DrawLogger;
            if (event.key.code == sf::Keyboard::Escape)
                m_Window.close();
        }

        if (event.type == sf::Event::Resized)
        {
            m_View.setSize(sf::Vector2f(m_Window.getSize()));
            m_View.setCenter(m_View.getSize() / 2.0f);
        }

    }
}

void Application::update()
{
    auto deltaTime = m_InternalClock.restart();
    ImGui::SFML::Update(m_Window, deltaTime);

    bobMovement(deltaTime);

    cratesLogic(deltaTime);
}

void Application::render()
{
    m_Window.setView(m_View);
    m_Window.clear();
    m_Window.draw(m_Map);
    m_Window.draw(m_Bob);

    if (m_DrawLogger)
        Util::Logger::Draw("Logger", &m_DrawLogger);
    ImGui::SFML::Render(m_Window);
    m_Window.display();
}

void Application::imGuiLayer()
{
}

void Application::parseArgs(int argc, const char* argv[])
{

}