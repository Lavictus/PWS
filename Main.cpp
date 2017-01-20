// Made by Mark Baaij
// NHTV Programming Entry Assingment
// For additional information and sources see the "Read Me" file

//including Header Files -----------------------------------------------------------------------------------------------------------//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>


// Main function -------------------------------------------------------------------------------------------------------------------//
int main()
{
	//Seed random number generator
	std::srand(static_cast<unsigned int>(std::time(0)));

	//Define constants -------------------------------------------------------------------------------------------------------------------//
	const int ScreenWidth = 1300;
	const int ScreenHeight = ScreenWidth / 1.5;
	sf::Vector2f trashcanSize(100, 130);
	float bombRadius = 35.f;
	const float trashcanspeed = 850.f;
	const float bombSpeed = 550.f;
	float bombAngle = 0.f;
	const float pi = 3.14159265359;
	
	

	



	//Render screen for the game
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;
	
	sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Catch the Bomb", sf::Style::Close, settings);


	sf::SoundBuffer explosionBuffer;
		if(!explosionBuffer.loadFromFile("Boom.wav"))
		{
			std::cout << "Could not load Explosion sound!" << std::endl;
		}
		sf::Sound explosion(explosionBuffer);
		explosion.setVolume(30);



	//Create the Trashcan
	
	sf::ConvexShape trashcan;

	trashcan.setPointCount(4);

	trashcan.setPoint(0, sf::Vector2f(0, 0));
	trashcan.setPoint(1, sf::Vector2f(100, 0));
	trashcan.setPoint(2, sf::Vector2f(80, 130));
	trashcan.setPoint(3, sf::Vector2f(20, 130));

	trashcan.setOutlineThickness(5);
	trashcan.setOutlineColor(sf::Color::Black);
	trashcan.setFillColor(sf::Color(70, 70, 70));
	trashcan.setOrigin(trashcanSize / 2.f);

	


	//Create a Bomb

	sf::CircleShape bomb;

	bomb.setRadius(bombRadius-5);
	bomb.setOutlineThickness(5);
	bomb.setOutlineColor(sf::Color::Red);
	bomb.setFillColor(sf::Color::Black);
	



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
	if (!font.loadFromFile("technott.ttf"))
	{
		std::cout << "Could not load Font!" << std::endl;
	}

	

	sf::Text headline;
	headline.setFont(font);
	headline.setString("Catch The Bomb");
	headline.setCharacterSize(120);
	headline.setPosition(160, 260);
	headline.setOutlineThickness(1);
	headline.setOutlineColor(sf::Color::Black);

	sf::Text undertext;
	undertext.setFont(font);
	undertext.setString("By Lavictus");
	undertext.setCharacterSize(70);
	undertext.setPosition(440, 400);
	undertext.setOutlineThickness(1);
	undertext.setOutlineColor(sf::Color::Black);


	sf::Text options;
	options.setFont(font);
	options.setString("Press Space or Enter to play\nPress Escape to quit");
	options.setCharacterSize(40);
	options.setPosition(50, 750);
	options.setOutlineThickness(1);
	options.setOutlineColor(sf::Color::Black);

	

	sf::Text score;
	score.setFont(font);
	score.setCharacterSize(50);
	score.setOutlineThickness(1);
	score.setOutlineColor(sf::Color::Black);

	

	






	// Game Loop ----------------------------------------------------------------------------------------------------------------------//
	int playerScore = 0;
	float speedUp = 1;
	sf::Clock gameClock;
	bool isPlaying = false;
	bool about = false;
	while (window.isOpen())
	{
		sf::Event game;
		while (window.pollEvent(game))
		{
			
			//Stop when window is closed or if escape is pressed
			if ((game.type == sf::Event::Closed) ||		
				((game.key.code == sf::Keyboard::Escape)))
			{
				window.close();
				break;
			}

		}



		//Play game when enter or space is pressed
		if ((game.key.code == sf::Keyboard::Space) || (game.key.code == sf::Keyboard::Return))
		{

			if (!isPlaying)
			{
				isPlaying = true;
				gameClock.restart();
				trashcan.setPosition(ScreenWidth / 2 + 25, 800);
				bomb.setPosition(2.f + (std::rand() % ScreenWidth - 2.f), -bombRadius*2);
				
				bombAngle = std::rand() % 360 * 2 * pi/360 ;
				playerScore = 0;
				speedUp = 1;

				
			}

			

		}

		if (isPlaying)
		{
			
			float deltaTime = gameClock.restart().asSeconds();


			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ((trashcan.getPosition().x) + trashcanSize.x / 2 < ScreenWidth + 50.f )))
			{
				trashcan.move(trashcanspeed * speedUp * deltaTime , 0.f);
			}

			if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && ((trashcan.getPosition().x) - trashcanSize.x / 2 > 1.f)))
			{
				trashcan.move(-trashcanspeed * speedUp * deltaTime , 0.f);
			}

			float factor = bombSpeed * speedUp * deltaTime ;
			bomb.move(std::sin(bombAngle) * factor, 1 * factor);



			if (bomb.getPosition().x < 0.f)
			{
				bombAngle = -bombAngle;
				bomb.setPosition( 0.01f, bomb.getPosition().y);
			}

			if (bomb.getPosition().x + bombRadius > ScreenWidth)
			{
				bombAngle = -bombAngle;
				bomb.setPosition(ScreenWidth - bombRadius - 0.01f, bomb.getPosition().y);
			}

			if (bomb.getPosition().y + bombRadius > ScreenHeight)
			{
				isPlaying = false;
				explosion.play();
				headline.setString("  You blew up ");
				headline.setOutlineColor(sf::Color::Red);
				
				undertext.setOutlineColor(sf::Color::Red);
				options.setString("Press Space or Enter to play again\nPress Escape to quit");

			}
			
			if (bomb.getPosition().x + bombRadius - 5.f> trashcan.getPosition().x - trashcanSize.x / 2 &&
				bomb.getPosition().x + bombRadius - 5.f< trashcan.getPosition().x + trashcanSize.x / 2  &&
				bomb.getPosition().y + bombRadius -10.f>= trashcan.getPosition().y - trashcanSize.y / 2 &&
				bomb.getPosition().y  <= trashcan.getPosition().y - trashcanSize.y / 2 + 20)
			{
				bomb.setPosition(2.f + (std::rand() % ScreenWidth - 2.f), -bombRadius * 2);
				bombAngle = std::rand() % 360 * 2 * pi / 360;
				
				++playerScore;
				
				speedUp += 0.005;


				std::ostringstream oss;
				oss << "Score: " << playerScore;
				score.setString(oss.str());
				score.setPosition(ScreenWidth - 300, 100);
				undertext.setString(oss.str());



				

			}

		


			


		}



	

	//Draw Window ---------------------------------------------------------------------------------------------------------------------//
	window.clear();
	window.draw(Landscape);


	if (isPlaying)
	{
		window.draw(bomb);
		window.draw(trashcan);
		window.draw(score);
		
	}



	else
	{
		window.draw(headline);
		window.draw(undertext);
		window.draw(options);
	}


	window.display();

}


	//Return Exit Value ---------------------------------------------------------------------------------------------------------------//
	return 0;
}
