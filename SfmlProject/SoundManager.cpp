#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
}

SoundManager & SoundManager::Get()
{
	if (!SoundManager::instance)
		SoundManager::instance = new SoundManager();
	return *SoundManager::instance;
}

void SoundManager::Register(eSoundType type, const std::string& path)
{
	auto iterator = this->sounds.find(type);
	if (iterator != this->sounds.end() && this->sounds.size() > 0) {
		std::cerr << "sound of this type already register: " << type << std::endl;
		return;
	}

	std::shared_ptr<sf::SoundBuffer> sound_buff = std::make_shared<sf::SoundBuffer>();
	if (!sound_buff->loadFromFile(path)) {
		std::cerr << "couldn't load file along this path: " << path << std::endl;
		return;
	}

	std::shared_ptr<sf::Sound> sound = std::make_shared<sf::Sound>();
	sound->setBuffer(*sound_buff.get());
	this->sounds.emplace(type, sound);
	std::cout << "sound registered succesfully" << std::endl;
}

std::shared_ptr<sf::Sound> SoundManager::GetSound(eSoundType type)
{
	auto iterator = this->sounds.find(type);
	if (iterator != this->sounds.end()) {
		return this->sounds[type];
		std::cout << "sound succesfully found!" << std::endl;
	}
	return nullptr;
}
