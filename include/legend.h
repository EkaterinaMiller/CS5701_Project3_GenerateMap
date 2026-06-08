#ifndef LEGEND_H
#define LEGEND_H
#include <vector>
#include <SFML/Graphics.hpp>

class Legend: public sf::Drawable
{
public:
    Legend(const std::array<sf::Color, 9> &palette, sf::Vector2f position, sf::Vector2f boxSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<sf::RectangleShape> mColorBoxes;
    sf::Vector2f mPosition;
    sf::Vector2f mBoxSize;
};

#endif // LEGEND_H