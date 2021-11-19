#ifndef BUTTON
#define BUTTON

#include <iostream>
#include <SFML/Graphics.hpp>

#include "button.h"

Button::Button() {

}

Button::Button(std::string input_text, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
	button.setSize(buttonSize);
	button.setFillColor(bgColor);

	// Get these for later use:
	btnWidth = buttonSize.x;
	btnHeight = buttonSize.y;

	text.setString(input_text);
	text.setCharacterSize(30);
	text.setFillColor(textColor);
}

void Button::set_Text(std::string t) {
	text.setString(t);
}

void Button::set_Size(sf::Vector2f s) {
	button.setSize(s);
}

void Button::set_Char_Size(int c) {
	text.setCharacterSize(c);
}

void Button::set_Font(sf::Font &fonts) {
	text.setFont(fonts);
}

void Button::set_Back_Color(sf::Color color) {
	button.setFillColor(color);
}

void Button::set_Text_Color(sf::Color color) {
	text.setFillColor(color);
}

void Button::set_Position(sf::Vector2f point) {
	button.setPosition(point);

	float xPos = (point.x + btnWidth/2) - (text.getLocalBounds().width / 2);
	float yPos = (point.y + btnHeight/2) - (text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

void Button::draw_To(sf::RenderWindow &window) {
	window.draw(button);
	window.draw(text);
}

// Check if the mouse is within the bounds of the button:
bool Button::is_Mouse_Over(sf::RenderWindow &window) {
	sf::Vector2i mouseCoords({ sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y });

	sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

	float mouseX = realCoords.x;
	float mouseY = realCoords.y;

	int btnPosX = button.getPosition().x;
	int btnPosY = button.getPosition().y;

	int btnxPosWidth = button.getPosition().x + button.getGlobalBounds().width;
	int btnyPosHeight = button.getPosition().y + button.getGlobalBounds().height;

	if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
		return true;
	}
	return false;
}

#endif