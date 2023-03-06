#include <iostream>
#include <vector>

#include "Pendulum.hpp"


static sf::Color getRainbow(float t) {
    const float  PI = 3.14159265358979f;
    const float r = sin(t);
    const float g = sin(t + 0.33f * 2.0f * PI);
    const float b = sin(t + 0.66f * 2.0f * PI);
    return {static_cast<uint8_t>(255.0f * r * r),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(255.0f * b * b)};

}

int32_t main()
{

    constexpr int32_t WINDOW_WIDTH = 1000;
    constexpr int32_t WINDOW_HEIGHT = 1000;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Double Pendulum", sf::Style::Default, settings);

    Pendulum p1(500, 400, 100, 90, 220);
    Pendulum p2(&p1, 100, 90, 220);

    sf::Clock clock; 

    std::vector<sf::Vertex> trace_value;

    sf::Vertex* trace_array; 

    sf::Event event;

    while (window.isOpen())
    {
        // Hit escape to close the window
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
                
        }

        
        p2.update();

        trace_value.push_back(sf::Vertex(p2.updatePosition(clock.getElapsedTime().asSeconds() * 20), getRainbow(clock.getElapsedTime().asSeconds() * 20)));
        p1.updatePosition(clock.getElapsedTime().asSeconds() * 20);

        clock.restart();
        
        trace_array = &trace_value[0];
        window.clear(sf::Color::Black);

        window.draw(trace_array, trace_value.size(), sf::Lines);
        p1.draw(window);
        p2.draw(window);

        window.display();
    }

    return 0;
}