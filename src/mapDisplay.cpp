#include "mapDisplay.h"
#include <algorithm>

MapDisplay::MapDisplay(sf::Vector2f position, sf::Vector2f size)
    : mPosition(position),
      mSize(size),
      mPalette({
          sf::Color::Blue,                 // 0
          sf::Color::Yellow,               // 1
          sf::Color(40, 170, 70),          // 2
          sf::Color(20, 110, 20),          // 3
          sf::Color(130, 130, 130),        // 4
          sf::Color(220, 220, 220)         // 5
      })
{
    mStartBoard.setPosition(mPosition);
    mStartBoard.setSize(mSize);
    mStartBoard.setFillColor(sf::Color::Black);
    mStartBoard.setOutlineThickness(1.f);
    mStartBoard.setOutlineColor(sf::Color(90, 90, 90));
}

void MapDisplay::setTiles(const std::vector<std::vector<int>>& tileValues)
{
    mTileValues = tileValues;
    rebuildTiles();
}

void MapDisplay::setPalette(const std::vector<sf::Color>& palette)
{
    if (!palette.empty())
    {
        mPalette = palette;
        rebuildTiles();
    }
}

sf::Color MapDisplay::colorForValue(int value) const
{
    if (value < 0 || mPalette.empty())
    {
        return sf::Color::Magenta;
    }

    const std::size_t index = static_cast<std::size_t>(value);
    if (index < mPalette.size())
    {
        return mPalette[index];
    }

    return sf::Color::Magenta;
}

void MapDisplay::rebuildTiles()
{
    mTiles.clear();
    if (mTileValues.empty() || mTileValues.front().empty())
    {
        return;
    }

    const std::size_t rows = mTileValues.size();
    std::size_t cols = 0;
    for (const auto& row : mTileValues)
    {
        cols = std::max(cols, row.size());
    }

    if (cols == 0)
    {
        return;
    }

    const float tileWidth = mSize.x / static_cast<float>(cols);
    const float tileHeight = mSize.y / static_cast<float>(rows);

    for (std::size_t r = 0; r < rows; ++r)
    {
        for (std::size_t c = 0; c < mTileValues[r].size(); ++c)
        {
            sf::RectangleShape tile({tileWidth, tileHeight});
            tile.setPosition({
                mPosition.x + static_cast<float>(c) * tileWidth,
                mPosition.y + static_cast<float>(r) * tileHeight
            });
            tile.setFillColor(colorForValue(mTileValues[r][c]));
            tile.setOutlineThickness(0.5f);
            tile.setOutlineColor(sf::Color(25, 25, 25));
            mTiles.push_back(tile);
        }
    }
}

void MapDisplay::update()
{
    // Update logic for the map display can be added here if needed
}

void MapDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mStartBoard, states);
    for (const auto& tile : mTiles)
    {
        target.draw(tile, states);
    }
}

