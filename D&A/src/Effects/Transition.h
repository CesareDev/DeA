#pragma once 
#include "Core/TextureManager.h"

class Transition
{
public:

	Transition();
	~Transition();

	void Init(const TextureManager& textureManager);
	void Render(sf::RenderTarget& target);
	bool FadeIn(float dt, float animatinTimeInSeconds = 1.f);
	bool FadeOut(float dt, float animatinTimeInSeconds = 1.f);

private:

	sf::RectangleShape m_FadeRect;
	bool m_EnterOrExit = true;
	float m_Alpha = 255.f;
};

