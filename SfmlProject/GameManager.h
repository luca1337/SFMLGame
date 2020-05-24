#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <time.h>

class IEntity;
class Board;

// a const string es: const std::string& value <-- const it's because i cannot modify it after i set the value and the & means
// we passed a "reference to the pointer" so the object itself and not a copy, and if it's a reference it also must be const, otherwise
// it's senseless, a reference to an object must always be const to ensure that the object is not modified.

class GameManager final
{
public:
	static GameManager& Get();
	void Init(unsigned int width, unsigned int height, const std::string& title);
	void Run();
	bool GetIsWindowOpen() const;
	void Add(std::shared_ptr<IEntity> ientity);
	float GetDeltaSeconds();
	std::shared_ptr<sf::RenderWindow> GetWindowHandle() const;

private:
	GameManager();
	~GameManager();
	std::shared_ptr<sf::RenderWindow> window;
	static GameManager* instance;
	std::vector<std::shared_ptr<IEntity>> entities;

	sf::Clock clock;
	float delta_seconds;

	void UpdateDelta();

	/*Entities*/
	std::shared_ptr<Board> board;
};

