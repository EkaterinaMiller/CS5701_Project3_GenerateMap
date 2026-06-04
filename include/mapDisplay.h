#ifndef MAPDISPLAY_H
#define MAPDISPLAY_H 
#include <SFML/Graphics.hpp>
#include <vector>

class MapDisplay:public sf::Drawable
{ 
public:
    MapDisplay(sf::Vector2f position, sf::Vector2f size);
    void setTiles(const std::vector<std::vector<int>>& tileValues);
    void setPalette(const std::vector<sf::Color>& palette);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    ~MapDisplay(){};

private:
    void rebuildTiles();
    sf::Color colorForValue(int value) const;

    sf::RectangleShape mStartBoard;
    sf::Vector2f mPosition;
    sf::Vector2f mSize;
    std::vector<std::vector<int>> mTileValues;
    std::vector<sf::Color> mPalette;
    std::vector<sf::RectangleShape> mTiles;
};
#endif