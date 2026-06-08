#include "legend.h"
Legend::Legend(const std::array<sf::Color, 9> &palette, sf::Vector2f position, sf::Vector2f boxSize)
    : mPosition(position), mBoxSize(boxSize)
{
    for (size_t i{1}; i<palette.size(); ++i){
        sf::RectangleShape colorBox(mBoxSize);
        colorBox.setFillColor(palette[i]);
        colorBox.setPosition({mPosition.x, mPosition.y + (i-1) * (mBoxSize.y+20)});
        mColorBoxes.push_back(colorBox);
    }
}
void Legend::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& box : mColorBoxes) {
        target.draw(box, states);
    }
}
