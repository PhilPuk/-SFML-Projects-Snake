#include "Menu.h"

//Private functions
	//Initialization
void Menu::initVariables()
{
	//Window
		//Screen size
	this->videoMode.width = 1000;
	this->videoMode.height = 800;
		//Framerate
	this->Framerate = 30;

	//Texts
		//Text Title
	this->Application_Title = "We Snake GYM";
		//Text Colors
	this->Color_Menu = sf::Color::White;
		//Text Pos
	this->Vector_Menu_Pos.x = 105.f;
	this->Vector_Menu_Pos.y = 500.f;
		//Text spacing
	this->Spacing_Menu_Pos_Y = 50.f;

	//Menu navigation
	this->Menu_Navigation_Index = 0;
	this->Navigation_Index_Changed = false;

	//Randomize color
	this->index_R = 1;
	this->index_G = 1;
	this->index_B = 1;

	//Timer
	this->Timer_RGBMAX = 2.f;
	this->Timer_RGB = this->Timer_RGBMAX;
}

void Menu::initWindow()
{
	this->window = new sf::RenderWindow(this->videoMode, this->Application_Title, sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(this->Framerate);
}

void Menu::initBackground()
{
	if (!this->Texture_Background.loadFromFile("Textures/background/background3.jpg"))
		std::cout << " - ERROR::GAME::INITBACKGROUND::Couldn't load texture: wood.jpg";

	this->Sprite_Background.setTexture(this->Texture_Background);
	//this->Sprite_Background.scale(0.52083f, 0.6667f);
	this->Sprite_Background.setPosition(sf::Vector2f(0.f, 0.f));
}

void Menu::initFonts()
{
	//Initialize all fonts
	if (!this->font.loadFromFile("Fonts/Starborn.ttf"))
		std::cout << " - ERROR::MENU::INITFONTS:: Couldn't load font!\n";
}

void Menu::initText()
{
	//sets all texts content
		//Title
	this->Text_Title.setString(this->Application_Title);
		//Start
	this->Text_Menu_Options[0].setString("Start");
		//Options
	this->Text_Menu_Options[1].setString("Settings");
		//Stop
	this->Text_Menu_Options[2].setString("Stop");

	//sets all texts settings
		//Title
	this->Text_Title.setFont(this->font);
	this->Text_Title.setCharacterSize(54);
	this->Text_Title.setFillColor(this->Color_Menu);
	this->Text_Title.setPosition(this->Vector_Menu_Pos.x, this->Vector_Menu_Pos.y - this->Spacing_Menu_Pos_Y * 2.f);
	this->Text_Title.setOutlineColor(sf::Color::Black);
	this->Text_Title.setOutlineThickness(5.f);
		//Menu_Options
	sf::Vector2f tmp_saveVector = this->Vector_Menu_Pos;
	for (int i = 0; i < 3; i++)
	{
		this->Text_Menu_Options[i].setFont(this->font);
		this->Text_Menu_Options[i].setCharacterSize(34);
		this->Text_Menu_Options[i].setFillColor(this->Color_Menu);
		this->Text_Menu_Options[i].setPosition(this->Vector_Menu_Pos);
		this->Text_Menu_Options[i].setOutlineColor(sf::Color::Black);
		this->Text_Menu_Options[i].setOutlineThickness(5.f);
		//Increase spacing for each text
		this->Vector_Menu_Pos.y = this->Vector_Menu_Pos.y + this->Spacing_Menu_Pos_Y;
	}
	//Reset vector
	this->Vector_Menu_Pos = tmp_saveVector;

	//Highscore
	this->Text_Highscore = this->Text_Title;
	this->Text_Highscore.setCharacterSize(34);
	this->Text_Highscore.setPosition(this->Vector_Menu_Pos.x + 200.f, this->Vector_Menu_Pos.y);
	this->Text_Highscore.setOutlineColor(sf::Color::Black);
	this->Text_Highscore.setOutlineThickness(5.f);

	//Creator
	this->Text_Creator = this->Text_Highscore;
	this->Text_Creator.setString("By phil_puk");
	this->Text_Creator.setPosition(this->videoMode.width - this->Text_Creator.getGlobalBounds().width - 50.f, this->videoMode.height - this->Text_Creator.getGlobalBounds().height);
	this->Text_Creator.setOutlineColor(sf::Color::Black);
	this->Text_Creator.setOutlineThickness(5.f);

	//Sets first option to Navigation Index Color
	this->Text_Menu_Options[this->Menu_Navigation_Index].setFillColor(sf::Color::Magenta);
}

void Menu::initGame()
{
	this->game = new Game(this->window, this->font, this->Texture_Background);
}

void Menu::getHighscoreFromTXT()
{
	std::ifstream in("Highscore.txt");
	std::string line;
	while (std::getline(in, line))
	{
		this->Highscore = std::stof(line);
	}
	in.close();
	//std::cout << this->Highscore;
}

void Menu::saveHighscoreInTXT()
{
	std::ofstream of;
	of.open("Highscore.txt");

	of << this->Highscore;

	of.close();
}

//Menu_Navigation
void Menu::navigateUP()
{
	if (this->Menu_Navigation_Index > 0)
	{
		this->Menu_Navigation_Index--;
		this->Navigation_Index_Changed = true;
	}
}

void Menu::navigateDOWN()
{
	if (this->Menu_Navigation_Index < 2)
	{
		this->Menu_Navigation_Index++;
		this->Navigation_Index_Changed = true;
	}
}


//Constructor / Destructor
Menu::Menu()
{
	//Get highscores
	this->getHighscoreFromTXT();

	//Call all functions that need to be initialized
	this->initVariables();
	this->initWindow();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initGame();
}

Menu::~Menu()
{
	delete this->window;

	this->saveHighscoreInTXT();

	delete this->game;
}

//Functions
void Menu::run()
{
	//Main loop for whole application
	while (this->window->isOpen())
	{

		this->udpate();

		this->render();
	}
}

void Menu::pollEvents()
{
	sf::Event ev;
	//Main loop for event polling
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		//Closing Event
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
				//Esc to close
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			
			//Menu_Options function called here
			if (ev.key.code == sf::Keyboard::Enter)
			{
				if (this->Menu_Navigation_Index == 0)
				{
					//Start button action
					this->game->run(*this->window);

					if (this->game->getScore() > this->Highscore)
						this->Highscore = this->game->getScore();

					this->game->resetAllVariables(this->window);
				}
				else if (this->Menu_Navigation_Index == 1)
				{
					//Settings button action
				}
				else if (this->Menu_Navigation_Index == 2)
				{
					//Stop button action
					this->window->close();
				}
			}

			//Menu Navigation Event
			if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Up)
				this->navigateUP();
			else if (ev.key.code == sf::Keyboard::S || ev.key.code == sf::Keyboard::Down)
				this->navigateDOWN();
			break;
		}
	}
}

