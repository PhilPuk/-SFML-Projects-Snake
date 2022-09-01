#pragma once

#include<sstream>

#include"Player.h"
#include"Fruit.h"
//#include"Bricks.h"

//Change game over system completely
//it's a complete mess!
//Game over sequences
	//Game over by esc
		//Opens up a are you sure you want to go back
	//Game over by losing in game
		//Prints game over text with achieved score
		//Waits for enter to continuee

class Game
{
private:
	sf::RenderWindow* window;
	sf::Vector2u winSize;
	//Logic
	bool endGame;
	bool endApplication;
	bool endGame_GameOver;
	bool endGame_ESC;

	float score;

	//Background
	sf::Texture Texture_Background;
	sf::Sprite Sprite_Background;

	//Texts
	sf::Font font;
	sf::Text Text_Score;
	sf::Text Text_GameOver;

	//RGB
	int index_R;
	int index_G;
	int index_B;

	float Timer_RGBMAX;
	float Timer_RGB;

	//Player
	Player* player;

	//Fruit
	Fruit* fruit;
	bool playerhitfruit;

	//Bricks
//	Bricks* bricks;

	//Private functions
	void initWindow(sf::RenderWindow* window);
	void initVariables();
	void initFont(sf::Font* font);
	void initTexts(sf::RenderWindow* window);
	void initPlayer(sf::RenderWindow* window);
	void initFruit(sf::RenderWindow* window);
//	void initBricks(sf::RenderWindow* window);
	void initBackground(sf::Texture& background_texture);
public:
	//Constructor / Destructor
	Game(sf::RenderWindow* window, sf::Font& font, sf::Texture& background_texture);
	virtual ~Game();

	//Accessors
	const bool& getEndApplication() const;
	const float& getScore() const;
	//Modifiers
	void resetEndGame();

	//Functions
		//Game over
	void resetAllVariables(sf::RenderWindow* window);
		//Main Loop
	void run();
		//Update
	void pollEvents();
	void updatePlayerHeadFruitCollision();
	void updateEndGame();
	void updateText();
	void update();
		//Render
	void renderGameOver();
	void renderText();
	void renderBackground();
	void render();
};

