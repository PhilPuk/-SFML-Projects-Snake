#include "Game.h"

void Game::initWindow(sf::RenderWindow* window)
{
	this->window = window;

	this->winSize = this->window->getSize();
}

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

	this->playerhitfruit = false;
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
	this->fruit = new Fruit(this->winSize);
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
	this->initWindow(window);
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

	this->playerhitfruit = false;
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
		this->playerhitfruit = true;
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen() && !this->endGame)
	{
		this->update();

		this->render();
	}

	//If player loses show game over
	if (this->endGame_GameOver)
	{

		//Game Over text
		std::stringstream ssGameOver;
		ssGameOver << "You ate yourself!\nYour Score: " << this->score << "\nPress space to continue!\n";
		this->Text_GameOver.setString(ssGameOver.str());

		this->renderGameOver();
	}

	this->resetEndGame();

}

//Update
void Game::pollEvents()
{
	sf::Event ev;

	while (this->window->pollEvent(ev))
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
	if (this->playerhitfruit)
	{
		//Score
		std::stringstream ssScore;
		ssScore << "Score: " << this->score;
		this->Text_Score.setString(ssScore.str());

		this->playerhitfruit = false;
	}
}

void Game::update()
{
	this->pollEvents();

	//Player
	this->player->update(this->winSize, this->score);

	//Get Game over
	if (this->player->getHeadHitBody())
	{
		this->endGame_GameOver = true;
	}

	//Player fruit collision
	this->updatePlayerHeadFruitCollision();

	//Fruit
	this->fruit->update(this->winSize);

	//Bricks
	//this->bricks->update(window);

	// texts
	this->updateText();

	this->updateEndGame();


}

void Game::renderGameOver()
{

	this->window->draw(this->Text_GameOver);

	this->window->display();
	bool keypressed = false;
	while (!keypressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			keypressed = true;
		sf::sleep(sf::milliseconds(50));
	}
}

void Game::renderText()
{
	this->window->draw(this->Text_Score);
}

void Game::renderBackground()
{
	this->window->draw(this->Sprite_Background);
}

//Render
void Game::render()
{
	this->window->clear();

	//Background
	this->renderBackground();

	//Fruit
	this->fruit->render(*this->window);

	//Player
	this->player->render(*this->window);

	//Bricks
//	this->bricks->render(window);

	//Texts
	this->renderText();

	this->window->display();
}
