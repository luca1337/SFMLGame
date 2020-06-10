#include "GameManager.h"
#include "IUpdatable.h"
#include "IRenderable.h"

#include "StateSetup.h"
#include "StatePlay.h"
#include "StateGameOver.h"
#include "SoundManager.h"

//unabsrtraction entity includes
#include "Board.h"

GameManager* GameManager::instance = nullptr;

GameManager& GameManager::Get()
{
	if (!instance)
		instance = new GameManager();

	return *instance;
}

void GameManager::Init(unsigned int width, unsigned int height, const std::string & title)
{
	std::srand((unsigned)time(nullptr));

	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
	this->window->setFramerateLimit(144);

	/*Init Entities*/
	board = std::make_shared<Board>();
	this->Add(board);

	SoundManager& sm = SoundManager::Get();
	sm.Register(eSoundType::PADDLE_BOUNCE, "paddle.wav");
	sm.Register(eSoundType::WALL_BOUNCE, "wall.wav");
}

void GameManager::Run()
{
	while (this->GetIsWindowOpen())
	{
		this->UpdateDelta();

		sf::Event ev;

		while (this->window->pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				this->window->close();
			}
		}

		this->window->clear();

		for (auto entity : entities)
		{
			if (entity->GetEnabled())
			{
				/*Update*/
				auto updatable_entity = std::dynamic_pointer_cast<IUpdatable>(entity);
				if (updatable_entity) updatable_entity->Update(delta_seconds);

				/*Render*/
				auto renderable_entity = std::dynamic_pointer_cast<IRenderable>(entity);
				if (renderable_entity) renderable_entity->Render(window);
			}
		}

		this->window->display();
	}
}

bool GameManager::GetIsWindowOpen() const
{
	return this->window->isOpen();
}

void GameManager::Add(std::shared_ptr<IEntity> ientity)
{
	entities.push_back(ientity);
}

float GameManager::GetDeltaSeconds()
{
	return delta_seconds;
}

std::shared_ptr<sf::RenderWindow> GameManager::GetWindowHandle() const
{
	return this->window;
}

GameManager::GameManager() 
{
	/*this->state_setup->SetNextState(this->state_play);
	this->state_play->SetNextState(this->state_game_over);
	this->state_game_over->SetNextState(this->state_play);

	current_state = this->state_setup;
	current_state->OnStateEnter();*/
}

GameManager::~GameManager()
{
	delete this->instance;
}

void GameManager::UpdateDelta()
{
	/*Updates the delta variable with the time it takes to update and render 1 frame*/

	this->delta_seconds = this->clock.restart().asSeconds();
}
