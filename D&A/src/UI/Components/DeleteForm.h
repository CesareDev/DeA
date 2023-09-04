#pragma once
#include "Core/ResourceManager.h"
#include "Button.h"

class DeleteForm : sf::Sprite
{
public:
	
	DeleteForm();
	~DeleteForm();

	void Init(const ResourceManager& resourceManager, const sf::Vector2f& position);
	void Render(sf::RenderTarget& target);

	bool IsYesClicked();
	bool IsNoClicked();

private:

	Button m_Yes;
	Button m_No;
};

