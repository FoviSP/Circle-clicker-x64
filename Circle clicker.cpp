#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

sf::RenderWindow window(sf::VideoMode(400, 400), "Circle clicker!");

class ClickableCircle : public sf::CircleShape {
public:
	bool click(const sf::Vector2i& mouse_pos) const {
		return getGlobalBounds().contains(mouse_pos.x, mouse_pos.y);
	}
};

ClickableCircle shape;
sf::Text text;
sf::Font f;
sf::Color bgcolor = sf::Color::Black;

int clicks = 0;

int random2() {
	return 2 + (rand() % 300);
}

void draw() {
	int r = 1 + (rand() % 200);
	shape.setRadius(r);
	shape.setPosition(random2() - r, random2() - r);
	text.rotate(random2());
	text.setPosition(random2(), random2());
	text.setString(std::to_string(clicks));
}

int main(){
	if (!f.loadFromFile("arial.ttf"))
	{
		std::cout << "Can't load font" << std::endl;
	}
	else {
		std::cout << "Font loaded" << std::endl;
	}
	text.setFont(f);
	text.setFillColor(sf::Color::Black);
	text.setOutlineThickness(2);
	text.setOutlineColor(sf::Color::White);
	text.setCharacterSize(44);
	std::cout << "\n\nCircle clicker! Version 0.02 by Leksiyko \nJust clicking!\n\n" << std::endl;
	draw();
	while (window.isOpen())
	{		sf::Event event;
		while (window.pollEvent(event))
		{
			window.clear();
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (!shape.click(sf::Mouse::getPosition(window))) {
					bgcolor = sf::Color(60,0,0);
					text.setString(std::to_string(--clicks));
					text.setFillColor(sf::Color::Red);
					break;
				}
				text.setFillColor(sf::Color::Green);
				bgcolor = sf::Color(0, 60, 0);
				std::cout << "Click! " << ++clicks << std::endl;
				draw();
				break;
			}
			
		}
		window.clear(bgcolor);
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	return 0;
}