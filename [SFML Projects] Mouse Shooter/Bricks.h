#pragma once

#include<iostream>
#include<vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Bricks
{
private:
	//Textures
	sf::Texture Texture_Bricks[1];
	int Amount_Bricks_x;
	int Amount_Bricks_y;
	//Bricks
	sf::Sprite Sprite_brick;
	std::vector<sf::Sprite*> bricks;

	//Private functions
	void initVariables(sf::RenderWindow* window);
	void initTextures();
	void initSprite(sf::RenderWindow* window);
	void initAllBricks(sf::RenderWindow* window);
public:
	//Constructor / Destructor
	Bricks(sf::RenderWindow* window);
	virtual ~Bricks();

	//Functions
		//Update
	void updateBricks(sf::RenderWindow* window);
	void update(sf::RenderWindow* window);
		//Render
	void renderBricks(sf::RenderWindow* window);
	void render(sf::RenderWindow* window);
};

