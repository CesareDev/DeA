#include "pch.h"
#include "LevelLabel.h"

LevelLabel::LevelLabel()
{
}

LevelLabel::~LevelLabel()
{
}

void LevelLabel::Init(const ResourceManager& resourceManager, const std::string& text)
{
	setString(text);
	const_cast<sf::Texture&>(resourceManager.GetFont().getTexture(80)).setSmooth(false);
	setFont(resourceManager.GetFont());
	setCharacterSize(80);
	setOutlineThickness(5.f);

	float x = (GLOBAL::WIN_WIDTH / 2.f) - (getGlobalBounds().width / 2.f);
	setPosition(x, 32.f);

	m_FillColor = getFillColor();
	m_FillColor.a = m_Alpha;
	setFillColor(m_FillColor);

	m_OutlineColor = sf::Color(0, 0, 0, m_Alpha);
	setOutlineColor(m_OutlineColor);
}

void LevelLabel::Update(float dt)
{
	if (!m_Still)
	{
		if (m_FadeIn && !m_Finish)
		{
			m_Alpha += 255 * dt;
			if (m_Alpha > 255)
				m_Alpha = 255;
			m_FillColor.a = m_Alpha;
			m_OutlineColor.a = m_Alpha;
			setFillColor(m_FillColor);
			setOutlineColor(m_OutlineColor);
			if (m_Alpha == 255)
			{
				m_FadeIn = false;
				m_Still = true;
			}
		}
		else if (!m_FadeIn && !m_Finish)
		{
			m_Alpha -= 255 * dt;
			if (m_Alpha < 0)
				m_Alpha = 0;
			m_FillColor.a = m_Alpha;
			m_OutlineColor.a = m_Alpha;
			setFillColor(m_FillColor);
			setOutlineColor(m_OutlineColor);
			if (m_Alpha == 0)
				m_Finish = true;
		}
	}
	else if (m_Still && !m_Finish)
	{
		m_ElapsedTime += dt;
		if (m_ElapsedTime > 1.f)
			m_Still = false;
	}
}

void LevelLabel::Render(sf::RenderTarget& target)
{
	if (!m_Finish)
	{
		const auto& currView = target.getView();
		target.setView(target.getDefaultView());
		target.draw(*this);
		target.setView(currView);
	}
}
