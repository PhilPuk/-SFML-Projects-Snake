#pragma once

#include<iostream>
#include<vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

enum dir { UP = 0, DOWN, LEFT, RIGHT};

class Player
{
private:
	//Player head
	sf::Sprite sprite_head;
	float player_size;
	sf::Texture Texture_Head[8];

		//Animation
	int Head_Animation_Index;

	//Snake body
	std::vector<sf::Sprite*> sprite_body;
	float score;
	float OldScore;
	sf::Texture Texture_Body[2];

	//Logic
	bool HeadHitBody;

	//Player Movement
	float MoveSpeed_Player;
	float TimerMoveMax;
	float TimerMove;
	float ProgressiveSpeed;
	float ProgressiveSpeedIncrease;
	sf::Vector2f last_movement;
	sf::Vector2f last_pos;
	bool dirUP;
	bool dirDOWN;
	bool dirLEFT;
	bool dirRIGHT;

	//Private functions
	void initVariables();
	void initShape(sf::RenderWindow* window);
	void initTexture();
public:
	//Constructor / Destructor
	Player(sf::RenderWindow* window);
	virtual ~Player();

	//Accessors
	const sf::FloatRect& getPlayerBounds() const;
	const bool& getHeadHitBody() const;
	//Modifiers

	//Functions
	void resetVariablesAfterGameOver(sf::RenderWindow* window);
		//Update
	void updateScore(float& score);
	void updateProgressiveSpeed();
	void updateBodySize();
	void updatePlayerMovement();
	void updatePlayerBodyCollision(int i);
	void updateBodyMovement();
	void updateWindowCollision(sf::RenderWindow& window);
	void update(sf::RenderWindow& window, float& score);
		//Render
	void renderPlayerBody(sf::RenderWindow& window);
	void renderPlayerHead(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
};

