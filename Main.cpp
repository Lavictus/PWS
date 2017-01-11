// Made by Lavictus MB
// NHTV Programming Entry Assingment
// For additional information and sources see the "Read Me" file

//including Header Files -----------------------------------------------------------------------------------------------------------//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



// Main function -------------------------------------------------------------------------------------------------------------------//
int main()
{
	//Render Screen -------------------------------------------------------------------------------------------------------------------//
	const int ScreenWidth = 1300;
	const int ScreenHeigt = ScreenWidth / 1.5;

	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeigt), "Catch the Bomb", sf::Style::Close);

	//Create Background ------------------------------------------------------------------------------------------------------------//

	sf::Texture background;
	sf::Sprite Landscape;

	if (!background.loadFromFile("BackgroundBlue2.png"))
	{
		std::cout << "Could not load Background!" << std::endl;
	}

	Landscape.setTexture(background);

	// Set Font -----------------------------------------------------------------------------------------------------------------------//

	sf::Font font;
	if (!font.loadFromFile("Shadows of Security.ttf"))
	{
		std::cout << "Could not load Font!" << std::endl;
	}

	sf::Text text;
	text.setFont(font);
	text.setString("Catch The Bomb");
	text.setCharacterSize(150);
	text.setPosition(235, 250); 
	text.setOutlineThickness(1);
	text.setOutlineColor(sf::Color::Blue);

	sf::Text undertext;
	undertext.setFont(font);
	undertext.setString("By Lavictus");
	undertext.setCharacterSize(100);
	undertext.setPosition(450, 430);
	undertext.setOutlineThickness(1);
	undertext.setOutlineColor(sf::Color::Blue);

	
	
	
	// Game Loop ----------------------------------------------------------------------------------------------------------------------//
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

	//Draw Window ---------------------------------------------------------------------------------------------------------------------//
		window.clear();
		window.draw(Landscape);
		window.draw(text);
		window.draw(undertext);
		window.display();

	}


	//Return Exit Value ---------------------------------------------------------------------------------------------------------------//
	return 0;
}
