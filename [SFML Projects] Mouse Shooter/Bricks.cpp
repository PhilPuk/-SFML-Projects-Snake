#include "Bricks.h"


//Private functions
void Bricks::initVariables(sf::RenderWindow* window)
{
	this->Amount_Bricks_x = window->getSize().x / 50 * 2;
	this->Amount_Bricks_y = window->getSize().y / 50 * 2;
}

void Bricks::initTextures()
{
	if (!this->Texture_Bricks[0].loadFromFile("Textures/Brick/brick0.png"))
		std::cout << " - ERROR::BRICKS::INITTEXTURE::Couldn't load texture: brick0.png!\n";
}

void Bricks::initSprite(sf::RenderWindow* window)
{
	this->Sprite_brick.setTexture(this->Texture_Bricks[0]);
}

void Bricks::initAllBricks(sf::RenderWindow* window)
{
	float pos_X = 0.f;
	float pos_Y = 0.f;

	sf::Vector2u  winSize = window->getSize();

	for (int i = 0; i < this->Amount_Bricks_x + this->Amount_Bricks_y; i++)
	{
		this->bricks.push_back(new sf::Sprite(this->Sprite_brick));
	}
	std::cout << this->Amount_Bricks_x << "\n";
	std::cout << this->bricks.size();
	
	//TOP
	for (int i = 0; i  < this->Amount_Bricks_x / 2; i++)
	{
		this->bricks[i]->setPosition(pos_X, pos_Y);
		pos_X = pos_X + 50.f;
	}

	//BOTTOM
	pos_X = 0.f;
	pos_Y = winSize.y - 50.f;
	for (int i = this->Amount_Bricks_x / 2; i < this->Amount_Bricks_x; i++)
	{
		this->bricks[i]->setPosition(pos_X, pos_Y);
		pos_X = pos_X + 50.f;
	}

	//LEFT 
	pos_X = 0.f;
	pos_Y = 0.f;
	for (int i = this->Amount_Bricks_x; i < this->Amount_Bricks_x + this->Amount_Bricks_y / 2; i++)
	{
		this->bricks[i]->setPosition(pos_X, pos_Y);
		pos_Y = pos_Y + 50.f;
	}

	//RIGHT
	pos_X = winSize.x - 50.f;
	pos_Y = 0.f;
	for (int i = this->Amount_Bricks_x + this->Amount_Bricks_y / 2; i < this->Amount_Bricks_x + this->Amount_Bricks_y; i++)
	{
		this->bricks[i]->setPosition(pos_X, pos_Y);
		pos_Y = pos_Y + 50.f;
	}
}

//Constructor / Destructor
Bricks::Bricks(sf::RenderWindow* window)
{
	this->initVariables(window);
	this->initTextures();
	this->initSprite(window);
	this->initAllBricks(window);
}

Bricks::~Bricks()
{
	//Delete vector array
	for (int i = 0; i < this->bricks.size(); i++)
	{
		delete this->bricks[i];

		this->bricks.erase(this->bricks.begin(), this->bricks.end());
	}
}

//Functions
	//Update
void Bricks::updateBricks(sf::RenderWindow* window)
{

}

void Bricks::update(sf::RenderWindow* window)
{
}

//Render
void Bricks::renderBricks(sf::RenderWindow* window)
{
	for (int i = 0; i < this->bricks.size(); i++)
	{
		window->draw(*this->bricks[i]);
	}
}

void Bricks::render(sf::RenderWindow* window)
{
	this->renderBricks(window);
}
