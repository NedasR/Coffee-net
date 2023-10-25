#include "CircleScene.hpp"
#include "GameManager.hpp"
#include "RendererManager.hpp"
#include <iostream>

void CircleScene::LoadScene()
{
    character = std::make_shared<Character>();
    image.create(20, 20, sf::Color::Blue);
    texture.loadFromImage(image);
    character.get()->setPosition(20.0f, 20.0f);
    character.get()->setScale(7, 7);
    character.get()->setTexture(texture);
    character.get()->setColor(sf::Color(sf::Color::Blue));
	GameManager::m_instance->SetHeadCharacter(*character.get());
	RendererManager::AddToRenderer(character);

    /*
    load texture
    * 
    * object settings
    * 
    RendererManager::AddToRenderer(character);
    */
}

void CircleScene::Update()
{
    std::cout << character.get()->GetNetworkID() << std::endl;
}
