#pragma once

#include<iostream>
#include<vector>
#include<time.h>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Fruit
{
private:
	//Fruit
	sf::RectangleShape sprite_head;
	float fruit_size;
	sf::Texture Texture_Fruit[5];
	int Index_Texture_Fruit;
	float posX;
	float posY;

	//Logic
	bool FruitEaten;

	//Private functions
	void initVariables(sf::Vector2u winSize);
	void initTexture();
	void initShape();
public:
	//Constructor / Destructor
	Fruit(sf::Vector2u winSize);
	virtual ~Fruit();

	//Accessors
	const sf::FloatRect& getShapeBounds() const;
	const sf::Vector2f& getPos() const;
	//Modifiers
	void setFruitEaten(bool set);

	//Functions
	void CreateNewPos(sf::Vector2u winSize);
		//Update
	void update(sf::Vector2u winSize);
		//Render
	void renderFruit(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

