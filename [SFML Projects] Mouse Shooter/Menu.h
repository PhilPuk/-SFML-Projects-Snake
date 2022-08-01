#pragma once

#include<iostream>
#include<string>
#include<fstream>

#include"Mouse.h"
#include"Game.h"

class Menu
{
private:
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	std::string Application_Title;
	int Framerate;

	//Fonts
	sf::Font font;

	//Texts
	sf::Text Text_Title;
	sf::Text Text_Menu_Options[3];
	sf::Color Color_Menu;
	sf::Vector2f Vector_Menu_Pos;
	float Spacing_Menu_Pos_Y;

		//Highscore
	sf::Text Text_Highscore;
	float Highscore;

	//Creator Text
	sf::Text Text_Creator;

	int index_R;
	int index_G;
	int index_B;

	float Timer_RGBMAX;
	float Timer_RGB;

	//Menu_Navigation
	short Menu_Navigation_Index;
	bool Navigation_Index_Changed;

	//Game
	Game* game;

	//Background
	sf::Texture Texture_Background;
	sf::Sprite Sprite_Background;

	//Private functions
	void getHighscoreFromTXT();
	void saveHighscoreInTXT();
		//Menu_Navigation
	void navigateUP();
	void navigateDOWN();
	 
		//Initilalization
	void initVariables();
	void initWindow();
	void initBackground();
	void initFonts();
	void initText();
	void initGame();

	//Mouse
	Mouse mouse;
public:
	//Constructor / Destructor
	Menu();
	~Menu();

	//Functions
	void run();
	void pollEvents();
		//update
	void updateText();
	void udpate();
		//render
	void renderText();
	void renderBackground();
	void render();
};

