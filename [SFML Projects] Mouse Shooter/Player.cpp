#include "Player.h"

//Private functions
void Player::initVariables()
{
	this->player_size = 50.f;

	//Player movement
	this->MoveSpeed_Player = this->player_size;

	this->TimerMoveMax = 15.f;
	this->TimerMove = this->TimerMoveMax;
	this->ProgressiveSpeed = 1.f;
	this->ProgressiveSpeed = 0.09f;

	this->last_movement.x = 0.f;
	this->last_movement.y = 0.f;

	this->score = 0.f;
	this->OldScore = 0.f;

	this->dirUP = false;
	this->dirDOWN = false;
	this->dirLEFT = false;
	this->dirRIGHT = false;

	//Logic
	this->HeadHitBody = false;

	//Head animation
	this->Head_Animation_Index = 0;

}

void Player::initShape(sf::RenderWindow* window)
{
	//this->sprite_head.setFillColor(sf::Color(255,255,255,255));
	//this->sprite_head.scale(sf::Vector2f(0.25f, 0.25f));
	this->sprite_head.setPosition(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2);
	this->last_pos.y = this->sprite_head.getPosition().y + 50.f;

	this->sprite_head.setTexture(this->Texture_Head[1]);
}

void Player::initTexture()
{
	//BODY
	if (!this->Texture_Body[0].loadFromFile("Textures/Body/body_0.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: body_0.png!\n";

	if (!this->Texture_Body[1].loadFromFile("Textures/Body/body_1.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: body_1.png!\n";

	/*
	if (!this->Texture_Body[2].loadFromFile("Textures/Body/body_2.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: body_2.png!\n";

	if (!this->Texture_Body[3].loadFromFile("Textures/Body/body_3.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: body_3.png!\n";
		*/

	//HEAD

	//UP
	if (!this->Texture_Head[0].loadFromFile("Textures/Head/head_open_up.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_open:up.png!\n";

	if (!this->Texture_Head[1].loadFromFile("Textures/Head/head_close_up.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_close_up.png!\n";

	//DOWN
	if (!this->Texture_Head[2].loadFromFile("Textures/Head/head_open_down.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_open_down.png!\n";

	if (!this->Texture_Head[3].loadFromFile("Textures/Head/head_close_down.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_close_down.png!\n";

	//LEFT
	if (!this->Texture_Head[4].loadFromFile("Textures/Head/head_open_left.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_open_left.png!\n";

	if (!this->Texture_Head[5].loadFromFile("Textures/Head/head_close_left.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_close_left.png!\n";

	//RIGHT
	if (!this->Texture_Head[6].loadFromFile("Textures/Head/head_open_right.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_open_right.png!\n";

	if (!this->Texture_Head[7].loadFromFile("Textures/Head/head_close_right.png"))
		std::cout << " - ERROR::PLAYER::INITTEXTURE::Couldn't load texture: head_close_right.png!\n";
}

//Constructor / Destructor
Player::Player(sf::RenderWindow* window)
{
	this->initVariables();
	this->initTexture();
	this->initShape(window);
}

Player::~Player()
{
	for (int i = 0; i < this->sprite_body.size(); i++)
	{
		delete this->sprite_body[i];
	}
}

const sf::FloatRect& Player::getPlayerBounds() const
{
	return this->sprite_head.getGlobalBounds();
}

const bool& Player::getHeadHitBody() const
{
	return this->HeadHitBody;
}

//Functions
void Player::resetVariablesAfterGameOver(sf::RenderWindow* window)
{
	this->dirUP = false;
	this->dirDOWN = false;
	this->dirLEFT = false;
	this->dirRIGHT = false;

	this->TimerMoveMax = 20.f;
	this->TimerMove = this->TimerMoveMax;
	this->ProgressiveSpeed = 1.f;

	this->last_movement.x = 0.f;
	this->last_movement.y = 0.f;

	this->score = 0.f;
	this->OldScore = 0.f;

	//Logic
	this->HeadHitBody = false;

	//Delete vector array
	for (int i = 0; i < this->sprite_body.size(); i++)
	{
		delete this->sprite_body[i];

		this->sprite_body.erase(this->sprite_body.begin(), this->sprite_body.end());
	}
}

void Player::updateScore(float& score)
{
	this->score = score;
}

void Player::updateProgressiveSpeed()
{
	this->ProgressiveSpeed = 1.f + (this->ProgressiveSpeedIncrease * this->score);
}

void Player::updateBodySize()
{
	if (this->OldScore != this->score)
	{
		this->OldScore = this->score;
		this->sprite_body.push_back(new sf::Sprite(this->sprite_head));
		this->sprite_body[this->score - 1]->setTexture(this->Texture_Body[0]);
		this->sprite_body[this->score - 1]->setColor(sf::Color(0, 0, 0, 0));
		this->sprite_body[this->score - 1]->setPosition(sf::Vector2f(this->sprite_body[this->score - 1]->getPosition().x, this->sprite_body[this->score - 1]->getPosition().y + 50.f));
	}
}

void Player::updatePlayerMovement()
{
	if (this->TimerMove <= this->TimerMoveMax)
	{
		this->TimerMove = this->TimerMove + this->ProgressiveSpeed;

		//UP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			this->dirUP = true;
			this->dirDOWN = false;
			this->dirLEFT = false;
			this->dirRIGHT = false;
		}
		//BOTTOM
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			this->dirUP = false;
			this->dirDOWN = true;
			this->dirLEFT = false;
			this->dirRIGHT = false;
		}
		//LEFT
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			this->dirUP = false;
			this->dirDOWN = false;
			this->dirLEFT = true;
			this->dirRIGHT = false;
		}
		//RIGHT
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			this->dirUP = false;
			this->dirDOWN = false;
			this->dirLEFT = false;
			this->dirRIGHT = true;
		}
	}
	else
	{
		//Reset timer
		this->TimerMove = 0.f;

		//Head animation
		if (this->Head_Animation_Index <= 1)
		{
			//OPEN
			this->Head_Animation_Index = 2;
		}
		else if (this->Head_Animation_Index >= 2)
		{
			//CLOSED
			this->Head_Animation_Index = 1;
		}

		//Body movement
		this->last_pos = this->sprite_head.getPosition();

		//UP
		if (this->dirUP)
		{
			//Head texture
			if (this->Head_Animation_Index == 1)
			{
				this->sprite_head.setTexture(this->Texture_Head[0]);
			}
			else
			{
				this->sprite_head.setTexture(this->Texture_Head[1]);
			}

			this->sprite_head.move(0.f, -this->MoveSpeed_Player);
			this->last_movement.x = 0.f;
			this->last_movement.y = -this->MoveSpeed_Player;
		}
		//BOTTOM
		else if (this->dirDOWN)
		{

			//Head texture
			if (this->Head_Animation_Index == 1)
			{
				this->sprite_head.setTexture(this->Texture_Head[2]);
			}
			else
			{
				this->sprite_head.setTexture(this->Texture_Head[3]);
			}

			this->sprite_head.move(0.f, this->MoveSpeed_Player);
			this->last_movement.x = 0.f;
			this->last_movement.y = this->MoveSpeed_Player;
		}
		//LEFT
		else if (this->dirLEFT)
		{

			//Head texture
			if (this->Head_Animation_Index == 1)
			{
				this->sprite_head.setTexture(this->Texture_Head[4]);
			}
			else
			{
				this->sprite_head.setTexture(this->Texture_Head[5]);
			}

			this->sprite_head.move(-this->MoveSpeed_Player, 0.f);
			this->last_movement.x = -this->MoveSpeed_Player;
			this->last_movement.y = 0.f;
		}
		//RIGHT
		else if (this->dirRIGHT)
		{
			//Head texture
			if (this->Head_Animation_Index == 1)
			{
				this->sprite_head.setTexture(this->Texture_Head[6]);
			}
			else
			{
				this->sprite_head.setTexture(this->Texture_Head[7]);
			}

			this->sprite_head.move(this->MoveSpeed_Player, 0.f);
			this->last_movement.x = this->MoveSpeed_Player;
			this->last_movement.y = 0.f;
		}
		else
		{
			this->sprite_head.move(this->last_movement);
		}
		//For debugging
		//std::cout << "Pos Shape X: " << this->sprite_head.getPosition().x << "	Y: " << this->sprite_head.getPosition().y<<"\n";
		this->updateBodyMovement();
	}
}

void Player::updatePlayerBodyCollision(int i)
{
		if (this->sprite_head.getGlobalBounds().contains(this->sprite_body[i]->getPosition().x + 5.f, this->sprite_body[i]->getPosition().y + 5.f))
		{
			this->HeadHitBody = true;
		}
}

void Player::updateBodyMovement()
{
	/*

	*/
	if (this->score > 0)
	{
		//Make new body part visible
		this->sprite_body[this->score - 1]->setColor(sf::Color(255, 255, 255, 255));

		//Temporary vectors to do the schieberegister
		sf::Vector2f tmpPos;
		sf::Vector2f tmpPos2;
		
		//Get body part 0 pos and set body part 0 pos to last head pos
		tmpPos = this->sprite_body[0]->getPosition();
		this->sprite_body[0]->setPosition(this->last_pos);

		//Schieberegister
			for (int i = 1; i < this->sprite_body.size(); i++)
			{
				tmpPos2 = this->sprite_body[i]->getPosition();
				this->sprite_body[i]->setPosition(tmpPos);
				//Brute force bug solution of invisible body part after instant double fruit pick up
				//this->sprite_body[i]->setColor(sf::Color(255, 255, 255, 255));
				tmpPos = tmpPos2;

				//Player body collision
				this->updatePlayerBodyCollision(i);
			}
	}

}

//Update
void Player::updateWindowCollision(sf::RenderWindow& window)
{
	/*
	* If player reaches one end of the screen
	* set him to the opposite side of the screen
	*/

	//TOP to bottom
	if (this->sprite_head.getGlobalBounds().top < 50.f)
	{
		this->sprite_head.setPosition(this->sprite_head.getPosition().x, window.getSize().y - this->player_size * 2);
	}
	//Bottom to top
	else if (this->sprite_head.getPosition().y + this->player_size * 2 > window.getSize().y)
	{
		this->sprite_head.setPosition(this->sprite_head.getPosition().x, 50.f);
	}

	//Left to right
	if (this->sprite_head.getPosition().x < 50.f)
	{
		this->sprite_head.setPosition(window.getSize().x - this->player_size * 2, this->sprite_head.getPosition().y);
	}
	//Right to left
	else if (this->sprite_head.getPosition().x + this->player_size * 2 > window.getSize().x)
	{
		this->sprite_head.setPosition(50.f, this->sprite_head.getPosition().y);
	}
}

void Player::update(sf::RenderWindow& window, float& score)
{
	this->updateScore(score);

	this->updateProgressiveSpeed();

	this->updateBodySize();

	this->updatePlayerMovement();

	this->updateWindowCollision(window);
}

//Render
void Player::renderPlayerBody(sf::RenderWindow& window)
{
	for (int i = 0; i < this->sprite_body.size(); i++)
	{
		window.draw(*this->sprite_body[i]);
	}
}

void Player::renderPlayerHead(sf::RenderWindow& window)
{
	window.draw(this->sprite_head);
}

void Player::render(sf::RenderWindow& window)
{
	this->renderPlayerHead(window);

	this->renderPlayerBody(window);


}
