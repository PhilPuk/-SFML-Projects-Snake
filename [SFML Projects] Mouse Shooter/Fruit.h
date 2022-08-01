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
	void initVariables(sf::RenderWindow* window);
	void initTexture();
	void initShape(sf::RenderWindow* window);
public:
	//Constructor / Destructor
	Fruit(sf::RenderWindow* window);
	virtual ~Fruit();

	//Accessors
	const sf::FloatRect& getShapeBounds() const;
	const sf::Vector2f& getPos() const;
	//Modifiers
	void setFruitEaten(bool set);

	//Functions
	void CreateNewPos(sf::RenderWindow& window);
		//Update
	void update(sf::RenderWindow& window);
		//Render
	void renderFruit(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};

