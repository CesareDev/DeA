#pragma once
#include "Core/ResourceManager.h"
#include "Core/Camera.h"

class LevelLabel : public sf::Text
{
public:

	LevelLabel();
	~LevelLabel();

	void Init(const ResourceManager& resourceManager, const std::string& text);
	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:

	sf::Color m_FillColor;
	sf::Color m_OutlineColor;
	float m_ElapsedTime;
	bool m_FadeIn = true;
	bool m_Still = false;
	bool m_Finish = false;
	int m_Alpha = 0;
};

