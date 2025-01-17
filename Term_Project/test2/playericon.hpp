#ifndef ICON_HPP
#define ICON_HPP

#include "DrawableObject.hpp"
#include "Game.hpp"

class PlayerIcon : public DrawableObject {

private:


	sf::Texture texture = DrawableObject::getTexture();
	sf::Sprite sprite = DrawableObject::getSprite();
	int positionIndex;

public:

	sf::Sprite getSprite() { return sprite; }
	int getPositionIndex() { return positionIndex; }

	
	PlayerIcon(sf::RenderWindow& WindowRef, std::string number,int xPosition,int yPosition) {
		texture.loadFromFile("images/Piece" + number + ".png");
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setPosition(xPosition, yPosition);
	}



};

#endif