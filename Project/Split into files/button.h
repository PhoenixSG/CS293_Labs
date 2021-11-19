#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

class Button
{
private:

	sf::RectangleShape button;
	sf::Text text;

	float btnWidth;
	float btnHeight;

public:
	Button();

	Button(std::string input_text, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor);

	void set_Text(std::string);

	void set_Size(sf::Vector2f);

	void set_Char_Size(int);

	void set_Font(sf::Font &fonts);

	void set_Back_Color(sf::Color color);

	void set_Text_Color(sf::Color color);

	void set_Position(sf::Vector2f point);

	void draw_To(sf::RenderWindow &window);

	// Check if the mouse is within the bounds of the button:
	bool is_Mouse_Over(sf::RenderWindow &window);
};