/**
 * @file button.cpp
 * @author Ekaterina Miller
 * @brief Implementation file for the Button class
 */
#include "button.h"

Button::Button() : Button("Push me!", {300.f, 100.f}, {200.f, 80.f}, sf::Color::White)
{
}

Button::Button(const std::string& s, sf::Vector2f position, sf::Vector2f size, sf::Color color)
        : mButton(mTexture),
          mButtonColor(color),
            mPosition(position),
            mBtnState(normal),
            mText(mFont)
{
    if (!mTexture.loadFromFile("button.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    // //create sprite that look like a button
    mButton.setTexture(mTexture, true);
    //get size of image
    sf::Vector2u imageSize=mTexture.getSize();
    // //change origin to the center of the image (makes rotation easy)
    mButton.setOrigin({imageSize.x/2.0f, imageSize.y/2.0f});
    //set position
    mButton.setPosition(mPosition);
    //choose color
    mButton.setColor(mButtonColor);
    // //set size as a ration of original size
    mButton.setScale({size.x/imageSize.x, size.y/imageSize.y});
  
    if (!mFont.openFromFile("VCR_OSD_MONO_1.001.ttf"))  
    {
        std::cout << "Error opening file\n";
        std::exit(2);
    }
    mText.setFont(mFont);

    mText.setString(s);
    mTextNormal = sf::Color::Green;
    mTextHover = sf::Color::Red;
    mText.setFillColor(mTextNormal);

    const auto bounds = mButton.getGlobalBounds();
    const unsigned int fontSize = static_cast<unsigned int>(bounds.size.y / 2.f);
    mText.setCharacterSize(fontSize);
    centerText();
}

void Button::centerText()
{
    const auto textBounds = mText.getGlobalBounds();
    mText.setOrigin({textBounds.size.x / 2.f, textBounds.size.y / 2.f});

    const auto buttonBounds = mButton.getGlobalBounds();
    const float fontSize = static_cast<float>(mText.getCharacterSize());
    mText.setPosition({mPosition.x, mPosition.y - fontSize / 4.f});
}

void Button::setPosition(sf::Vector2f position)
{
    mPosition = position;
    mButton.setPosition(mPosition);
    centerText();
}

void Button::setSize(sf::Vector2f size)
{
    sf::Vector2u imageSize=mTexture.getSize();
    mButton.setScale({size.x/imageSize.x, size.y/imageSize.y});

    const auto bounds = mButton.getGlobalBounds();
    const unsigned int fontSize = static_cast<unsigned int>(bounds.size.y / 2.f);
    mText.setCharacterSize(fontSize);
    centerText();
}

void Button::setColor(sf::Color btnColor)
{
    mButtonColor = btnColor;
    mButton.setColor(mButtonColor);
}

void Button::setText(const std::string& s)
{
    mText.setString(s);
    centerText();
}

bool Button::handleInput(const sf::Event& e, sf::RenderWindow& window)
{
    const sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    const sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixelPos);
    const bool mouseInButton = mButton.getGlobalBounds().contains(mousePosition);

    if (e.is<sf::Event::MouseMoved>())
    {
        mBtnState = mouseInButton ? hovered : normal;
    }

    if (const auto* mousePressed = e.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button == sf::Mouse::Button::Left)
        {
            if (mouseInButton)
            {
                mBtnState = clicked;
                return true;
            }
            mBtnState = normal;
        }
    }

    if (const auto* mouseReleased = e.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button == sf::Mouse::Button::Left)
        {
            mBtnState = mouseInButton ? hovered : normal;
        }
    }

    return false;
}

void Button::update()
{
    switch (mBtnState)
    {
    case normal:
        mButton.setRotation(sf::degrees(0.f));
        mText.setFillColor(mTextNormal);
        break;
    case hovered:
        mButton.setRotation(sf::degrees(0.f));
        mText.setFillColor(mTextHover);
        break;
    case clicked:
        mButton.setRotation(sf::degrees(180.f));
        mText.setFillColor(mTextHover);
        break;
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mButton, states);
    target.draw(mText, states);
}
