#pragma once

#include <memory>
#include "Character.hpp"
class GameManager
{
	public:

	static GameManager* m_instance;

	static Character* m_headCharacter;

	GameManager();

	~GameManager();

	void SetHeadCharacter(Character& character);

	bool IsHeadCharacter(Character& character);
};