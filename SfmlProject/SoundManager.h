#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <string>

enum eSoundType
{
	PADDLE_BOUNCE,
	WALL_BOUNCE,
	BALL_OUT
};

class SoundManager final
{
public:
	static SoundManager& Get();
	void Register(eSoundType type, const std::string& path);
	std::shared_ptr<sf::Sound> GetSound(eSoundType type);

private:
	SoundManager();
	std::map<eSoundType, std::shared_ptr<sf::Sound>> sounds;
	static SoundManager* instance;
};