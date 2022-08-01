#include "Game.h"

//Private functions
void Game::initVariables()
{
	//Logic
	this->endGame = false;
	this->endApplication = false;

	this->score = 0.f;

	//Timer
	this->Timer_RGBMAX = 2.f;
	this->Timer_RGB = this->Timer_RGBMAX;

	//Randomize color
	this->index_R = 1;
	this->index_G = 1;
	this->index_B = 1;
}

void Game::initFont(sf::Font* font)
{
	this->font = *font;
}

void Game::initTexts(sf::RenderWindow* window)
{
	//Score
	this->Text_Score.setFont(this->font);
	this->Text_Score.setCharacterSize(25);
	this->Text_Score.setPosition(sf::Vector2f(50.f, 10.f));
	this->Text_Score.setFillColor(sf::Color::White);
	this->Text_Score.setOutlineColor(sf::Color::Black);
	this->Text_Score.setOutlineThickness(5.f);

	//Game over
	this->Text_GameOver.setFont(this->font);
	this->Text_GameOver.setCharacterSize(35);
	this->Text_GameOver.setFillColor(sf::Color::White);
	this->Text_GameOver.setString("You ate yourself!\nYour Score: \nPress enter to continue!\n");
		//Centering
	sf::FloatRect rect = this->Text_GameOver.getLocalBounds();
	this->Text_GameOver.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
	this->Text_GameOver.setPosition(sf::Vector2f(static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2));
}

void Game::initPlayer(sf::RenderWindow* window)
{
	this->player = new Player(window);
}

void Game::initFruit(sf::RenderWindow* window)
{
	this->fruit = new Fruit(window);
}

/*
void Game::initBricks(sf::RenderWindow* window)
{
	this->bricks = new Bricks(window);
}
*/

void Game::initBackground(sf::Texture& background_texture)
{
	this->Texture_Background = background_texture;

	this->Sprite_Background.setTexture(this->Texture_Background);
	//this->Sprite_Background.scale(0.52083f, 0.6667f);
	this->Sprite_Background.setPosition(sf::Vector2f(0.f, 0.f));
}

//Constructor / Destructor
Game::Game(sf::RenderWindow* window, sf::Font& font, sf::Texture& background_texture)
{
	this->initVariables();
	this->initFont(&font);
	this->initTexts(window);
	this->initPlayer(window);
	this->initFruit(window);
	//this->initBricks(window);
	this->initBackground(background_texture);
}

Game::~Game()
{
	delete this->player;

	delete this->fruit;
}

//Accessors
const bool& Game::getEndApplication() const
{
	return this->endApplication;
}

const float& Game::getScore() const
{
	return this->score;
}

//Modifiers
void Game::resetEndGame()
{
	this->endGame = false;
	this->endGame_ESC = false;
	this->endGame_GameOver = false;
}

void Game::resetAllVariables(sf::RenderWindow* window)
{
	//Game class
		//Resets bool end game
	this->resetEndGame();
		//Reset score
	this->score = 0.f;

	this->player->resetVariablesAfterGameOver(window);

}

void Game::updatePlayerHeadFruitCollision()
{
	if (this->player->getPlayerBounds().contains(this->fruit->getPos()))
	{
		this->fruit->setFruitEaten(true);
		++this->score;

		//For debugging
		//std::cout << "Player collision with fruit!\n";
		//std::cout << this->score<<"\n";
	}
}

//Functions
void Game::run(sf::RenderWindow& window)
{
	while (window.isOpen() && !this->endGame)
	{
		this->update(window);

		this->render(window);
	}

	//If player loses show game over
	if (this->endGame_GameOver)
	{
		this->renderGameOver(window);
	}

	this->resetEndGame();

}

//Update
void Game::pollEvents(sf::RenderWindow& window)
{
	sf::Event ev;

	while (window.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->endApplication = true;
			this->endGame = true;
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->endGame = true;
			}
			break;
		}
	}
}

void Game::updateEndGame()
{
	if (this->endGame_ESC || this->endGame_GameOver)
		this->endGame = true;
}

void Game::updateText()
{
	//Randomize color
	if (this->Timer_RGB < this->Timer_RGBMAX)
	{
		this->Timer_RGB += 1.f;
	}
	else
	{
		this->Timer_RGB = 0.f;
		int addone = rand() % 30 + 1;
		int addtwo = rand() % 30 + 1;
		int addthree = rand() % 30 + 1;
		this->index_R += addone;
		this->index_G += addtwo;
		this->index_B += addthree;

		if (this->index_R > 255)
		{
			this->index_R = rand() % 255 + 1;
		}
		if (this->index_G > 255)
		{
			this->index_G = rand() % 255 + 1;
		}
		if (this->index_B > 255)
		{
			this->index_B = rand() % 255 + 1;
		}
	}
		this->Text_Score.setOutlineColor(sf::Color(this->index_R, this->index_G, this->index_B, 255));

	//Score
	std::stringstream ssScore;
	ssScore << "Score: " << this->score;
	this->Text_Score.setString(ssScore.str());

	//Game Over
	std::stringstream ssGameOver;
	ssGameOver << "You ate yourself!\nYour Score: " << this->score<<"\nPress space to continue!\n";
	this->Text_GameOver.setString(ssGameOver.str());
}

void Game::update(sf::RenderWindow& window)
{
	this->pollEvents(window);

	//Player
	this->player->update(window, this->score);

	//Get Game over
	if (this->player->getHeadHitBody())
	{
		this->endGame_GameOver = true;
	}

	//Player fruit collision
	this->updatePlayerHeadFruitCollision();

	//Fruit
	this->fruit->update(window);

	//Bricks
	//this->bricks->update(window);

	// texts
	this->updateText();

	this->updateEndGame();


}

void Game::renderGameOver(sf::RenderWindow& window)
{

	window.draw(this->Text_GameOver);

	window.display();
	bool keypressed = false;
	while (!keypressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			keypressed = true;
		sf::sleep(sf::milliseconds(50));
	}
}

void Game::renderText(sf::RenderWindow& window)
{
	window.draw(this->Text_Score);
}

void Game::renderBackground(sf::RenderWindow& window)
{
	window.draw(this->Sprite_Background);
}

//Render
void Game::render(sf::RenderWindow& window)
{
	window.clear();

	//Background
	this->renderBackground(window);

	//Fruit
	this->fruit->render(window);

	//Player
	this->player->render(window);

	//Bricks
//	this->bricks->render(window);

	//Texts
	this->renderText(window);



	window.display();
}