//update
void Menu::updateText()
{
	//Randomize color
	if (this->Timer_RGB < this->Timer_RGBMAX)
	{
		this->Timer_RGB += 1.f;
	}
	else
	{
		this->Timer_RGB = 0.f;

		float addone = rand() % 30 + 1;
		float addtwo = rand() % 30 + 1;
		float addthree = rand() % 30 + 1;
		this->index_R += addone;
		this->index_G += addtwo;
		this->index_B += addthree;

		if (this->index_R > 255)
		{
			this->index_R = rand() % 255 +1;
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

	//RGB Title
	this->Text_Title.setOutlineColor(sf::Color(this->index_R, this->index_G, this->index_B, 255));

	//Changes color of currently selected option 
	//Resets other to standart color

		for (int i = 0; i < 3; i++)
		{
			if (i == this->Menu_Navigation_Index)
				this->Text_Menu_Options[i].setFillColor(sf::Color::Magenta);
			else
				this->Text_Menu_Options[i].setFillColor(this->Color_Menu);
			//RGB
			this->Text_Menu_Options[i].setOutlineColor(sf::Color(this->index_R, this->index_G, this->index_B, 255));
		}
		this->Navigation_Index_Changed = false;

	//RGB Highscore
	this->Text_Highscore.setOutlineColor(sf::Color(this->index_R, this->index_G, this->index_B, 255));

	//RGB
	this->Text_Creator.setOutlineColor(sf::Color(this->index_R, this->index_G, this->index_B, 255));

	std::stringstream ssHighscore;
	ssHighscore << "Highscore: " << this->Highscore;
	this->Text_Highscore.setString(ssHighscore.str());
}

void Menu::udpate()
{
	//Calls every function that updates stuff

	//Event polling
	this->pollEvents();

	//Updating mouse
	this->mouse.updateMousePositions(*this->window, false);

	//Text updating
	this->updateText();
}

//render
void Menu::renderText()
{
	//Title text
	this->window->draw(this->Text_Title);

	//Menu_Options
	for (int i = 0; i < 3; i++)
	{
		this->window->draw(this->Text_Menu_Options[i]);
	}

	this->window->draw(this->Text_Highscore);

	this->window->draw(this->Text_Creator);
}

void Menu::renderBackground()
{
	this->window->draw(this->Sprite_Background);
}

void Menu::render()
{
	//Clears window
	this->window->clear(sf::Color(50, 50, 50, 255));

	//Background
	this->renderBackground();

	this->renderText();
	//Displays on window
	this->window->display();
}
