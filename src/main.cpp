#include <iostream>
#include <string>
#include <vector>
#include "Pendulum.h"

int32_t main()
{
    // Here we set the constant values for the window width and height
    constexpr int32_t WINDOW_WIDTH = 1000;
    constexpr int32_t WINDOW_HEIGHT = 1000;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Double Pendulum", sf::Style::Default, settings);

    sf::Event event;

    Pendulum p1(100, 90, 220, window.getSize().x / 2, 175);
    Pendulum p2(100, 90, 220, &p1);


    sf::Clock clock; 

    std::vector<sf::Vertex> line;
    sf::Vertex *lineArr; 

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
                
        }

        p2.update();
        line.push_back(sf::Vertex(p2.updatePos(clock.getElapsedTime().asSeconds() * 20), sf::Color::Black));
        p1.updatePos(clock.getElapsedTime().asSeconds() * 20);

        clock.restart();
        lineArr = &line[0];
        window.clear(sf::Color::White);

        window.draw(lineArr, line.size(), sf::Lines);
        p1.draw(window);
        p2.draw(window);

        window.display();
    }

    return 0;
}