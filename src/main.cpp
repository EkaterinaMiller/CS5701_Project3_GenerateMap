#include <SFML/Graphics.hpp>
#include <iostream>
#include "bulletList.h"

int main() {
    // SFML 3 uses sf::VideoMode::getDesktopMode() or explicit sf::Vector2u for sizing
    auto window = sf::RenderWindow(sf::VideoMode({1200, 800}), "SFML 3.1 works!");
    window.setFramerateLimit(60);

    sf::RectangleShape startBoard({500, 500});
    startBoard.setPosition({50,30});
    sf::RectangleShape finalBoard({500, 500});
    finalBoard.setPosition({650,30});
    sf::Font font;
    if (!font.openFromFile("VCR_OSD_MONO_1.001.ttf"))
    {
        std::cerr << "Error opening font file\n";
        exit(1);
    }
    BulletList size({50, 550}, font, "Size", {"Small", "Medium", "Large"});
    BulletList terrain({650, 550}, font, "Terrain", {"Grass", "Sand", "Water"});



    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(startBoard);
        window.draw(finalBoard);
        window.draw(size);
        window.draw(terrain);
        window.display();
    }
}