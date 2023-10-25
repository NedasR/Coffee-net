#include "GameManager.hpp"

GameManager* GameManager::m_instance = nullptr;
Character* GameManager::m_headCharacter = nullptr;

GameManager::GameManager()
{
	if (!m_instance)
	{
		m_instance = this;
	}
}

GameManager::~GameManager()
{

}

void GameManager::SetHeadCharacter(Character& character)
{
	if (!m_headCharacter)
	{
		m_headCharacter = &character;
		m_headCharacter->isMain = true;
	}
	else 
	{
		m_headCharacter->isMain = false;
		m_headCharacter = &character;
		m_headCharacter->isMain = true;
	}
}

bool GameManager::IsHeadCharacter(Character& character)
{
	if (character.isMain)
	{
		return true;
	}
	return false;
}
