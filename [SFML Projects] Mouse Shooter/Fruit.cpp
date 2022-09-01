#include "Fruit.h"

//Private functions
void Fruit::initVariables(sf::Vector2u winSize)
{

	//Fruit
	this->fruit_size = 50.f;

	int tmp_x = winSize.x / this->fruit_size;
	int tmp_y = winSize.y / this->fruit_size;

	this->Index_Texture_Fruit = 0;

	//Random Spawn in block system
	this->posX = static_cast<float>(rand() % tmp_x);
	this->posY = static_cast<float>(rand() % tmp_y);


	this->posX = this->posX * 50.f;
	this->posY = this->posY * 50;

	if (this->posX < 100.f)
		this->posX = 100.f;
	else if (this->posX > winSize.x - 100.f)
		this->posX = winSize.x - 100.f;

	if (this->posY < 100.f)
		this->posY = 100.f;
	else if (this->posY > winSize.y - 100.f)
		this->posY = winSize.y - 100.f;

	//Logic
	this->FruitEaten = false;
}

void Fruit::initTexture()
{
	if (!this->Texture_Fruit[0].loadFromFile("Textures/Fruit/fruit9.png"))
		std::cout << " - ERROR::FRUIT::INITTEXTURE::Couldn't load texture: fruit9.png!\n";

	if (!this->Texture_Fruit[1].loadFromFile("Textures/Fruit/fruit9.png"))
		std::cout << " - ERROR::FRUIT::INITTEXTURE::Couldn't load texture: fruit9.png!\n";

	if (!this->Texture_Fruit[2].loadFromFile("Textures/Fruit/fruit9.png"))
		std::cout << " - ERROR::FRUIT::INITTEXTURE::Couldn't load texture: fruit9.png!\n";

	if (!this->Texture_Fruit[3].loadFromFile("Textures/Fruit/fruit9.png"))
		std::cout << " - ERROR::FRUIT::INITTEXTURE::Couldn't load texture: fruit9.png!\n";

	if (!this->Texture_Fruit[4].loadFromFile("Textures/Fruit/fruit9.png"))
		std::cout << " - ERROR::FRUIT::INITTEXTURE::Couldn't load texture: fruit9.png!\n";
}

void Fruit::initShape()
{

	this->sprite_head.setFillColor(sf::Color(255, 255, 255, 255));
	this->sprite_head.setSize(sf::Vector2f(this->fruit_size, this->fruit_size));
	this->sprite_head.setPosition(this->posX, this->posY);

	this->sprite_head.setTexture(&this->Texture_Fruit[0]);
}

//Constructor / Destructor
Fruit::Fruit(sf::Vector2u winSize)
{
	this->initVariables(winSize);
	this->initTexture();
	this->initShape();
}

Fruit::~Fruit()
{
}

//Accessors
const sf::FloatRect& Fruit::getShapeBounds() const
{
	return this->sprite_head.getGlobalBounds();
}

const sf::Vector2f& Fruit::getPos() const
{
	return this->sprite_head.getPosition();
}

void Fruit::setFruitEaten(bool set)
{
	this->FruitEaten = set;
}

//Functions
void Fruit::CreateNewPos(sf::Vector2u winSize)
{
	if (this->FruitEaten)
	{
		//Random Spawn in block system
		int tmp_x = winSize.x / this->fruit_size;
		int tmp_y = winSize.y / this->fruit_size;

		this->posX = static_cast<float>(rand() % tmp_x);
		this->posY = static_cast<float>(rand() % tmp_y);

		this->posX = this->posX * 50.f;
		this->posY = this->posY * 50;

		if (this->posX < 100.f)
			this->posX = 100.f;
		else if (this->posX > winSize.x - 100.f)
			this->posX = winSize.x - 100.f;

		if (this->posY < 100.f)
			this->posY = 100.f;
		else if (this->posY > winSize.y - 100.f)
			this->posY = winSize.y - 100.f;

		//Reset bool
		this->FruitEaten = false;

		this->sprite_head.setPosition(this->posX, this->posY);

		this->Index_Texture_Fruit++;
		if (this->Index_Texture_Fruit >= 5)
			this->Index_Texture_Fruit = 0;
		this->sprite_head.setTexture(&this->Texture_Fruit[this->Index_Texture_Fruit]);
	}
}

//Update
void Fruit::update(sf::Vector2u winSize)
{
	//If bool eaten true create new fruit pos
	this->CreateNewPos(winSize);
}

//Render
void Fruit::renderFruit(sf::RenderTarget& target)
{
	target.draw(this->sprite_head);
}

void Fruit::render(sf::RenderTarget& target)
{
	this->renderFruit(target);
}
